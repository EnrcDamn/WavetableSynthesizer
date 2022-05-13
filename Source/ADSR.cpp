/*
  ==============================================================================

    ADSR.cpp
    Created: 13 May 2022 6:22:16pm
    Author:  Enrico Damiani

  ==============================================================================
*/

#include "ADSR.h"


double ADSREnv::adsr(double input, int trigger) 
{
    if (trigger == 1 && attackPhase != 1 && holdPhase != 1 && decayPhase != 1) 
    {
        holdCount = 0;
        decayPhase = 0;
        sustainPhase = 0;
        releasePhase = 0;
        attackPhase = 1;
    }

    if (attackPhase == 1) 
    {
        releasePhase = 0;
        amplitude += (1 * attack);
        output = input * amplitude;

        if (amplitude >= 1) 
        {
            amplitude = 1;
            attackPhase = 0;
            decayPhase = 1;
        }
    }


    if (decayPhase == 1) 
    {
        output = input * (amplitude *= decay);
        if (amplitude <= sustain) {
            decayPhase = 0;
            holdPhase = 1;
        }
    }

    if (holdCount < holdTime && holdPhase == 1) 
    {
        output = input * amplitude;
        holdCount++;
    }

    if (holdCount >= holdTime && trigger == 1) 
    {
        output = input * amplitude;
    }

    if (holdCount >= holdTime && trigger != 1) 
    {
        holdPhase = 0;
        releasePhase = 1;
    }

    if (releasePhase == 1 && amplitude > 0.) 
    {
        output = input * (amplitude *= release);
    }

    return output;
}


void ADSREnv::setAttack(double attackMS) 
{

}

void ADSREnv::setRelease(double releaseMS) 
{

}

void ADSREnv::setSustain(double sustainL) 
{
    
}

void ADSREnv::setDecay(double decayMS) 
{

}