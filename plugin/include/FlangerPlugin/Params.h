#pragma once
#include <JuceHeader.h>

namespace ParamIDs
{
    constexpr auto delay = "delay";
    constexpr auto depth = "depth";
    constexpr auto feedback = "feedback";
    constexpr auto invertPolarity = "invertPolarity";
    constexpr auto lfoFreq = "lfoFreq";
    constexpr auto lfoDepth = "lfoDepth";
    constexpr auto stereo = "stereo";
    constexpr auto bypass = "bypass";
    constexpr auto mix = "mix";
    constexpr auto gain = "gain";
}

namespace ParamRange
{
    constexpr int delayStart = 0.0f;
    constexpr int delayEnd = 20.0f;
    constexpr int delayInterval = 0.1f;
    constexpr float delayDefault = 5.0f;

    constexpr float depthStart = 0.0f;
    constexpr float depthEnd = 20.0f;
    constexpr float depthInterval = 0.1f;
    constexpr float depthDefault = 5.0f;

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

    constexpr float lfoDepthStart = 0.f;
    constexpr float lfoDepthEnd = 1.f;
    constexpr float lfoDepthInterval = 0.01f;
    constexpr float lfoDepthDefault = 0.5f;

    constexpr float stereoStart = 0.f;
    constexpr float stereoEnd = 1.f;
    constexpr float stereoInterval = 0.01f;
    constexpr float stereoDefault = 0.f;

    constexpr float mixStart = 0.f;
    constexpr float mixEnd = 1.f;
    constexpr float mixInterval = 0.01f;
    constexpr float mixDefault = 0.f;

    constexpr float gainStart = -12.0f;
    constexpr float gainEnd = 12.0f;
    constexpr float gainInterval = 0.1f;
    constexpr float gainDefault = 0.0f;
}

class Params
{
public:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
};