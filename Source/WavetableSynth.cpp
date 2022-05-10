/*
  ==============================================================================

    WavetableSynth.cpp
    Created: 9 May 2022 3:54:28pm
    Author:  Enrico Damiani

  ==============================================================================
*/

#include "WavetableSynth.h"

void WavetableSynth::prepareToPlay(double sampleRate) 
{
    this->sampleRate = sampleRate;

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

    }
    else if (midiEvent.isAllNotesOff())
    {

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