#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

namespace ParamIDs {
constexpr auto delay = "delay";
constexpr auto feedback = "feedback";
constexpr auto invertPolarity = "invertPolarity";
constexpr auto invertWet = "invertWet";
constexpr auto lfoFreq = "lfoFreq";
constexpr auto lfoSyncMode = "lfoSyncMode";
constexpr auto lfoRate = "lfoRate";
constexpr auto lfoDepth = "lfoDepth";
constexpr auto waveForm = "waveForm";
constexpr auto stereo = "stereo";
constexpr auto power = "power";
constexpr auto mix = "mix";
constexpr auto saturation = "saturation";
constexpr auto gain = "gain";
} // namespace ParamIDs

namespace ParamRange {
constexpr float delayStart = 0.01f;
constexpr float delayEnd = 20.0f;
constexpr float delayInterval = 0.001f;
constexpr float delayDefault = 5.0f;

constexpr float feedbackStart = 0.f;
constexpr float feedbackEnd = 1.f;
constexpr float feedbackInterval = 0.1f;
constexpr float feedbackDefault = 0.f;

constexpr float invertPolarityStart = 0.f;
constexpr float invertPolarityEnd = 0.5f;
constexpr float invertPolarityInterval = 0.001f;

constexpr float lfoFreqStart = 0.0f;
constexpr float lfoFreqEnd = 1.50f;
constexpr float lfoFreqInterval = 0.01f;
constexpr float lfoFreqDefault = 0.01f;

const juce::StringArray lfoRates = {"1/1",  "1/2",   "1/4",  "1/4.",
                                    "1/4T", "1/8",   "1/8.", "1/8T",
                                    "1/16", "1/16.", "1/16T"};

constexpr float lfoDepthStart = 0.f;
constexpr float lfoDepthEnd = 1.f;
constexpr float lfoDepthInterval = 0.01f;
constexpr float lfoDepthDefault = 0.5f;

const juce::StringArray waveformChoices = {"Sine", "Triangle", "Square", "Saw"};

constexpr float stereoStart = 0.f;
constexpr float stereoEnd = 1.f;
constexpr float stereoInterval = 0.01f;
constexpr float stereoDefault = 0.f;

constexpr float mixStart = 0.f;
constexpr float mixEnd = 1.f;
constexpr float mixInterval = 0.01f;
constexpr float mixDefault = 8.f;

constexpr float saturationStart = 0.f;
constexpr float saturationEnd = 1.f;
constexpr float saturationInterval = 0.01f;
constexpr float saturationDefault = 0.f;

constexpr float gainStart = -12.0f;
constexpr float gainEnd = 12.0f;
constexpr float gainInterval = 0.1f;
constexpr float gainDefault = 0.0f;
} // namespace ParamRange

class Params {
public:
  static juce::AudioProcessorValueTreeState::ParameterLayout
  createParameterLayout();
};
