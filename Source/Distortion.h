/*
  ==============================================================================

    Distortion.h
    Created: 20 Feb 2020 4:15:35pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

class Distortion
{
public:
    Distortion() {}
    ~Distortion() {}
    
    Distortion(float input, float drive, float output)
    {
        mInput = input;
        mDrive = drive;
        mOutput = output;
    }
    
    void setParameters(float input, float drive, float output)
    {
        mInput = input;
        mDrive = drive;
        mOutput = output;
    }

    void processBuffer(AudioBuffer<float>& buffer, int numChannels, int channelIdx)
    {
        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            auto* writePtr = buffer.getWritePointer(channelIdx, sample);
            *writePtr *= (mInput * mDrive);
            *writePtr = ((2.f / float_Pi) * std::atan(*writePtr)) * mOutput;
            buffer.addSample(channelIdx, sample, *writePtr);
        }
    }
    
private:
    float mInput;
    float mDrive;
    float mOutput;
};
