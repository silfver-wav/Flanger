#pragma once

#include "../utils/Params.h"
#include "LFO.h"

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>

class Flanger : public juce::AudioProcessorValueTreeState::Listener {
public:
  Flanger(juce::AudioProcessorValueTreeState &params);
  ~Flanger();
  void prepare(juce::dsp::ProcessSpec &spec);
  void process(juce::AudioBuffer<float> &buffer);

private:
  juce::AudioProcessorValueTreeState &parameters;

  LFO lfo;

  juce::AudioBuffer<float> drySignal;
  std::vector<float> feedback;

  int numChannels = 0;
  float sampleRate = 44100.f;
  float minFreq = 20.f;
  float maxFreq = 20000.0f;
  float baseDelay = 2.f;

  void processBufferThroughCombFilter(juce::AudioBuffer<float> &buffer,
                                      int channel);
  void processMix(juce::AudioBuffer<float> &buffer);

  void parameterChanged(const juce::String &parameterID, float newValue);

  [[nodiscard]] float getDelay() const {
    return *parameters.getRawParameterValue(ParamIDs::delay);
  }

  [[nodiscard]] float getDepth() const {
    return *parameters.getRawParameterValue(ParamIDs::depth);
  }

  [[nodiscard]] float getFeedback() const {
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
