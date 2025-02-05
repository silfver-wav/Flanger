#pragma once

#include "../../utils/Utils.h"
#include "lookandfeel/KnobLookAndFeel.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace Gui {
class Knob : public juce::Component {
public:
  Knob(const std::string& name, const float start, const float end,
       const float interval, const float defaultValue) {
    label.setText(name, juce::dontSendNotification);
    label.setColour(juce::Label::textColourId, juce::Colours::black);
    label.setSize(labelWidth, labelHeight);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setSize(sliderWidth, sliderHeight);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    slider.setLookAndFeel(&knobLookAndFeel);

    slider.setRange(start, end, interval);

    slider.setPopupDisplayEnabled(false, false, this);
    slider.setValue(defaultValue);
    slider.setColour(juce::Slider::ColourIds::trackColourId, Colours::secondaryColour);
    slider.setDoubleClickReturnValue(true, defaultValue);
    addAndMakeVisible(slider);
  }

  void resized() override {
    auto area = getLocalBounds();

    int labelX = (area.getWidth() - labelWidth) / 2;
    int labelY = labelHeight + 10;
    label.setBounds(labelX, labelY, labelWidth, labelHeight);

    int sliderX = (area.getWidth() - sliderWidth) / 2; // Centered horizontally
    int sliderY = labelY + labelHeight + 10;
    slider.setBounds(sliderX, sliderY, sliderWidth, sliderHeight);
  }

  juce::Slider slider;
private:
  juce::Label label;
  int labelWidth = 150, labelHeight = 16;
  int textBoxWidth = 150, textBoxHeight = 14;
  int sliderWidth = 150, sliderHeight = 150;

  KnobLookAndFeel knobLookAndFeel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};
}
