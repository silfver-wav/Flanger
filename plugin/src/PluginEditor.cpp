#include "PluginEditor.h"
#include "PluginProcessor.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p),
    processorRef(p),
    visualComponent(p),
    delayComponent(p.parameters),
    lfoComponent(p.parameters),
    outputComponent(p.parameters)
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
  g.fillAll(juce::Colour::fromRGB(55, 55, 55));
}

void AudioPluginAudioProcessorEditor::resized() {
  auto area = getLocalBounds();

  auto headerHeight = 36;
  headerComponent.setBounds(area.removeFromTop(headerHeight));

  auto sideBarArea = area.removeFromRight(juce::jmax(80, area.getWidth() / 4));
  outputComponent.setBounds(sideBarArea);

  auto remainingHeight = area.getHeight();
  auto visualHeight = juce::jmin(230, remainingHeight / 2);
  auto componentHeight = (remainingHeight - visualHeight) / 2;

  visualComponent.setBounds(area.removeFromTop(visualHeight));
  delayComponent.setBounds(area.removeFromTop(componentHeight));
  lfoComponent.setBounds(area);
}


