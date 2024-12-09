#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class LFOComponent : public juce::Component {
public:
  LFOComponent() {}

  void paint (juce::Graphics& g) override {
    g.fillAll (juce::Colours::blanchedalmond);
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFOComponent)
};
