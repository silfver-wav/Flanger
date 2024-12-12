#pragma once


#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>

class VisualComponent : public juce::Component, public juce::Timer {
public:
  VisualComponent(AudioPluginAudioProcessor &p) : processorRef(p) {
    processorRef.gainMeter.initImages(46, 400);
    processorRef.gainMeter.setRelease(.5f);
    processorRef.gainMeter.setImages(opts);

    auto fps = 24.f;
    startTimer(static_cast<int>(1000.f / fps));
  }

  void paint (juce::Graphics& g) override {
    g.fillAll (juce::Colours::black);
    g.setImageResamplingQuality(juce::Graphics::lowResamplingQuality);
    processorRef.gainMeter.draw(g, getLocalBounds().toFloat());
  }

  void timerCallback() override {
    if (processorRef.gainMeter.shouldRepaint())
      // TODO: change the colour depending on parameter input
      repaint();
  }

private:
  AudioPluginAudioProcessor &processorRef;
  GainMeterSpirograph::ImageOptions opts = {
    3,
    3,
    1,
    2056,
    256.f,
    24.f,
    .3f,
    1.f,
    3.f,
    1.f,
    Colours::secondaryColour.withAlpha(.1f),
    juce::Colours::white.withAlpha(.5f),
    juce::Colours::transparentBlack,
    Colours::secondaryColour.withAlpha(0.5f),
  };
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualComponent)
};
