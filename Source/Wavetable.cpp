/*
  ==============================================================================

    Wavetable.cpp
    Created: 9 May 2022 10:00:45pm
    Author:  Enrico Damiani

  ==============================================================================
*/

#include "Wavetable.h"


WavetableOscillator::WavetableOscillator(std::vector<float> waveTable, double sampleRate)
    : waveTable { std::move(waveTable)},
      sampleRate {sampleRate}
{
    
}

void WavetableOscillator::setFrequency(float frequency)
{
    indexIncrement = frequency * static_cast<float>(waveTable.size()) / 
                        static_cast<float>(sampleRate);
}

float WavetableOscillator::getSample()
{

}