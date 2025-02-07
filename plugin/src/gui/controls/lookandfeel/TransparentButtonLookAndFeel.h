#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace Gui {
class TransparentButtonLookAndFeel : public juce::LookAndFeel_V4 {

  void drawButtonText(juce::Graphics &g, juce::TextButton &button,
                      bool isMouseOverButton, bool isButtonDown) override {
    g.setColour(juce::Colours::white);
    juce::Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);
    g.drawText(button.getButtonText(), button.getLocalBounds(),
               juce::Justification::centred, true);
  }

};
}