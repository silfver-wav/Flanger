#include "TapeSaturation.h"

namespace DSP {
TapeSaturation::TapeSaturation(juce::AudioProcessorValueTreeState &params)
    : parameters(params) {
  parameters.addParameterListener(ParamIDs::saturation, this);
  dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear);
}

TapeSaturation::~TapeSaturation() {
  parameters.removeParameterListener(ParamIDs::saturation, this);
}

void TapeSaturation::prepare(juce::dsp::ProcessSpec &spec) {
  jassert(spec.sampleRate > 0);
  jassert(spec.numChannels > 0);

  dryWet.prepare(spec);
  dryWet.reset();

  dryWet.setWetMixProportion(getSaturation());
}

void TapeSaturation::parameterChanged(const juce::String &parameterID,
                                      float newValue) {
  if (parameterID == ParamIDs::saturation) {
    dryWet.setWetMixProportion(newValue);
  }
}

}
