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
    int height = area.getHeight() / 2;
    label.setBounds(area.removeFromTop(height));
    comboBox.setBounds (10, height, getWidth() - comboBoxWidth, comboBoxHeight);
  }
  juce::ComboBox comboBox;
private:
  juce::Label label;
  int labelWidth = 150, labelHeight = 16;
  int comboBoxWidth = 20, comboBoxHeight = 20;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ComboBoxKnob)
};
