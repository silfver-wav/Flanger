#include "LFO.h"

LFO::LFO() {
  // Constructor definition
}

LFO::~LFO() {
  // Destructor definition
}

void LFO::prepare(float newSampleRate) {
  sampleRate = newSampleRate;
  phase.reset();
}

float LFO::processSample(float input) {
  // Calculate the phase increment based on the LFO frequency and sample rate
  auto phaseIncrement =
      juce::MathConstants<float>::twoPi * frequency.getNextValue() / sampleRate;

  // Advance the phase and apply the phase offset, then center it around -pi to
  // pi
  float currentPhase = phase.advance(phaseIncrement) -
                       juce::MathConstants<float>::pi; // + phaseOffset;

  // Calculate the LFO value (output of the oscillator)
  float lfoValue = 0.f;
  switch (waveform) {
  case Waveform::SINE:
    lfoValue = std::sin(currentPhase);
    break;
  case Waveform::TRIANGLE:
    // TODO: make triangle code
    break;
  case Waveform::SQUARE:
    // TODO: make square code
    break;
  }

  return input + depth * lfoValue;
}

