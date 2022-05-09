/*
  ==============================================================================

    Synth.cpp
    Created: 2 May 2022 1:11:44pm
    Author:  enric

  ==============================================================================
*/

#include "Synth.h"

bool Synth::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}


void Synth::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
               int currentPitchWheelPosition)
{

}


void Synth::stopNote(float velocity, bool allowTailOff)
{

}


void Synth::controllerMoved(int controllerNumber, int newControllerValue)
{

}


void Synth::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample,
                     int numSamples)
{

}