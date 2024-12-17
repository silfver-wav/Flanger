#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

class ComboBoxKnob : public juce::Component {
public:
  ComboBoxKnob(const std::string& name, const juce::StringArray& options) {
    label.setText(name, juce::dontSendNotification);
    label.setSize(labelWidth, labelHeight);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    for (int i = 0; i < options.size(); ++i) {
      comboBox.addItem(options[i], i + 1);
    }

    addAndMakeVisible(comboBox);
  }

  void resized() override {
    auto area = getLocalBounds();

    int labelX = (area.getWidth() - labelWidth) / 2;
    int labelY = labelHeight + 10; // Top of the area
    label.setBounds(labelX, labelY, labelWidth, labelHeight);

    int comboBoxX = (area.getWidth() - comboBoxWidth) / 2; // Centered horizontally
    int comboBoxY = labelY + labelHeight + padding;
    comboBox.setBounds (comboBoxX, comboBoxY, comboBoxWidth, comboBoxHeight);
  }

  juce::ComboBox comboBox;
private:
  juce::Label label;
  int labelWidth = 150, labelHeight = 16;
  int comboBoxWidth = 100, comboBoxHeight = 20;
  int padding = 60;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ComboBoxKnob)
};
