#pragma once

#include "Button.h"
#include "Group.h"
#include "Knob.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class DelayComponent : public juce::Component {
public:
  DelayComponent(juce::AudioProcessorValueTreeState &parameters)
      : parameters(parameters),
        group("Delay"),
        delay("Delay", ParamRange::delayStart, ParamRange::delayEnd,
              ParamRange::delayInterval, ParamRange::delayDefault),
        feedback("Feedback", ParamRange::feedbackStart, ParamRange::feedbackEnd,
                 ParamRange::feedbackInterval, ParamRange::feedbackDefault),
        invPolarity("Invert Polarity"),
        invWet("Invert Wetness")
  {
    addAndMakeVisible(group);
    addAndMakeVisible(delay);
    addAndMakeVisible(feedback);
    addAndMakeVisible(invPolarity);
    addAndMakeVisible(invWet);

    delayAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::delay, delay.slider);
    feedbackAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::feedback, feedback.slider);
    invPolarityAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(parameters, ParamIDs::invertPolarity, invPolarity.button);
    invWetAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(parameters, ParamIDs::invertWet, invWet.button);
  }

  void resized() override {
    auto area = getLocalBounds();
    group.setBounds(area.reduced(2));

    auto knobWidth = getLocalBounds().getWidth() / 4;
    delay.setBounds(area.removeFromLeft(knobWidth).reduced(10));
    invWet.setBounds(area.removeFromLeft(knobWidth).reduced(10));
    feedback.setBounds(area.removeFromLeft(knobWidth).reduced(10));
    invPolarity.setBounds(area.removeFromLeft(knobWidth).reduced(10));
  }

private:
  juce::AudioProcessorValueTreeState &parameters;
  Group group;

  Knob delay;
  Knob feedback;
  Button invPolarity;
  Button invWet;

  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      delayAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      feedbackAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
    invPolarityAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
    invWetAttachment;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayComponent)
};
