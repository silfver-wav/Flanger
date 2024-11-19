#pragma once

#include "../utils/Params.h"
#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>


enum Waveform { SINE, TRIANGLE, SQUARE };

class LFO {
public:
  LFO();
  ~LFO();
  void prepare(float newSampleRate);
  float processSample(float input);

  void setFrequency(float newFrequency) noexcept {
    frequency.setTargetValue(newFrequency);
  }

  void setDepth(float newDepth) { depth = newDepth; }

  void setWaveform(Waveform newWaveform) { waveform = newWaveform; }

private:
  float sampleRate;
  float depth = ParamRange::lfoDepthDefault;
  juce::SmoothedValue<float> frequency{static_cast<float>(ParamRange::lfoFreqDefault)};
  juce::dsp::Phase<float> phase;
  Waveform waveform = Waveform::SINE;
};
