#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class VisualComponent : public juce::Component {
public:
  VisualComponent() {

  }

  void paint (juce::Graphics& g) override {
    g.fillAll (juce::Colours::blueviolet);
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualComponent)
};
