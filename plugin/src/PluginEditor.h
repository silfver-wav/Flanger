#pragma once

#include "PluginProcessor.h"
#include "gui/FooterComponent.h"
#include "gui/HeaderComponent.h"
#include "gui/LFOComponent.h"
#include "gui/OutputComponent.h"
#include "gui/VisualComponent.h"
#include "gui/components/DelayComponent.h"

#include <juce_graphics/juce_graphics.h>


class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
  AudioPluginAudioProcessor &processorRef;
  HeaderComponent headerComponent;
  FooterComponent footerComponent;
  VisualComponent visualComponent;
  OutputComponent outputComponent;
  DelayComponent delayComponent;
  LFOComponent lfoComponent;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
