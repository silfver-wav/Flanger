#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class TransparentComboBoxLookAndFeel : public juce::LookAndFeel_V4 {
public:
  void drawComboBox (juce::Graphics &g, int width, int height, bool isButtonDown,
                     int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox &box) override {
    /*
    g.setColour (juce::Colours::transparentBlack); // Transparent background
    g.fillRect (0, 0, width, height);


    // g.setFont (box.getFont());
    g.drawText (box.getText(), box.getLocalBounds().reduced(5, 0), juce::Justification::centredLeft, true);
    */
    // Draw the outline of the ComboBox
    auto cornerSize = box.findParentComponentOfClass<juce::ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
    juce::Rectangle<int> boxBounds (0, 0, width, height);

    g.setColour (juce::Colours::transparentBlack);
    g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

    g.setColour (juce::Colours::transparentBlack);
    g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);

    juce::Rectangle<int> arrowZone (width - 30, 0, 20, height);
    juce::Path path;
    path.startNewSubPath ((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
    path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
    path.lineTo ((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);

    g.setColour (juce::Colours::white); //.withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
    g.strokePath (path, juce::PathStrokeType (2.0f));
  }

  void drawPopupMenuItem (juce::Graphics &g, const juce::Rectangle<int> &area,
                          bool isSeparator, bool isActive, bool isHighlighted, bool isTicked,
                          bool hasSubMenu, const juce::String &text, const juce::String &shortcutKey,
                          const juce::Drawable *icon, const juce::Colour *textColour) override {
    if (isSeparator) return; // No separator

    auto colour = isHighlighted ? juce::Colours::lightgrey : juce::Colours::white;
    g.setColour(colour);
    g.setFont (14.0f);
    g.drawText (text, area.reduced(10, 0), juce::Justification::centredLeft, true);
  }

  void drawPopupMenuBackground (juce::Graphics &g, int width, int height) override {
    g.setColour(juce::Colours::black);
    g.fillRect(0, 0, width, height);
  }

  void drawComboBoxTextWhenNothingSelected (juce::Graphics& g, juce::ComboBox& box, juce::Label& label) override
  {
    g.setColour (juce::Colours::white);

    auto font = label.getLookAndFeel().getLabelFont (label);

    g.setFont (font);

    auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

    g.drawFittedText (box.getTextWhenNothingSelected(), textArea, label.getJustificationType(),
                      juce::jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                      label.getMinimumHorizontalScale());
  }
};
