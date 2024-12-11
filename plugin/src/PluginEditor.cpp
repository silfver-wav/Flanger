#include "PluginEditor.h"
#include "PluginProcessor.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p),
    processorRef(p),
    visualComponent(p),
    delayComponent(p.parameters),
    lfoComponent(p.parameters)
{
  addAndMakeVisible (headerComponent);
  addAndMakeVisible(footerComponent);
  addAndMakeVisible(visualComponent);
  addAndMakeVisible(outputComponent);
  addAndMakeVisible(delayComponent);
  addAndMakeVisible(lfoComponent);

  setSize(1000, 800);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::black);
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

