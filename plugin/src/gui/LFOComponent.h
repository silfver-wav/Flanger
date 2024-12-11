#pragma once

#include "components/Knob.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class LFOComponent : public juce::Component {
public:
  LFOComponent(juce::AudioProcessorValueTreeState &parameters)
      : parameters(parameters),
        lfoFreq("Frequency", ParamRange::lfoFreqStart, ParamRange::lfoFreqEnd, ParamRange::lfoFreqInterval, ParamRange::lfoFreqDefault),
        lfoDepth("Depth", ParamRange::lfoDepthStart, ParamRange::lfoDepthEnd, ParamRange::lfoDepthInterval, ParamRange::lfoDepthDefault),
        stereo("Stereo", ParamRange::stereoStart, ParamRange::stereoEnd, ParamRange::stereoInterval, ParamRange::stereoDefault) {
    addAndMakeVisible(lfoFreq);
    addAndMakeVisible(lfoDepth);
    addAndMakeVisible(stereo);

    lfoFreqAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::lfoFreq, lfoFreq.slider);
    lfoDepthAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::lfoDepth, lfoDepth.slider);
    stereoAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::stereo, stereo.slider);
  }

  void paint(juce::Graphics &g) override {
    g.fillAll(juce::Colours::blanchedalmond);
  }

  void resized() override {
    auto area = getLocalBounds();
    auto knobWidth = getLocalBounds().getWidth() / 3;

    lfoFreq.setBounds(area.removeFromLeft(knobWidth).reduced(10));
    lfoDepth.setBounds(area.reduced(10));
    stereo.setBounds(area.removeFromLeft(knobWidth).reduced(10));
  }

private:
  juce::AudioProcessorValueTreeState &parameters;
  Knob lfoFreq;
  // lfoSyncMode
  // lfoRate
  Knob lfoDepth;
  // Waveform
  Knob stereo;

  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      lfoFreqAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      lfoDepthAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      stereoAttachment;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFOComponent)
};
