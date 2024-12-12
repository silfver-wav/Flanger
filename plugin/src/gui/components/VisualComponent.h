#pragma once

#include <../../../../libs/juce/modules/juce_core/juce_core.h>
#include <../../../../libs/juce/modules/juce_graphics/juce_graphics.h>

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

    auto area = getLocalBounds().toFloat();
    constexpr float squareSize = 400.0f;
    auto gainMeterArea = juce::Rectangle<float>(
        area.getCentreX() - (squareSize / 2.0f),
        area.getCentreY() - (squareSize / 2.0f),
        squareSize,
        squareSize
    );

    processorRef.gainMeter.draw(g, gainMeterArea);
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
    juce::Colours::blue.withAlpha(.1f),
    juce::Colours::white.withAlpha(.5f),
    juce::Colours::transparentBlack,
    juce::Colours::blue.withAlpha(0.5f),
  };
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualComponent)
};
