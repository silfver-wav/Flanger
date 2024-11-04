#pragma once

class CombFilter
{
public:
    CombFilter();
    ~CombFilter();
    float process(const float &inputSample, float depth, float delay);

private:
    /* data */
};
