#include "VisualComponent.h"

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace Gui {
VisualComponent::VisualComponent(juce::AudioProcessorValueTreeState &params, GainMeterSpirograph &gm) : parameters(params), gainMeter(gm) {
  gainMeter.initImages(46, 400);
  gainMeter.setRelease(.5f);
  mixValue = getMix();
  updateGainMeter();

  auto fps = 24.f;
  startTimer(static_cast<int>(1000.f / fps));
}

void VisualComponent::paint (juce::Graphics& g) {
  g.fillAll (juce::Colours::black);
  g.setImageResamplingQuality(juce::Graphics::lowResamplingQuality);

  auto area = getLocalBounds().toFloat();
  float squareSize = area.getHeight() - 5.0f;
  const auto gainMeterArea = juce::Rectangle(
      area.getCentreX() - (squareSize / 2.0f),
      area.getCentreY() - (squareSize / 2.0f),
      squareSize,
      squareSize
  );

  gainMeter.draw(g, gainMeterArea);
}

void VisualComponent::timerCallback() {
  if (gainMeter.shouldRepaint()) {
    const float newMix = getMix();
    if (std::abs(mixValue - newMix) > 0.1f) {
      DBG("Here i am");
      mixValue = newMix;
      updateGainMeter();
    }
    repaint();
  }
}

void VisualComponent::updateGainMeter() {
  const float alpha = mixValue * .1f;
  opts.spiroColourStart = juce::Colours::blue.withAlpha(alpha);
  opts.armsColourEnd = juce::Colours::blue.withAlpha(alpha / 2.0f);
  gainMeter.setImages(opts);
}
}