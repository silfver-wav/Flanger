#pragma once

#include "lookandfeel/InvertPolarityLookAndFeel.h"
#include "lookandfeel/ToggleButtonLookAndFeel.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace Gui {
class Button : public juce::Component {
public:
  Button(const std::string& name, auto id) {
    // TODO: make a better solution for this lookAndFeel application
    if (id == ParamIDs::invertPolarity || id == ParamIDs::invertWet) {
      button.setLookAndFeel(&invertPolarityLookAndFeel);
    } else {
      button.setLookAndFeel(&toggleButtonLookAndFeel);
    }
    addAndMakeVisible(button);

    label.setText(name, juce::dontSendNotification);
    label.setColour(juce::Label::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
  }

  void resized() override {
    auto area = getLocalBounds();

    int buttonWidth = 35, buttonHeight = 35;
    int buttonX = (area.getWidth() - buttonWidth) / 2;
    int buttonY = (area.getHeight() - buttonHeight) / 2;
    button.setBounds(buttonX, buttonY, buttonWidth, buttonHeight);

    int labelWidth = area.getWidth() * 0.9f, labelHeight = area.getHeight() * 0.25f;
    int labelX = (area.getWidth() - labelWidth) / 2;
    int labelY = area.getHeight() * 0.75f;
    label.setBounds(labelX, labelY, labelWidth, labelHeight);
  }

  juce::ToggleButton button;
private:
  juce::Label label;
  int padding = 60;

  InvertPolarityLookAndFeel invertPolarityLookAndFeel;
  ToggleButtonLookAndFeel toggleButtonLookAndFeel;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Button)
};
}