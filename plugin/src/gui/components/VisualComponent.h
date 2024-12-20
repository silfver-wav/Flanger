#pragma once

#include "../../utils/Params.h"
#include "../visuals/GainMeter.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace Gui {
class VisualComponent :
  public juce::Component,
  public juce::Timer
{
public:
  VisualComponent(juce::AudioProcessorValueTreeState &params, GainMeterSpirograph &gm); // AudioPluginAudioProcessor &p);

  void paint (juce::Graphics& g) override;

  void timerCallback() override;

  float getMix() const {
    return *parameters.getRawParameterValue(ParamIDs::mix);
  }

  void updateGainMeter();

private:
  juce::AudioProcessorValueTreeState &parameters;
  GainMeterSpirograph &gainMeter;
  float mixValue;

  GainMeterSpirograph::ImageOptions opts = {
    3,
    3,
    1,
    2056,
    256.f,
    24.f,
    .3f,
    1.f,
    3.f,
    1.f,
    juce::Colours::blue.withAlpha(.1f),
    juce::Colours::white.withAlpha(.5f),
    juce::Colours::transparentBlack,
    juce::Colours::blue.withAlpha(0.5f),
  };
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualComponent)
};
}