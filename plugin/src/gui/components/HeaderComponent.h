#pragma once

#include "../controls/PresetPanel.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class HeaderComponent : public juce::Component {
public:
  HeaderComponent(juce::AudioProcessorValueTreeState& parameters, Service::PresetManger presetManger) : bypass("Bypass"), presetPanel(presetManger) {
    addAndMakeVisible(presetPanel);
  }

  void paint (juce::Graphics& g) override {
    g.fillAll(juce::Colours::black);
  }

  void resized() override {
    presetPanel.setBounds(getLocalBounds().removeFromTop(proportionOfWidth(0.1f))); // proportionOfHeight(0.1f)));
  }

private:
  Button bypass;
  PresetPanel presetPanel;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
