#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "utils/Utils.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p),
    processorRef(p),
    topComponent(p.parameters, p.getPresetManger(), p.getGainMeter()),
    outputComponent(p.parameters),
    delayComponent(p.parameters),
    lfoComponent(p.parameters)
{
  addAndMakeVisible (topComponent);
  addAndMakeVisible(outputComponent);
  addAndMakeVisible(delayComponent);
  addAndMakeVisible(lfoComponent);

  setResizable(true, true);
  setResizeLimits(600, 400, 2000, 1600);
  // getConstrainer()->setFixedAspectRatio(2.0f);
  setSize(1000, 800);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
  g.fillAll(Colours::primaryColour.brighter(0.35f));
}

void AudioPluginAudioProcessorEditor::resized() {
  auto area = getLocalBounds();
  topComponent.setBounds(area.removeFromTop(area.proportionOfHeight(0.5f)));

  auto bottomArea = area.reduced(Layout::padding);
  auto outputArea = bottomArea.removeFromRight(bottomArea.proportionOfWidth(0.2f));
  outputComponent.setBounds(outputArea.reduced(Layout::padding));
  delayComponent.setBounds(bottomArea.removeFromTop(bottomArea.proportionOfHeight(0.5f)).reduced(Layout::padding));
  lfoComponent.setBounds(bottomArea.reduced(Layout::padding));
}


