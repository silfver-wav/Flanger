#include "Flanger.h"

namespace juce::dsp {
Flanger::Flanger(juce::AudioProcessorValueTreeState &params)
    : parameters(params) {
  parameters.addParameterListener(ParamIDs::lfoFreq, this);
  parameters.addParameterListener(ParamIDs::lfoDepth, this);
  parameters.addParameterListener(ParamIDs::mix, this);
  parameters.addParameterListener(ParamIDs::waveForm, this);
  dryWet.setMixingRule(DryWetMixingRule::linear);
}

Flanger::~Flanger() {
  parameters.removeParameterListener(ParamIDs::lfoFreq, this);
  parameters.removeParameterListener(ParamIDs::lfoDepth, this);
  parameters.removeParameterListener(ParamIDs::mix, this);
}

void Flanger::prepare(ProcessSpec &spec) {

  jassert(spec.sampleRate > 0);
  jassert(spec.numChannels > 0);

  sampleRate = spec.sampleRate;

  // TODO: fixa maxPossibleDelay
  const auto maxPossibleDelay =
      std::ceil((maximumDelayModulation * maxDepth * oscVolumeMultiplier +
                 maxCentreDelayMs) *
                sampleRate / 1000.0);
  delay = DelayLine<float, DelayLineInterpolationTypes::Linear>{
      static_cast<int>(maxPossibleDelay)};
  delay.prepare(spec);

  dryWet.prepare(spec);
  feedback.resize(spec.numChannels);

  osc.prepare(spec);
  bufferDelayTimes.setSize(1, (int)spec.maximumBlockSize, false, false, true);

  update();
  reset();
}

void Flanger::reset() {
  std::fill(feedback.begin(), feedback.end(), static_cast<float>(0));

  delay.reset();
  osc.reset();
  dryWet.reset();
}

void Flanger::update() {
  std::function<float(float)> oscFunction;
  switch (getWaveForm()) {
  case 0:
    oscFunction = [](float x) { return std::sin(x); };
    break;
  case 1:
    oscFunction = [](float x) {
      return (2 / MathConstants<float>::pi) * std::asin(std::sin(x));
    };
    break;
  case 2:
    oscFunction = [](float x) { return x < 0.0f ? -1.0f : 1.0f; };
    break;
  case 3:
    oscFunction = [](float x) { return x / MathConstants<float>::pi; };
    break;
  default:
    oscFunction = [](float x) { return std::sin(x); };
    break;
  }

  osc.initialise(oscFunction);

  float freq;
  switch (getLFOSyncMode()) {
  case 0:
    freq = getLFOFreq();
    break;
  case 1:
    freq = getNoteDurations(getLFOSyncRate());
    break;
  default:
    freq = getLFOFreq();
    break;
  }
  osc.setFrequency(freq);

  dryWet.setWetMixProportion(getMix() / 2.0f);
}

float Flanger::getNoteDurations(const int choice) const {
  if (BPM <= 0.0)
    return 0.0f;

  double freq = 0.0;
  switch (choice) {
  case 0: // "1/1" (Whole note)
    freq = 120.0 / BPM;
    break;
  case 1: // Half note (1/2)
    freq = 120 / BPM;
    break;
  case 2: // Quarter note (1/4)
    freq = 60 / BPM;
    break;
  case 3: // Dotted-quarter note (1/4.)
    freq = 90 / BPM;
    break;
  case 4: // Triplet-quarter note (1/4T)
    freq = 40 / BPM;
    break;
  case 5: // Eighth note (1/8)
    freq = 30 / BPM;
    break;
  case 6: // Dotted-eighth note (1/8.)
    freq = 45 / BPM;
    break;
  case 7: // Triplet-eighth note (1/8T)
    freq = 20 / BPM;
    break;
  case 8: // Sixteenth note (1/16)
    freq = 15 / BPM;
    break;
  case 9: // Dotted-sixteenth note (1/16.)
    freq = 22.5 / BPM;
    break;
  case 10: // Triplet-sixteenth note (1/16T)
    freq = 10 / BPM;
    break;
  default:
    break;
  }

  return static_cast<float>(freq);
}

void Flanger::process(const ProcessContextReplacing<float> &context) {
  const auto &inputBlock = context.getInputBlock();
  auto &outputBlock = context.getOutputBlock();
  const auto numChannels = outputBlock.getNumChannels();
  const auto numSamples = outputBlock.getNumSamples();

  jassert(inputBlock.getNumChannels() == numChannels);
  jassert(inputBlock.getNumChannels() == feedback.size());
  jassert(inputBlock.getNumSamples() == numSamples);

  if (getBypass()) {
    return;
  }

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
          (float)(getDelay() + lfoValue * lfoDepth) / 1000.0f * sampleRate;
      delay.setDelay(delayCalc);

      auto feedbackSign = getInvertPolarity() ? -1 : 1;
      float inputWithFeedback = input + feedbackSign * feedback[channel];
      delay.pushSample((int)channel, inputWithFeedback);
      auto wetSignal = delay.popSample((int)channel);

      if (getInvertWet()) {
        wetSignal = -wetSignal;
      }

      outputSamples[i] = wetSignal;
      feedback[channel] = wetSignal * getFeedback();
    }
  }

  dryWet.mixWetSamples(outputBlock);
}

void Flanger::setBPM(double bpm) {
  if (std::abs(bpm - BPM) > 0.01f) {
    BPM = bpm;
    update();
  }
}

void Flanger::updateDelayValues(size_t numSamples) {}

//==============================================================================

void Flanger::parameterChanged(const juce::String &parameterID,
                               float newValue) {
  update();
}

} // namespace juce::dsp