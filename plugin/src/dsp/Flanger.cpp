#include "Flanger.h"

namespace juce::dsp {
Flanger::Flanger(juce::AudioProcessorValueTreeState &params)
    : parameters(params) {
  parameters.addParameterListener(ParamIDs::lfoFreq, this);
  parameters.addParameterListener(ParamIDs::lfoDepth, this);
  parameters.addParameterListener(ParamIDs::mix, this);

  auto oscFunction = [](float x) { return std::sin(x); };
  osc.initialise(oscFunction);

  dryWet.setMixingRule(DryWetMixingRule::linear);
  // waveform shape
}

Flanger::~Flanger() {
  parameters.removeParameterListener(ParamIDs::lfoFreq, this);
  parameters.removeParameterListener(ParamIDs::lfoDepth, this);
  parameters.removeParameterListener(ParamIDs::mix, this);
  // waveform shape
}

void Flanger::prepare(ProcessSpec &spec) {

  jassert(spec.sampleRate > 0);
  jassert(spec.numChannels > 0);

  sampleRate = spec.sampleRate;

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
  std::fill (feedback.begin(), feedback.end(), static_cast<float> (0));

  delay.reset();
  osc.reset();
  dryWet.reset();
}

void Flanger::update() {
  osc.setFrequency (getLFOFreq());
  dryWet.setWetMixProportion (getMix());
}

void Flanger::process(const ProcessContextReplacing<float>& context) {
    const auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    const auto numChannels = outputBlock.getNumChannels();
    const auto numSamples = outputBlock.getNumSamples();

    jassert(inputBlock.getNumChannels() == numChannels);
    jassert(inputBlock.getNumChannels() == feedback.size());
    jassert(inputBlock.getNumSamples() == numSamples);

    if (context.isBypassed) {
        outputBlock.copyFrom(inputBlock);
        return;
    }

    dryWet.pushDrySamples(inputBlock);

    for (size_t channel = 0; channel < numChannels; ++channel) {
        auto* inputSamples = inputBlock.getChannelPointer(channel);
        auto* outputSamples = outputBlock.getChannelPointer(channel);
        float phaseOffset = (channel == 1) ? juce::MathConstants<float>::halfPi * getAmountOfStereo() : 0.0f;

        for (size_t i = 0; i < numSamples; ++i) {
          // Hämta indata för detta sample
          auto input = inputSamples[i];

          float lfoValue = osc.processSample(0.f + phaseOffset);

          float delayCalc = (float) (getDelay() + lfoValue * lfoDepth)  / 1000.0f * sampleRate ;
          delay.setDelay(delayCalc);

          // Apply feedback to the input
          auto feedbackSign = getInvertPolarity() ? -1 : 1;
          float inputWithFeedback = input + feedbackSign * feedback[channel];
          delay.pushSample((int) channel, inputWithFeedback);
          outputSamples[i] = delay.popSample((int) channel);

          // Update feedback
          feedback[channel] = outputSamples[i] * getFeedback();
        }
    }

    dryWet.mixWetSamples(outputBlock);
}



void Flanger::updateDelayValues(size_t numSamples) {}

//==============================================================================

void Flanger::parameterChanged(const juce::String &parameterID,
                               float newValue) {
  if (parameterID == ParamIDs::lfoFreq) {
    update();
    // osc.setFrequency(newValue);
  } else if (parameterID == ParamIDs::lfoDepth) {
    lfoDepth = newValue;
    update();
    // lfo.setDepth(newValue);
  } else if (parameterID == ParamIDs::mix) {
    // dryWet.setWetMixProportion(newValue);
    update();
  }
}
} // namespace juce::dsp