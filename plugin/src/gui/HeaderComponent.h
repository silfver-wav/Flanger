#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class HeaderComponent : public juce::Component {
public:
  HeaderComponent() {}

  void paint (juce::Graphics& g) override {
    g.fillAll (juce::Colours::lightblue);
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};