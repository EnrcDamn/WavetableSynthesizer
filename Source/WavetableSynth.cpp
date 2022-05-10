/*
  ==============================================================================

    WavetableSynth.cpp
    Created: 9 May 2022 3:54:28pm
    Author:  Enrico Damiani

  ==============================================================================
*/


#include "WavetableSynth.h"


std::vector<float> WavetableSynth::generateSineWaveTable()
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


void WavetableSynth::initializeOscillators()
{
    // 128 as the midi notes number
    constexpr auto OSCILLATORS_COUNT = 128;
    const auto waveTable = generateSineWaveTable();

    // clear oscillators first
    oscillators.clear();
    for (auto i = 0; i < OSCILLATORS_COUNT; ++i)
    {
        oscillators.emplace_back(waveTable, sampleRate);
    }
}

void WavetableSynth::prepareToPlay(double sampleRate) 
{
    this->sampleRate = sampleRate;
    initializeOscillators();
}


void WavetableSynth::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Top-down approach: read midi messages and render audio inbetween
    auto currentSample = 0;

    for (const auto midiMessage : midiMessages) 
    {
        // get message from midiBuffer class
        const auto midiEvent = midiMessage.getMessage();
        // get the sample at which the midi event happened
        const auto midiEventSample = static_cast<int>(midiEvent.getTimeStamp());

        // Render everything from buf[0] -> buf[midiEventSample]
        // TODO: implement render()
        render(buffer, currentSample, midiEventSample);
        handleMidiEvent(midiEvent);
        currentSample = midiEventSample;
    }
    // last cycle: buf[currentSample] -> buf[-end-]
    render(buffer, currentSample, buffer.getNumSamples());
}

void WavetableSynth::handleMidiEvent(const juce::MidiMessage& midiEvent)
{
    if (midiEvent.isNoteOn())
    {
        const auto oscillatorId = midiEvent.getNoteNumber();
        const auto frequency = midiNoteNumberToFrequency(oscillatorId);
        oscillators[oscillatorId].setFrequency(frequency);
    }
    else if (midiEvent.isNoteOff())
    {
        const auto oscillatorId = midiEvent.getNoteNumber();
        oscillators[oscillatorId].stop();
    }
    else if (midiEvent.isAllNotesOff())
    {
        for (auto& oscillator : oscillators)
        {
            oscillator.stop();
        }
    }
}

float WavetableSynth::midiNoteNumberToFrequency(int midiNoteNumber)
{
    constexpr auto A4_FREQUENCY = 440.f;
    constexpr auto A4_NOTE_NUMBER = 69.f;
    constexpr auto SEMITONES_IN_AN_OCTAVE = 12.f;
    // difference in semitones: 2 ^ (abs difference between midi note and A4) / semitones
    return A4_FREQUENCY * std::powf(2.f, (midiNoteNumber - A4_NOTE_NUMBER) / SEMITONES_IN_AN_OCTAVE);
}