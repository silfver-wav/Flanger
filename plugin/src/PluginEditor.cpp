#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "utils/Colours.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p),
    processorRef(p),
    visualComponent(p.parameters, p.gainMeter),
    delayComponent(p.parameters),
    lfoComponent(p.parameters),
    outputComponent(p.parameters)
{
  addAndMakeVisible (headerComponent);
  addAndMakeVisible(visualComponent);
  addAndMakeVisible(outputComponent);
  addAndMakeVisible(delayComponent);
  addAndMakeVisible(lfoComponent);

  setSize(1000, 800);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(Colours::primaryColour);
}

void AudioPluginAudioProcessorEditor::resized() {
  auto area = getLocalBounds();

  auto headerHeight = 36;
  headerComponent.setBounds(area.removeFromTop(headerHeight));

  auto sideBarArea = area.removeFromRight(juce::jmax(80, area.getWidth() / 4));
  outputComponent.setBounds(sideBarArea);

  auto remainingHeight = area.getHeight();
  auto visualHeight = juce::jmin(250, remainingHeight / 2);
  auto componentHeight = (remainingHeight - visualHeight) / 2;

  visualComponent.setBounds(area.removeFromTop(visualHeight));
  delayComponent.setBounds(area.removeFromTop(componentHeight));
  lfoComponent.setBounds(area);
}


