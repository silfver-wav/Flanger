#include "Params.h"
#include <juce_audio_processors/juce_audio_processors.h>

juce::AudioProcessorValueTreeState::ParameterLayout
Params::createParameterLayout() {
  using namespace juce;

  std::vector<std::unique_ptr<RangedAudioParameter>> params;

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::delay, "Delay",
      NormalisableRange(ParamRange::delayStart, ParamRange::delayEnd,
                        ParamRange::delayInterval),
      ParamRange::delayDefault, String(),
      AudioProcessorParameter::genericParameter,
      [](float value, float) { return String(value, 1) + " ms"; }));

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::feedback, "Feedback",
      NormalisableRange(ParamRange::feedbackStart, ParamRange::feedbackEnd),
      ParamRange::feedbackDefault, String(),
      AudioProcessorParameter::genericParameter,
      [](float value, float) { return String(static_cast<int>(value * 100)) + " %"; }));

  params.push_back(std::make_unique<AudioParameterBool>(
      ParamIDs::invertPolarity, "Invert Polarity", false));

  params.push_back(std::make_unique<AudioParameterBool>(ParamIDs::invertWet,
                                                        "Invert Wet", false));

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::lfoFreq, "LFO Frequency",
      NormalisableRange(ParamRange::lfoFreqStart, ParamRange::lfoFreqEnd,
                        ParamRange::lfoFreqInterval),
      ParamRange::lfoFreqDefault, String(),
      AudioProcessorParameter::genericParameter,
      [](float value, float) { return String(value, 0.01) + " Hz"; }));

  params.push_back(std::make_unique<AudioParameterChoice>(
      ParamIDs::lfoSyncMode, "LFO Sync Mode",
      StringArray{"Frequency", "Tempo-Synced"}, 0));

  params.push_back(std::make_unique<AudioParameterChoice>(
      ParamIDs::lfoRate, "LFO Rate", ParamRange::lfoRates, 2));

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::lfoDepth, "LFO Depth",
      NormalisableRange(ParamRange::lfoDepthStart, ParamRange::lfoDepthEnd,
                        ParamRange::lfoDepthInterval),
      ParamRange::lfoDepthDefault));

  params.push_back(std::make_unique<AudioParameterChoice>(
      ParamIDs::waveForm, "LFO Wave Form", ParamRange::waveformChoices, 0));

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::stereo, "Stereo",
      NormalisableRange(ParamRange::stereoStart, ParamRange::stereoEnd,
                        ParamRange::stereoInterval),
      ParamRange::stereoDefault, String(),
      AudioProcessorParameter::genericParameter,
      [](float value, float) { return String(static_cast<int>(value * 100)) + " %"; }));

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::mix, "Mix",
      NormalisableRange(ParamRange::mixStart, ParamRange::mixEnd,
                        ParamRange::mixInterval),
      ParamRange::mixDefault, String(),
      AudioProcessorParameter::genericParameter,
      [](float value, float) { return String(static_cast<int>(value * 100)) + " %"; }));

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::saturation, "Saturation",
      NormalisableRange(ParamRange::saturationStart, ParamRange::saturationEnd,
                        ParamRange::saturationInterval),
      ParamRange::saturationDefault));

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::gain, "Gain",
      NormalisableRange(ParamRange::gainStart, ParamRange::gainEnd,
                        ParamRange::gainInterval),
      ParamRange::gainDefault, String(),
      AudioProcessorParameter::genericParameter,
      [](float value, float) { return String(value, 1) + " dB "; }));

  params.push_back(
      std::make_unique<AudioParameterBool>(ParamIDs::power, "Power", true));

  return {params.begin(), params.end()};
}
