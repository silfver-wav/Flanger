#pragma once

#include <JuceHeader.h>
#include "Params.h"
#include "LFO.h"

namespace juce
{
    class Flanger : public AudioProcessorValueTreeState::Listener
    {
    public:
        Flanger(AudioProcessorValueTreeState &params);
        ~Flanger();
        void prepare(dsp::ProcessSpec &spec);
        void process(AudioBuffer<float> &buffer);

    private:
        AudioProcessorValueTreeState &parameters;

        LFO lfo;

        AudioBuffer<float> drySignal;
        std::vector<float> feedback;

        int numChannels = 0;
        float sampleRate = 44100.f;
        float minFreq = 20.f;
        float maxFreq = 20000.0f;
        float baseDelay = 2.f;

        void proccessBuuferThroughCombFilter(AudioBuffer<float> &buffer, int channel);
        void processMix(AudioBuffer<float> &buffer);

        void parameterChanged(const String &parameterID, float newValue);

        float getDelay()
        {
            return *parameters.getRawParameterValue(ParamIDs::delay);
        }

        float getDepth()
        {
            return *parameters.getRawParameterValue(ParamIDs::depth);
        }

        float getFeedback()
        {
            return *parameters.getRawParameterValue(ParamIDs::feedback);
        }

        bool getInvertPolarity()
        {
            return *parameters.getRawParameterValue(ParamIDs::invertPolarity);
        }

        bool getBypass()
        {
            return *parameters.getRawParameterValue(ParamIDs::bypass);
        }

        float getLFOFreq()
        {
            return *parameters.getRawParameterValue(ParamIDs::lfoFreq);
        }

        float getLFODepth()
        {
            return *parameters.getRawParameterValue(ParamIDs::lfoDepth);
        }

        float getAmountOfStereo()
        {
            return *parameters.getRawParameterValue(ParamIDs::stereo);
        }

        float getMix()
        {
            return *parameters.getRawParameterValue(ParamIDs::mix);
        }

        float getGain()
        {
            float gainDB = *parameters.getRawParameterValue(ParamIDs::gain);
            return Decibels::decibelsToGain(gainDB);
        }
    };
}