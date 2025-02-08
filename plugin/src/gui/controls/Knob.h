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
    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setLookAndFeel(&knobLookAndFeel);

    slider.setRange(start, end, interval);

    slider.setPopupDisplayEnabled(false, false, this);
    slider.setValue(defaultValue);
    slider.setDoubleClickReturnValue(true, defaultValue);
    addAndMakeVisible(slider);

    label.setText(name, juce::dontSendNotification);
    label.setColour(juce::Label::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
  }

  void resized() override {
    auto area = getLocalBounds().toFloat();

    int sliderWidth = (int) area.getWidth() * 0.9f, sliderHeight = (int) area.getHeight() * 0.9f;
    int sliderX = (area.getWidth() - sliderWidth) / 2;
    slider.setBounds(sliderX, 0, sliderWidth, sliderHeight);

    int labelWidth = area.getWidth() * 0.9f, labelHeight = area.getHeight() * 0.25f;
    int labelX = (area.getWidth() - labelWidth) / 2;
    int labelY = area.getHeight() * 0.75f;
    label.setBounds(labelX, labelY, labelWidth, labelHeight);
  }

  juce::Slider slider;
private:
  juce::Label label;
  KnobLookAndFeel knobLookAndFeel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
};
}
