#pragma once

#include "../controls/Button.h"
#include "../controls/Group.h"
#include "../controls/Knob.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

namespace Gui {
class DelayComponent : public juce::Component {
public:
  DelayComponent(juce::AudioProcessorValueTreeState &parameters)
      : parameters(parameters),
        group("Delay"),
        delay("Delay", ParamRange::delayStart, ParamRange::delayEnd,
              ParamRange::delayInterval, ParamRange::delayDefault),
        feedback("Feedback", ParamRange::feedbackStart, ParamRange::feedbackEnd,
                 ParamRange::feedbackInterval, ParamRange::feedbackDefault),
        invPolarity("Invert Polarity", ParamIDs::invertPolarity),
        invWet("Invert Wet", ParamIDs::invertWet)
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

    setBufferedToImage(true);
  }

  void paint(juce::Graphics &g) override {
    g.setColour(Colours::primaryColour);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), Layout::radius);
  }

  void resized() override {
    auto area = getLocalBounds();
    group.setBounds(-10, 1, area.getWidth(), area.getHeight());

    int topPadding = 5;
    area = area.withTrimmedTop(topPadding);

    auto componentWidth = area.proportionOfWidth(0.25f);
    auto componentArea = area;

    delay.setBounds(componentArea.removeFromLeft(componentWidth).reduced(5));
    invWet.setBounds(componentArea.removeFromLeft(componentWidth).reduced(5));
    feedback.setBounds(componentArea.removeFromLeft(componentWidth).reduced(5));
    invPolarity.setBounds(componentArea.removeFromLeft(componentWidth).reduced(5));
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
}
