#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace Gui {
class Button : public juce::Component {
public:
  Button(const std::string& name) {
    label.setText(name, juce::dontSendNotification);
    label.setSize(labelWidth, labelHeight);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    button.setSize(buttonWidth, buttonHeight);
    addAndMakeVisible(button);
  }
  /*
    void paint(juce::Graphics &g) {
      g.fillAll(juce::Colours::black);
    }
  */
  void resized() override {
    auto area = getLocalBounds();

    int labelX = (area.getWidth() - labelWidth) / 2;
    int labelY = labelHeight + 10; // Top of the area
    label.setBounds(labelX, labelY, labelWidth, labelHeight);

    int buttonX = (area.getWidth() - buttonWidth) / 2; // Centered horizontally
    int buttonY = labelY + labelHeight + padding;
    button.setBounds(buttonX, buttonY, buttonWidth, buttonHeight);
  }

  juce::ToggleButton button;
private:
  juce::Label label;
  int labelWidth = 150, labelHeight = 16;
  int buttonWidth = 25, buttonHeight = 25;
  int padding = 60;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Button)
};
}