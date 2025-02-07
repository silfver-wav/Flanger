#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class TransparentComboBoxLookAndFeel : public juce::LookAndFeel_V4 {
public:
  /*
  void drawPopupMenuItem (juce::Graphics &g, const juce::Rectangle<int> &area,
                          bool isSeparator, bool isActive, bool isHighlighted, bool isTicked,
                          bool hasSubMenu, const juce::String &text, const juce::String &shortcutKey,
                          const juce::Drawable *icon, const juce::Colour *textColour) override {
    if (isSeparator) return; // No separator

    auto colour = isHighlighted ? juce::Colours::lightgrey : juce::Colours::white;
    g.setColour(colour);
    g.setFont (17.0f);
    g.drawText (text, area.reduced(10, 0), juce::Justification::centredLeft, true);
  }

  void drawPopupMenuBackground (juce::Graphics &g, int width, int height) override {
    g.setColour(juce::Colours::black);
    g.fillRect(0, 0, width, height);
  }
  */
  void drawComboBoxTextWhenNothingSelected (juce::Graphics& g, juce::ComboBox& box, juce::Label& label) override
  {
    g.setColour (juce::Colours::white);

    auto font = label.getLookAndFeel().getLabelFont (label);
    g.setFont (font); // Ensure font size matches selected items

    // Get the text area with proper vertical centering
    auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

    // Adjust vertical alignment (move text slightly down)
    textArea.translate(0, 1); // Moves text 2 pixels down

    g.drawFittedText (box.getTextWhenNothingSelected(), textArea, juce::Justification::centredLeft,
                      juce::jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                      label.getMinimumHorizontalScale());
  }
};
