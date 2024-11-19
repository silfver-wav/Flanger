#pragma once

#include "PluginProcessor.h"

class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
  ~AudioPluginAudioProcessorEditor() override;

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  AudioPluginAudioProcessor &processorRef;

  // Labels
  juce::Label nrStagesLabel;
  juce::Label spreadLabel;
  juce::Label centerLabel;
  juce::Label feedbackLabel;
  juce::Label invertPolarityLabel;
  juce::Label depthLabel;
  juce::Label lfoFreqLabel;
  juce::Label lfoDepthLabel;
  juce::Label stereoLabel;
  juce::Label gainLabel;

  // Sliders
  juce::Slider nrStagesSlider;
  juce::Slider spreadSlider;
  juce::Slider centerSlider;
  juce::Slider feedbackSlider;
  juce::Slider depthSlider;
  juce::Slider lfoFreqSlider;
  juce::Slider lfoDepthSlider;
  juce::Slider stereoSlider;
  juce::Slider gainSlider;

  // Attachments
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      nrStagesAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      spreadAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      centerAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      feedbackAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
      invertPolarityAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      depthAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      lfoFreqAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      lfoDepthAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      stereoAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>
      bypassAttachment;
  std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
      gainAttachment;

  // Buttons
  juce::ToggleButton invertPolarityButton;
  juce::ToggleButton bypassButton;

  void initGUI();

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
