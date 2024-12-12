#pragma once

#include "components/Button.h"
#include "components/Group.h"
#include "components/Knob.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class LFOComponent : public juce::Component {
public:
  LFOComponent(juce::AudioProcessorValueTreeState &parameters)
      : parameters(parameters),
        group("LFO"),
        lfoFreq("Frequency", ParamRange::lfoFreqStart, ParamRange::lfoFreqEnd, ParamRange::lfoFreqInterval, ParamRange::lfoFreqDefault),
        lfoSyncMode("Sync to project tempo"),
        lfoDepth("Depth", ParamRange::lfoDepthStart, ParamRange::lfoDepthEnd, ParamRange::lfoDepthInterval, ParamRange::lfoDepthDefault),
        stereo("Stereo", ParamRange::stereoStart, ParamRange::stereoEnd, ParamRange::stereoInterval, ParamRange::stereoDefault) {
    addAndMakeVisible(group);
    addAndMakeVisible(lfoFreq);
    addAndMakeVisible(lfoSyncMode);
    addAndMakeVisible(lfoDepth);
    addAndMakeVisible(stereo);

    lfoFreqAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::lfoFreq, lfoFreq.slider);
    lfoSyncModeAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(parameters, ParamIDs::lfoSyncMode, lfoSyncMode.button);
    lfoDepthAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::lfoDepth, lfoDepth.slider);
    stereoAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::stereo, stereo.slider);
  }

  void resized() override {
    auto area = getLocalBounds();
    group.setBounds(area.reduced(2));

    auto knobWidth = getLocalBounds().getWidth() / 4;
    lfoFreq.setBounds(area.removeFromLeft(knobWidth).reduced(10));
    lfoSyncMode.setBounds(area.removeFromLeft(knobWidth).reduced(10));
    lfoDepth.setBounds(area.removeFromLeft(knobWidth).reduced(10));
    stereo.setBounds(area.removeFromLeft(knobWidth).reduced(10));
  }

private:
  juce::AudioProcessorValueTreeState &parameters;
  Group group;

  Knob lfoFreq;
  Button lfoSyncMode;
  // lfoSyncMode
  // lfoRate
  Knob lfoDepth;
  // Waveform
  Knob stereo;

  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      lfoFreqAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
    lfoSyncModeAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      lfoDepthAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      stereoAttachment;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFOComponent)
};
