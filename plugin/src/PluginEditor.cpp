#include "PluginEditor.h"
#include "PluginProcessor.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p) {

  processorRef.gainMeter.setImagesCount(46);
  processorRef.gainMeter.setImagesBounds(128);
  processorRef.gainMeter.setRelease(.5f);

  processorRef.gainMeter.setImages(
      3, 3, 1, 2056, 256.f, 24.f, .3f, 1.f, 3.f, 1.f,
      juce::Colours::blue.withAlpha(.1f), juce::Colours::white.withAlpha(.5f),
      juce::Colours::transparentBlack, juce::Colours::blue.withAlpha(0.5f));

  auto x = 1.f;
  auto y = .7f;
  auto scale = 800.f;
  setSize(int(x * scale), int(y * scale));
  auto fps = 24.f;
  startTimer(int(1000.f / fps));
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::black);
  g.setImageResamplingQuality(juce::Graphics::mediumResamplingQuality);
  processorRef.gainMeter.draw(g, getLocalBounds().toFloat());
}

void AudioPluginAudioProcessorEditor::resized() {

}

void AudioPluginAudioProcessorEditor::timerCallback() {
  if (processorRef.gainMeter.shouldRepaint())
    repaint();
}


