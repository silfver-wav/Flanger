#pragma once

#include "../../utils/Params.h"
#include "../controls/PresetPanel.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

namespace Gui {
class HeaderComponent : public juce::Component {
public:
  HeaderComponent(juce::AudioProcessorValueTreeState& parameters, Service::PresetManger presetManger) : presetPanel(presetManger) {
    addAndMakeVisible(presetPanel);

    powerButton.setSize(25, 25);
    addAndMakeVisible(powerButton);

    powerButtonAttachment =
    std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(parameters, ParamIDs::power, powerButton);
  }

  void paint (juce::Graphics& g) override {
    g.fillAll(juce::Colours::blueviolet);
  }

  void resized() override {
    auto bounds = getLocalBounds();
    bounds.removeFromLeft(proportionOfWidth(0.05f));
    powerButton.setBounds(bounds.removeFromLeft(bounds.proportionOfWidth(0.1f)));
    presetPanel.setBounds(bounds.removeFromLeft(bounds.proportionOfWidth(0.8f)));
  }

private:
  juce::ToggleButton powerButton;
  PresetPanel presetPanel;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> powerButtonAttachment;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
}