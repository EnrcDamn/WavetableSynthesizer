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
    void pitchWheelMoved(int newPitchWheelValue) override;
    void setAllSampleRate(double rate)
    {
        osc.setSampleRate(rate);
        /*for (auto l : lfos)
            l->setSampleRate(rate);*/
        setCurrentPlaybackSampleRate(rate);
    }
    void prepare(double sampleRate, int samplesPerBlock, int outputChannel);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    float midiNoteNumberToFrequency(int midiNoteNumber);
   
private:
    WavetableOscillator osc;

};

//=====================================================================

class WavetableSynth : public juce::Synthesiser
{
public:
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);
    void setAllSampleRates(double rate)
    {
        setCurrentPlaybackSampleRate(rate);
        for (auto v : voices)
            v->setAllSampleRate(rate);
    }
    void prepare(double rate, int samplesPerBlock, int numChannels)
    {
        prepare(rate, samplesPerBlock, numChannels);
        for (auto v : voices)
        {
            v->prepare(rate, samplesPerBlock, numChannels);
        }

    }

private:
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);

    double sampleRate;
    std::vector<SynthVoice*> voices;
};