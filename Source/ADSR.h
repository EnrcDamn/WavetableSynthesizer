/*
  ==============================================================================

    ADSR.h
    Created: 13 May 2022 6:22:16pm
    Author:  Enrico Damiani

  ==============================================================================
*/

#pragma once

class ADSREnv {

public:
    double adsr(double input, int trigger);
    double input;
    double output;
    double attack;
    double decay;
    double sustain;
    double release;
    double amplitude;
    void setAttack(double attackMS);
    void setDecay(double decayMS);
    void setSustain(double sustainL);
    void setRelease(double releaseMS);
    int trigger;
    long holdTime = 1;
    long holdCount;
    int attackPhase, decayPhase, sustainPhase, holdPhase, releasePhase;
};
