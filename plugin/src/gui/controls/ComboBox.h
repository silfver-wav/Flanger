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

    comboBox.setSize(comboBoxWidth, comboBoxHeight);
    for (int i = 0; i < options.size(); ++i)
      comboBox.addItem(options[i], i + 1);
    addAndMakeVisible(comboBox);
  }

  void resized() override {
    auto area = getLocalBounds();
    label.setBounds(area.removeFromTop(labelHeight));
    comboBox.setBounds(area.reduced(25));
  }

  juce::ComboBox comboBox;
private:
  juce::Label label;
  int labelWidth = 150, labelHeight = 16;
  int comboBoxWidth = 150, comboBoxHeight = 5;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ComboBoxKnob)
};
