#pragma once

#include <JuceHeader.h>
#include "Params.h"

namespace juce::dsp
{
    enum Waveform
    {
        SINE,
        TRIANGLE,
        SQUARE
    };

    class LFO
    {
    public:
        LFO();
        ~LFO();
        void prepare(float newSampleRate);
        float processSample(float input);

        void setFrequency(float newFrequency) noexcept
        {
            frequency.setTargetValue(newFrequency);
        }

        void setDepth(float newDepth)
        {
            depth = newDepth;
        }

        void setWaveform(Waveform newWaveform)
        {
            waveform = newWaveform;
        }

    private:
        float sampleRate;
        float depth = ParamRange::lfoDepthDefault;
        SmoothedValue<float> frequency{static_cast<float>(ParamRange::lfoFreqDefault)};
        Phase<float> phase;
        Waveform waveform = Waveform::SINE;
    };
}