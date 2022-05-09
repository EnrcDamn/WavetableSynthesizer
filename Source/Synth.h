/*
  ==============================================================================

    Synth.h
    Created: 2 May 2022 1:11:44pm
    Author:  enric

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Synth : public juce::SynthesiserSound,
              public juce::SynthesiserVoice
{
public: 
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber,
                   float velocity,
                   juce::SynthesiserSound* sound,
                   int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
                         int startSample,
                         int numSamples) override;
};