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
    Distortion();
    Distortion (float input, float output);
    
    void setParameters (float input, float output);
    void processBuffer (AudioBuffer<float>& buffer, int numChannels, int channelIdx);
    
protected:
    void genDist (AudioBuffer<float>& buffer, int numChannels, int channelIdx);
    
// ==============================================================================
private:
    float mInput;
    float mOutput;
};
