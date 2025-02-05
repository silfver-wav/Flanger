#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "utils/Colours.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p),
    processorRef(p),
    headerComponent(p.parameters, p.getPresetManger()),
    visualComponent(p.parameters, p.getGainMeter()),
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
  g.fillAll(juce::Colours::white);
}

void AudioPluginAudioProcessorEditor::resized() {
  auto area = getLocalBounds();
  auto topArea = area.removeFromTop(area.proportionOfHeight(0.5f));
  auto bottomArea = area;

  headerComponent.setBounds(topArea.removeFromTop(area.proportionOfHeight(0.1f)));
  visualComponent.setBounds(topArea);

  auto outputArea = bottomArea.removeFromRight(bottomArea.proportionOfWidth(0.2f));
  outputComponent.setBounds(outputArea);
  delayComponent.setBounds(bottomArea.removeFromTop(bottomArea.proportionOfHeight(0.5f)));
  lfoComponent.setBounds(bottomArea);
}


