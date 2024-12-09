#include "PluginEditor.h"
#include "PluginProcessor.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p) {


  addAndMakeVisible (headerComponent);
  addAndMakeVisible(footerComponent);
  addAndMakeVisible(visualComponent);
  addAndMakeVisible(outputComponent);
  addAndMakeVisible(delayComponent);
  addAndMakeVisible(lfoComponent);

  processorRef.gainMeter.initImages(46, 800);
  processorRef.gainMeter.setRelease(.5f);

  processorRef.gainMeter.setImages(
      3, 3, 1, 2056, 256.f, 24.f, .3f, 1.f, 3.f, 1.f,
      juce::Colours::blue.withAlpha(.1f), juce::Colours::white.withAlpha(.5f),
      juce::Colours::transparentBlack, juce::Colours::blue.withAlpha(0.5f));

  auto width = 800;
  auto height = 560;
  setSize(width, height);
  auto fps = 24.f;
  startTimer(static_cast<int>(1000.f / fps));

  // gainSlider("a gain slider", processorRef.parameters.getParameter(ParamIDs::gain));
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::black);
  g.setImageResamplingQuality(juce::Graphics::lowResamplingQuality);
  processorRef.gainMeter.draw(g, getLocalBounds().toFloat());
}

void AudioPluginAudioProcessorEditor::resized() {
  auto area = getLocalBounds();
  auto headerFooterHeight = 36;
  headerComponent.setBounds (area.removeFromTop    (headerFooterHeight));
  footerComponent.setBounds (area.removeFromBottom (headerFooterHeight));

  auto sideBarArea = area.removeFromRight (juce::jmax (80, area.getWidth() / 4));
  outputComponent.setBounds (sideBarArea);

  auto contentItemHeight = 230;
  visualComponent.setBounds     (area.removeFromTop (contentItemHeight));
  delayComponent.setBounds (area.removeFromBottom (130));
  lfoComponent.setBounds (area.removeFromTop (130));
}

void AudioPluginAudioProcessorEditor::timerCallback() {
  if (processorRef.gainMeter.shouldRepaint())
    repaint();
}


