#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class DelayComponent : public juce::Component {
public:
  DelayComponent() {}

  void paint (juce::Graphics& g) override {
    g.fillAll (juce::Colours::cadetblue);
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayComponent)
};
