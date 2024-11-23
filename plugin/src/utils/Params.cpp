#include "Params.h"
#include <juce_audio_processors/juce_audio_processors.h>

juce::AudioProcessorValueTreeState::ParameterLayout
Params::createParameterLayout() {
  using namespace juce;

  std::vector<std::unique_ptr<RangedAudioParameter>> params;

  params.push_back(std::make_unique<juce::AudioParameterFloat>(
      ParamIDs::delay, "Delay",
      juce::NormalisableRange(ParamRange::delayStart, ParamRange::delayEnd,
                              ParamRange::delayInterval),
      ParamRange::delayDefault));

  params.push_back(std::make_unique<juce::AudioParameterFloat>(
      ParamIDs::feedback, "Feedback",
      juce::NormalisableRange(ParamRange::feedbackStart,
                              ParamRange::feedbackEnd),
      ParamRange::feedbackDefault));

  params.push_back(std::make_unique<juce::AudioParameterBool>(
      ParamIDs::invertPolarity, "Invert Polarity", false));

  params.push_back(std::make_unique<juce::AudioParameterBool>(
      ParamIDs::invertWet, "Invert Wet", false));

  params.push_back(std::make_unique<juce::AudioParameterFloat>(
      ParamIDs::lfoFreq, "LFO Frequency",
      juce::NormalisableRange(ParamRange::lfoFreqStart, ParamRange::lfoFreqEnd,
                              ParamRange::lfoFreqInterval),
      ParamRange::lfoFreqDefault));

  params.push_back(std::make_unique<juce::AudioParameterChoice>(
      ParamIDs::lfoSyncMode, "LFO Sync Mode",
      juce::StringArray{"Frequency", "Tempo-Synced"}, 0));

    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        ParamIDs::lfoRate,
        "LFO Rate",
        ParamRange::lfoRates,
        2));

  params.push_back(std::make_unique<juce::AudioParameterFloat>(
      ParamIDs::lfoDepth, "LFO Depth",
      juce::NormalisableRange(ParamRange::lfoDepthStart,
                              ParamRange::lfoDepthEnd,
                              ParamRange::lfoDepthInterval),
      ParamRange::lfoDepthDefault));

  params.push_back(std::make_unique<juce::AudioParameterChoice>(
      ParamIDs::waveForm, "LFO Wave Form", ParamRange::waveformChoices, 0));

  params.push_back(std::make_unique<juce::AudioParameterFloat>(
      ParamIDs::stereo, "Stereo",
      juce::NormalisableRange<float>(ParamRange::stereoStart,
                                     ParamRange::stereoEnd,
                                     ParamRange::stereoInterval),
      ParamRange::stereoDefault));

  params.push_back(std::make_unique<juce::AudioParameterFloat>(
      ParamIDs::mix, "Mix",
      juce::NormalisableRange(ParamRange::mixStart, ParamRange::mixEnd,
                              ParamRange::mixInterval),
      ParamRange::mixDefault));

  params.push_back(std::make_unique<AudioParameterFloat>(
      ParamIDs::gain, "Gain",
      NormalisableRange<float>(ParamRange::gainStart, ParamRange::gainEnd,
                               ParamRange::gainInterval),
      ParamRange::gainDefault));

  params.push_back(std::make_unique<juce::AudioParameterBool>(ParamIDs::bypass,
                                                              "Bypass", false));

  return {params.begin(), params.end()};
}
