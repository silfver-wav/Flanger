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

    textButton.setButtonText("Flanger");
    addAndMakeVisible(textButton);
  }

  void paint (juce::Graphics& g) override {
    g.setColour(juce::Colours::black);
  }

  void resized() override {
    auto area = getLocalBounds().reduced(5);

    // Define proportions for power button, right button, and spacing
    auto powerWidth = area.proportionOfWidth(0.05f);
    auto rightButtonWidth = area.proportionOfWidth(0.05f);
    auto gapWidth = area.proportionOfWidth(0.25f); // Adjust as needed
    auto presetWidth = area.getWidth() - powerWidth - rightButtonWidth - (2 * gapWidth);

    powerButton.setBounds(area.removeFromLeft(powerWidth));  // Left: Power button
    area.removeFromLeft(gapWidth); // Left spacing
    presetPanel.setBounds(area.removeFromLeft(presetWidth)); // Center: Preset panel
    area.removeFromLeft(gapWidth); // Right spacing
    textButton.setBounds(area.removeFromLeft(rightButtonWidth)); // Right: New button
  }


private:
  juce::ToggleButton powerButton;
  PresetPanel presetPanel;
  juce::TextButton textButton;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> powerButtonAttachment;


  PowerButtonLookAndFeel powerButtonLookAndFeel;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
}