#pragma once

#include <../../../../libs/juce/modules/juce_core/juce_core.h>
#include <../../../../libs/juce/modules/juce_graphics/juce_graphics.h>

class HeaderComponent : public juce::Component {
public:
  HeaderComponent() {}

  void paint (juce::Graphics& g) override {
    g.fillAll(juce::Colour::fromRGB(35, 35, 35));
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
