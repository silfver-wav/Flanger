#pragma once

#include "Knob.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class DelayComponent : public juce::Component {
public:
  DelayComponent(juce::AudioProcessorValueTreeState &parameters)
      : parameters(parameters),
        delay("Delay", ParamRange::delayStart, ParamRange::delayEnd, ParamRange::delayInterval, ParamRange::delayDefault),
        feedback("Feedback", ParamRange::feedbackStart, ParamRange::feedbackEnd, ParamRange::feedbackInterval, ParamRange::feedbackDefault)
  {
    addAndMakeVisible(delay);
    addAndMakeVisible(feedback);

    delayAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::delay, delay.slider);
    feedbackAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::feedback, feedback.slider);
  }

  void paint(juce::Graphics &g) override {
    g.fillAll(juce::Colours::cadetblue);
  }

  void resized() override {
    auto area = getLocalBounds();
    auto knobWidth = getLocalBounds().getWidth() / 2;

    delay.setBounds(area.removeFromLeft(knobWidth).reduced(10));
    feedback.setBounds(area.reduced(10));
  }

private:
  juce::AudioProcessorValueTreeState &parameters;
  // Knobs
  Knob delay;
  Knob feedback;

  /*
  // Buttons
  juce::ToggleButton invertPolarityButton;
  juce::ToggleButton invertWetButton;

  // Labels
  juce::Label invertPolarityLabel;
  juce::Label invertWetLabel;
  */

  // Attachments
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      delayAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      feedbackAttachment;
  // std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
  // invertPolarityAttachment;
  // std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
  // invertWetAttachment;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayComponent)
};
