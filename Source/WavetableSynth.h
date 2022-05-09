/*
  ==============================================================================

    WavetableSynth.h
    Created: 9 May 2022 3:54:28pm
    Author:  Enrico Damiani

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WavetableSynth
{
public:
    void prepareToPlay(double sampleRate);
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    float midiNoteNumberToFrequency(int midiNoteNumber);

    double sampleRate;
};