#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class OutputComponent : public juce::Component {
public:
  OutputComponent() {}

  void paint (juce::Graphics& g) override {
    g.fillAll (juce::Colours::darkgoldenrod);
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OutputComponent)
};
