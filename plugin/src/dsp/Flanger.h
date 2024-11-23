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
  void setBPM(double bpm);
private:
  AudioProcessorValueTreeState &parameters;
  Oscillator<float> osc;
  DelayLine<float, DelayLineInterpolationTypes::Linear> delay;
  DryWetMixer<float> dryWet;
  std::vector<float> feedback { 2 };
  AudioBuffer<float> bufferDelayTimes;

  double sampleRate = 44100.0;
  int numChannels = 0;
  double BPM = 0;

  float maxDelayTime = 0.02f, lfoDepth = 1.0f;

  static constexpr float maxDepth               = 1.0,
                            maxCentreDelayMs       = 100.0,
                            maximumDelayModulation = 20.0;

  void parameterChanged(const juce::String &parameterID, float newValue);
  void updateOsc();
  void updateFreq();
  float getSubdivisionFreq(int choice) const;
  void updateDryWet();

  [[nodiscard]] float getDelay() const {
    return *parameters.getRawParameterValue(ParamIDs::delay);
  }

  [[nodiscard]] float getFeedback() const {  // testa utan smootedvalue sen
    return *parameters.getRawParameterValue(ParamIDs::feedback);
  }

  [[nodiscard]] bool getInvertPolarity() const {
    return *parameters.getRawParameterValue(ParamIDs::invertPolarity);
  }

  [[nodiscard]] bool getInvertWet() const {
    return *parameters.getRawParameterValue(ParamIDs::invertWet);
  }

  [[nodiscard]] bool getBypass() const {
    return *parameters.getRawParameterValue(ParamIDs::bypass);
  }

  [[nodiscard]] float getLFOFreq() const {
    return *parameters.getRawParameterValue(ParamIDs::lfoFreq);
  }

  [[nodiscard]] int getLFOSyncRate() const {
    return static_cast<int>(*parameters.getRawParameterValue(ParamIDs::lfoRate));
  }

  [[nodiscard]] int getLFOSyncMode() const {
    return static_cast<int>(*parameters.getRawParameterValue(ParamIDs::lfoSyncMode));
  }

  [[nodiscard]] float getLFODepth() const {
    return *parameters.getRawParameterValue(ParamIDs::lfoDepth);
  }

  [[nodiscard]] int getWaveForm() const {
    return static_cast<int>(*parameters.getRawParameterValue(ParamIDs::waveForm));
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
