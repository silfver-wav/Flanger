#pragma once

#include "../utils/Params.h"
// #include "LFO.h"

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>

namespace juce::dsp {
class Flanger : public juce::AudioProcessorValueTreeState::Listener {
public:
  Flanger(juce::AudioProcessorValueTreeState &params);
  ~Flanger();
  void prepare(juce::dsp::ProcessSpec &spec);
  void process(const ProcessContextReplacing<float>& context);
  void reset();
  void update();

private:
  AudioProcessorValueTreeState &parameters;
  Oscillator<float> osc;
  DelayLine<float, DelayLineInterpolationTypes::Linear> delay;
  SmoothedValue<float, ValueSmoothingTypes::Linear> oscVolume;
  DryWetMixer<float> dryWet;
  std::vector<float> feedback { 2 };
  AudioBuffer<float> bufferDelayTimes;

  void updateDelayValues(size_t numSamples);

  double sampleRate = 44100.0;
  int numChannels = 0;

  float minFreq = 20.f, maxFreq = 20000.0f, baseDelay = 2.f, maxDelayTime = 0.02f, lfoDepth = 1.0f;

  static constexpr float maxDepth               = 1.0,
                            maxCentreDelayMs       = 100.0,
                            oscVolumeMultiplier    = 0.5,
                            maximumDelayModulation = 20.0;

  void parameterChanged(const juce::String &parameterID, float newValue);

  [[nodiscard]] float getDelay() const {
    return *parameters.getRawParameterValue(ParamIDs::delay);
  }

  [[nodiscard]] float getFeedback() const {  // testa utan smootedvalue sen
    return *parameters.getRawParameterValue(ParamIDs::feedback);
  }

  [[nodiscard]] bool getInvertPolarity() const {
    return *parameters.getRawParameterValue(ParamIDs::invertPolarity);
  }

  [[nodiscard]] bool getBypass() const {
    return *parameters.getRawParameterValue(ParamIDs::bypass);
  }

  [[nodiscard]] float getLFOFreq() const {
    return *parameters.getRawParameterValue(ParamIDs::lfoFreq);
  }

  [[nodiscard]] float getLFODepth() const {
    return *parameters.getRawParameterValue(ParamIDs::lfoDepth);
  }

  [[nodiscard]] float getAmountOfStereo() const {
    return *parameters.getRawParameterValue(ParamIDs::stereo);
  }

  [[nodiscard]] float getMix() const {
    return *parameters.getRawParameterValue(ParamIDs::mix);
  }

  [[nodiscard]] float getGain() const {
    float gainDB = *parameters.getRawParameterValue(ParamIDs::gain);
    return juce::Decibels::decibelsToGain(gainDB);
  }
};
}
