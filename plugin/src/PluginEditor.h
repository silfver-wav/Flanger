#pragma once

#include "PluginProcessor.h"
#include "gui/components/OutputComponent.h"
#include "gui/components/DelayComponent.h"
#include "gui/components/HeaderComponent.h"
#include "gui/components/LFOComponent.h"
#include "gui/components/VisualComponent.h"

#include <juce_graphics/juce_graphics.h>


class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
  AudioPluginAudioProcessor &processorRef;
  Gui::HeaderComponent headerComponent;
  Gui::VisualComponent visualComponent;
  Gui::OutputComponent outputComponent;
  Gui::DelayComponent delayComponent;
  Gui::LFOComponent lfoComponent;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
