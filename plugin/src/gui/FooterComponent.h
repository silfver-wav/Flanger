#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class FooterComponent : public juce::Component {
public:
  FooterComponent() {}

  void paint (juce::Graphics& g) override {
    g.fillAll(juce::Colour::fromRGB(45, 35, 35));
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FooterComponent)
};
