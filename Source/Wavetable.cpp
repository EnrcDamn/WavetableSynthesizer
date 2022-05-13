/*
  ==============================================================================

    Wavetable.cpp
    Created: 9 May 2022 10:00:45pm
    Author:  Enrico Damiani

  ==============================================================================
*/

#include "Wavetable.h"
//#include <cmath>

WavetableOscillator::WavetableOscillator(std::vector<float> waveTable, double sampleRate)
    : waveTable { std::move(waveTable)},
      sampleRate {sampleRate}
{
    
}

void WavetableOscillator::setSampleRate(double newRate)
{
    sampleRate = newRate;
}


void WavetableOscillator::initializeOscillators()
{
    const auto waveTable = generateSineWaveTable();
}

std::vector<float> WavetableOscillator::generateSineWaveTable()
{
    constexpr auto WAVETABLE_LENGTH = 64;

    std::vector<float> sineWaveTable(WAVETABLE_LENGTH);

    for (auto i = 0; i < WAVETABLE_LENGTH; ++i)
    {
        sineWaveTable[i] = std::sinf(2.f * juce::float_Pi *
            static_cast<float>(i) / static_cast<float>(WAVETABLE_LENGTH));
    }
    return sineWaveTable;
}




void WavetableOscillator::setFrequency(float frequency)
{
    indexIncrement = frequency * static_cast<float>(waveTable.size()) / 
                        static_cast<float>(sampleRate);
}

float WavetableOscillator::getSample()
{
    // get one sample of the wavetable and increment index
    const auto sample = linearInterpolation();
    index += indexIncrement;
    index = fmod(index, static_cast<float> (waveTable.size()));
    return sample;
}

float WavetableOscillator::linearInterpolation()
{
    const auto truncatedIndex = static_cast<int>(index);
    const auto nextIndex = (truncatedIndex + 1) % static_cast<int>(waveTable.size());

    const auto nextIndexWeight = index - static_cast<float>(truncatedIndex);
    const auto truncatedIndexWeight = 1.f - nextIndexWeight;

    return truncatedIndexWeight * waveTable[truncatedIndex] +
        nextIndexWeight * waveTable[nextIndex];
}

void WavetableOscillator::stop()
{
    index = 0.f;
    indexIncrement = 0.f;
}

bool WavetableOscillator::isPlaying()
{
    // check if oscillator is playing
    return indexIncrement != 0.f;
}