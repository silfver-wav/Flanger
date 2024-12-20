#include "Flanger.h"

namespace DSP {
Flanger::Flanger(juce::AudioProcessorValueTreeState &params)
    : parameters(params) {
  parameters.addParameterListener(ParamIDs::lfoFreq, this);
  parameters.addParameterListener(ParamIDs::lfoRate, this);
  parameters.addParameterListener(ParamIDs::lfoSyncMode, this);
  parameters.addParameterListener(ParamIDs::mix, this);
  parameters.addParameterListener(ParamIDs::waveForm, this);
  dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

Flanger::~Flanger() {
  parameters.removeParameterListener(ParamIDs::lfoFreq, this);
  parameters.removeParameterListener(ParamIDs::lfoRate, this);
  parameters.removeParameterListener(ParamIDs::lfoSyncMode, this);
  parameters.removeParameterListener(ParamIDs::mix, this);
  parameters.removeParameterListener(ParamIDs::waveForm, this);
}

void Flanger::prepare(juce::dsp::ProcessSpec &spec) {

  jassert(spec.sampleRate > 0);
  jassert(spec.numChannels > 0);

  sampleRate = spec.sampleRate;

  // TODO: fixa maxPossibleDelay
  const auto maxPossibleDelay =
      std::ceil((maximumDelayModulation * maxDepth + maxCentreDelayMs) *
                sampleRate / 1000.0);
  delay = juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear>{
      static_cast<int>(maxPossibleDelay)};
  delay.prepare(spec);

  dryWet.prepare(spec);
  feedback.resize(spec.numChannels);

  osc.prepare(spec);
  bufferDelayTimes.setSize(1, (int)spec.maximumBlockSize, false, false, true);

  updateFreq();
  updateOsc();
  updateDryWet();
  reset();
}

void Flanger::reset() {
  std::fill(feedback.begin(), feedback.end(), static_cast<float>(0));

  delay.reset();
  osc.reset();
  dryWet.reset();
}

void Flanger::process(
    const juce::dsp::ProcessContextReplacing<float> &context) {
  const auto &inputBlock = context.getInputBlock();
  auto &outputBlock = context.getOutputBlock();
  const auto numChannels = outputBlock.getNumChannels();
  const auto numSamples = outputBlock.getNumSamples();

  jassert(inputBlock.getNumChannels() == numChannels);
  jassert(inputBlock.getNumChannels() == feedback.size());
  jassert(inputBlock.getNumSamples() == numSamples);

  dryWet.pushDrySamples(inputBlock);

  for (size_t channel = 0; channel < numChannels; ++channel) {
    auto *inputSamples = inputBlock.getChannelPointer(channel);
    auto *outputSamples = outputBlock.getChannelPointer(channel);
    float phaseOffset = (channel == 1) ? juce::MathConstants<float>::halfPi *
                                             getAmountOfStereo()
                                       : 0.0f;

    for (size_t i = 0; i < numSamples; ++i) {
      auto input = inputSamples[i];

      float lfoValue = osc.processSample(0.f + phaseOffset);
      float delayCalc =
          (float)(getDelay() + lfoValue * getLFODepth()) / 1000.0f * sampleRate;
      delay.setDelay(delayCalc);

      auto feedbackSign = getInvertPolarity() ? -1 : 1;
      float inputWithFeedback = input + feedbackSign * feedback[channel];
      delay.pushSample((int)channel, inputWithFeedback);
      auto wetSignal = delay.popSample((int)channel);

      outputSamples[i] = getInvertWet() ? wetSignal : -wetSignal;
      feedback[channel] = wetSignal * getFeedback();
    }
  }

  dryWet.mixWetSamples(outputBlock);
}

void Flanger::setBPM(double bpm) {
  if (std::abs(bpm - BPM) > 0.01f) {
    BPM = bpm;
    updateFreq();
  }
}

//==============================================================================

void Flanger::parameterChanged(const juce::String &parameterID,
                               float newValue) {
  if (parameterID == ParamIDs::lfoFreq || parameterID == ParamIDs::lfoRate ||
      parameterID == ParamIDs::lfoSyncMode) {
    updateFreq();
  } else if (parameterID == ParamIDs::mix) {
    updateDryWet();
  } else if (parameterID == ParamIDs::waveForm) {
    updateOsc();
  }
}

void Flanger::updateDryWet() { dryWet.setWetMixProportion(getMix() / 2.0f); }

void Flanger::updateOsc() {
  std::function<float(float)> oscFunction;
  switch (getWaveForm()) {
  case 0:
    oscFunction = [](float x) { return std::sin(x); };
    break;
  case 1:
    oscFunction = [](float x) {
      return (2 / juce::MathConstants<float>::pi) * std::asin(std::sin(x));
    };
    break;
  case 2:
    oscFunction = [](float x) { return x < 0.0f ? -1.0f : 1.0f; };
    break;
  case 3:
    oscFunction = [](float x) { return x / juce::MathConstants<float>::pi; };
    break;
  default:
    oscFunction = [](float x) { return std::sin(x); };
    break;
  }

  osc.initialise(oscFunction);
}

void Flanger::updateFreq() {
  float freq;
  switch (getLFOSyncMode()) {
  case 0:
    freq = getLFOFreq();
    break;
  case 1:
    freq = getSubdivisionFreq(getLFOSyncRate());
    break;
  default:
    freq = getLFOFreq();
    break;
  }

  osc.setFrequency(freq);
}

float Flanger::getSubdivisionFreq(const int choice) const {
  if (BPM <= 0.0)
    return 0.0f;

  double beatDuration = 60.0 / BPM; // Quarter note (1/4) in seconds

  double multiplier = 1.0;
  switch (choice) {
  case 0:  // Whole note (1/1)
    multiplier = 4.0;
    break;
  case 1:  // Half note (1/2)
    multiplier = 2.0;
    break;
  case 2:  // Quarter note (1/4)
    multiplier = 1.0;
    break;
  case 3:  // Dotted-quarter note (1/4.)
    multiplier = 1.5;
    break;
  case 4:  // Triplet-quarter note (1/4T)
    multiplier = 2.0 / 3.0;
    break;
  case 5:  // Eighth note (1/8)
    multiplier = 0.5;
    break;
  case 6:  // Dotted-eighth note (1/8.)
    multiplier = 0.75;
    break;
  case 7:  // Triplet-eighth note (1/8T)
    multiplier = 1.0 / 3.0;
    break;
  case 8:  // Sixteenth note (1/16)
    multiplier = 0.25;
    break;
  case 9:  // Dotted-sixteenth note (1/16.)
    multiplier = 0.375;
    break;
  case 10: // Triplet-sixteenth note (1/16T)
    multiplier = 1.0 / 6.0;
    break;
  default:
    return 0.0f; // Invalid choice
  }

  double freq = 1.0 / (beatDuration * multiplier);

  return static_cast<float>(freq);
}

}