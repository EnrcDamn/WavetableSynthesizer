/*
  ==============================================================================

    WavetableSynth.cpp
    Created: 9 May 2022 3:54:28pm
    Author:  Enrico Damiani

  ==============================================================================
*/


#include "WavetableSynth.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    const auto frequency = midiNoteNumberToFrequency(midiNoteNumber);
    osc.setFrequency(frequency);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    osc.stop();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::prepare(double sampleRate, int samplesPerBlock, int outputChannel)
{
    // clear oscillators first
    osc.initializeOscillators();
    osc.setSampleRate(sampleRate);
}


void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

}


float SynthVoice::midiNoteNumberToFrequency(int midiNoteNumber)
{
    constexpr auto A4_FREQUENCY = 440.f;
    constexpr auto A4_NOTE_NUMBER = 69.f;
    constexpr auto SEMITONES_IN_AN_OCTAVE = 12.f;
    // difference in semitones: 2 ^ (abs difference between midi note and A4) / semitones
    return A4_FREQUENCY * std::powf(2.f, (midiNoteNumber - A4_NOTE_NUMBER) / SEMITONES_IN_AN_OCTAVE);
}

//==================================================================================





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
        render(buffer, currentSample, midiEventSample);
        handleMidiEvent(midiEvent);
        currentSample = midiEventSample;
    }
    // last cycle: buf[currentSample] -> buf[-end-]
    render(buffer, currentSample, buffer.getNumSamples());
}
 

void WavetableSynth::render(juce::AudioBuffer<float>& buffer, 
    int startSample, int endSample)
{
    auto* firstChannel = buffer.getWritePointer(0);
    for (auto& oscillator : oscillators)
    {
        if (oscillator.isPlaying())
        {
            for (auto sample = startSample; sample < endSample; ++sample)
            {
                firstChannel[sample] += oscillator.getSample();
            }
        }
    }

    for (auto channel = 1; channel < buffer.getNumChannels(); ++channel)
    {
        std::copy(firstChannel + startSample, firstChannel + endSample, buffer.getWritePointer(channel) + startSample);
    }
}


void WavetableSynth::handleMidiEvent(const juce::MidiMessage& midiEvent)
{
    if (midiEvent.isNoteOn())
    {
        
    }
    else if (midiEvent.isNoteOff())
    {
        
    }
    else if (midiEvent.isAllNotesOff())
    {
        
    }
}

