/*
  ==============================================================================

    WavetableSynth.h
    Created: 9 May 2022 3:54:28pm
    Author:  Enrico Damiani

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>
#include "Wavetable.h"

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};

//=====================================================================

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

};

//=====================================================================

class WavetableSynth
{
public:
    void prepareToPlay(double sampleRate);
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
    void initializeOscillators();
    std::vector<float> generateSineWaveTable();
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    float midiNoteNumberToFrequency(int midiNoteNumber);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);

    double sampleRate;
    std::vector<WavetableOscillator> oscillators;
};