/*
  ==============================================================================

    Wavetable.h
    Created: 9 May 2022 10:00:45pm
    Author:  Enrico Damiani

  ==============================================================================
*/

#pragma once

#include <vector>

class WavetableOscillator
{
public:
    WavetableOscillator(std::vector<float> waveTable, double sampleRate);

    void setFrequency(float frequency);
    float getSample();

private:
    std::vector<float> waveTable;
    double sampleRate;
    float index = 0.f;
    float indexIncrement = 0.f;
};