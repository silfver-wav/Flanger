#include "CombFilter.h"

float CombFilter::process(const float &inputSample, float depth, float delay)
{
    // y(n) = x(n) + g x[n-M(n)]
    float outSample = inputSample + depth * delay;

    return outSample;
}