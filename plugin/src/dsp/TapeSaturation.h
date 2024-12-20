#pragma once

#include "../utils/Params.h"

#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>

namespace DSP {
class TapeSaturation : public juce::AudioProcessorValueTreeState::Listener {
public:
  TapeSaturation(juce::AudioProcessorValueTreeState &params);
  ~TapeSaturation();

  void prepare(juce::dsp::ProcessSpec &spec);

  void process(const juce::dsp::ProcessContextReplacing<float>& context)
  {
    const auto &inputBlock = context.getInputBlock();
    auto &outputBlock = context.getOutputBlock();
    const auto numChannels = outputBlock.getNumChannels();
    const auto numSamples = outputBlock.getNumSamples();

    jassert(inputBlock.getNumChannels() == numChannels);
    jassert(inputBlock.getNumSamples() == numSamples);

    dryWet.pushDrySamples(inputBlock);

    for (size_t channel = 0; channel < numChannels; ++channel) {
      auto *inputSamples = inputBlock.getChannelPointer(channel);
      auto *outputSamples = outputBlock.getChannelPointer(channel);

      for (size_t i = 0; i < numSamples; ++i) {
        auto input = inputSamples[i];
        outputSamples[i] = std::tanh(input);
      }
    }

    dryWet.mixWetSamples(outputBlock);
  }

private:
  juce::AudioProcessorValueTreeState &parameters;
  juce::dsp::DryWetMixer<float> dryWet;

  void parameterChanged(const juce::String &parameterID, float newValue);
  [[nodiscard]] float getSaturation() const {
    return *parameters.getRawParameterValue(ParamIDs::saturation);
  }
};
}
