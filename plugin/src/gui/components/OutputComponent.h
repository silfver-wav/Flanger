#pragma once

#include "../controls/Group.h"
#include "../controls/Knob.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

namespace Gui {
class OutputComponent : public juce::Component {
public:
  OutputComponent(juce::AudioProcessorValueTreeState &parameters)
      : parameters(parameters),
        group("Output"),
        saturation("Saturation", ParamRange::saturationStart, ParamRange::saturationEnd, ParamRange::saturationInterval, ParamRange::saturationDefault),
        mix("Mix", ParamRange::mixStart, ParamRange::mixEnd, ParamRange::mixInterval, ParamRange::mixDefault),
        gain("Gain", ParamRange::gainStart, ParamRange::gainEnd, ParamRange::gainInterval, ParamRange::gainDefault)
  {
    addAndMakeVisible(group);
    addAndMakeVisible(saturation);
    addAndMakeVisible(mix);
    addAndMakeVisible(gain);

    saturationAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::saturation, saturation.slider);
    mixAttachment =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::mix, mix.slider);
    gainAttachment =
      std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(parameters, ParamIDs::gain, gain.slider);
  }

  void resized() override {
    auto area = getLocalBounds();
    group.setBounds(area.reduced(2));

    auto knobHeight = getLocalBounds().getHeight() / 3;
    saturation.setBounds(area.removeFromTop(knobHeight).reduced(10));
    mix.setBounds(area.removeFromTop(knobHeight).reduced(10));
    gain.setBounds(area.removeFromTop(knobHeight).reduced(10));
  }

private:
  juce::AudioProcessorValueTreeState &parameters;
  Group group;

  Knob saturation;
  Knob mix;
  Knob gain;

  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      saturationAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      mixAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
    gainAttachment;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OutputComponent)
};
}