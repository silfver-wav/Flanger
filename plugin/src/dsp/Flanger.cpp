#include "Flanger.h"

Flanger::Flanger(juce::AudioProcessorValueTreeState &params) : parameters(params) {
  parameters.addParameterListener(ParamIDs::lfoFreq, this);
  parameters.addParameterListener(ParamIDs::lfoDepth, this);
  // waveform shape
}

Flanger::~Flanger() {
  parameters.removeParameterListener(ParamIDs::lfoFreq, this);
  parameters.removeParameterListener(ParamIDs::lfoDepth, this);
  // waveform shape
}

void Flanger::prepare(juce::dsp::ProcessSpec &spec) {
  sampleRate = static_cast<float>(spec.sampleRate);
  numChannels = spec.numChannels;

  lfo.prepare(sampleRate);

  drySignal.setSize(numChannels, spec.maximumBlockSize);
}

void Flanger::process(juce::AudioBuffer<float> &buffer) {
  if (getBypass())
    return;

  for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
    drySignal.copyFrom(channel, 0, buffer.getReadPointer(channel),
                       buffer.getNumSamples());
    processBufferThroughCombFilter(buffer, channel);
  }

  processMix(buffer);

  buffer.applyGain(getGain());
}

void Flanger::processMix(juce::AudioBuffer<float> &buffer) {
  float gain = 1 - getMix();
  buffer.applyGain(getMix());

  for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
    buffer.addFromWithRamp(channel, 0, drySignal.getReadPointer(channel),
                           drySignal.getNumSamples(), gain, gain);
  }
}

void Flanger::processBufferThroughCombFilter(juce::AudioBuffer<float> &buffer,
                                              int channel) {
  const float *inputSamples = buffer.getReadPointer(channel);
  float *outputSamples = buffer.getWritePointer(channel);

  float amountOfFeedback = getFeedback();
  float phaseOffset = (channel == 1)
                          ? juce::MathConstants<float>::halfPi * getAmountOfStereo()
                          : 0.0f;

  for (int sampleIndex = 0; sampleIndex < buffer.getNumSamples();
       sampleIndex++) {
    // Calculate the feedback input if feedback is used
    float feedbackInput =
        feedback[channel] * amountOfFeedback * (getInvertPolarity() ? -1 : 1);
    float inputSample = inputSamples[sampleIndex] + feedbackInput;

    // Get the LFO value for delay modulation
    float lfoValue = lfo.processSample(phaseOffset);
    float delayLine = baseDelay * (1.0f + lfoValue);

    // y(n) = x(n) + g x[n-M(n)]
    inputSample = inputSample + getDepth() * delayLine;

    outputSamples[sampleIndex] = inputSample;
    feedback[channel] = inputSample;
  }
}

//==============================================================================

void Flanger::parameterChanged(const juce::String &parameterID, float newValue) {
  if (parameterID == ParamIDs::lfoFreq) {
    lfo.setFrequency(newValue);
  } else if (parameterID == ParamIDs::lfoDepth) {
    lfo.setDepth(newValue);
  }
}
