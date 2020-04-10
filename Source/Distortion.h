/*
  ==============================================================================

    Distortion.h
    Created: 20 Feb 2020 4:15:35pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Distortion
{
public:
    Distortion() {}
    
    Distortion (float input, float output)
    {
        mInput = input;
        mOutput = output;
    }
    
    void setParameters (float input, float output)
    {
        mInput = input;
        mOutput = output;
    }
    
    /**
        Algorithms to add:
            x = in1;                        // -1..1
            amount = in2;                   // -1..1
            k = 2*amount/(1-amount);
            out1 = (1+k)*x/(1+k*abs(x));
     */

    void processBuffer (AudioBuffer<float>& buffer, int numChannels, int channelIdx)
    {
        genDist (buffer, numChannels, channelIdx);
    }
    
    void genDist (AudioBuffer<float>& buffer, int numChannels, int channelIdx)
    {
        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            auto* writePtr = buffer.getWritePointer(channelIdx, sample);
            auto amount = mInput;
            auto k = 2 * amount / (1 - amount);
            *writePtr = ((1 + k) * *writePtr / (1 + k * std::abs(*writePtr))) * mOutput;
        }
    }
    
private:
    float mInput;
    float mOutput;
};
