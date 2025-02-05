#pragma once

#include "../../utils/Params.h"
#include "../controls/PresetPanel.h"
#include "../controls/lookandfeel/PowerButtonLookAndFeel.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

namespace Gui {
class HeaderComponent : public juce::Component {
public:
  HeaderComponent(juce::AudioProcessorValueTreeState& parameters, Service::PresetManger presetManger) : presetPanel(presetManger) {
    addAndMakeVisible(presetPanel);
    powerButton.setLookAndFeel(&powerButtonLookAndFeel);
    powerButton.setClickingTogglesState(true);
    addAndMakeVisible(powerButton);

    powerButtonAttachment =
    std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(parameters, ParamIDs::power, powerButton);
  }

  void paint (juce::Graphics& g) override {
    g.setColour(juce::Colours::black);
  }

  void resized() override {
    auto bounds = getLocalBounds();
    bounds.removeFromLeft(proportionOfWidth(0.01f));
    // bounds.removeFromTop(proportionOfHeight(0.05f));
    // bounds.removeFromBottom(proportionOfHeight(0.05f));
    powerButton.setBounds(bounds.removeFromLeft(bounds.proportionOfWidth(0.1f)).reduced(2));
    presetPanel.setBounds(bounds.removeFromLeft(bounds.proportionOfWidth(0.9f)));
  }

private:
  juce::ToggleButton powerButton;
  PresetPanel presetPanel;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> powerButtonAttachment;

  PowerButtonLookAndFeel powerButtonLookAndFeel;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
}