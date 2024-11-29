#pragma once

#include "PluginProcessor.h"
#include <juce_graphics/juce_graphics.h>

class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor, public juce::Timer {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;
    void timerCallback() override;

private:
  AudioPluginAudioProcessor &processorRef;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
