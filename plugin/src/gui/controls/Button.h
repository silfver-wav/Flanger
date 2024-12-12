#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

class Button : public juce::Component {
public:
  Button(const std::string& name) {
    button.setSize(buttonWidth, buttonHeight);
    addAndMakeVisible(button);

    label.setText(name, juce::dontSendNotification);
    label.setSize(labelWidth, labelHeight);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
  }

  void resized() override {
    auto area = getLocalBounds();
    button.setBounds(area.removeFromTop(area.getHeight() - labelHeight).reduced(5));
    label.setBounds(area);
  }

  juce::ToggleButton button;
private:
  juce::Label label;
  int labelWidth = 5, labelHeight = 5;
  int buttonWidth = 5, buttonHeight = 5;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Button)
};
