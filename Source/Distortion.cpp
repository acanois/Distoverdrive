/*
  ==============================================================================

    Distortion.cpp
    Created: 20 Jun 2020 11:30:34pm
    Author:  David Richter

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion() {}

Distortion::Distortion (float input, float output)
{
    mInput = input;
    mOutput = output;
}

void Distortion::setParameters (float input, float output)
{
    mInput = input;
    mOutput = output;
}

// Algorithms are in a separate methods to allow for selectable algorithms later on
void Distortion::processBuffer (AudioBuffer<float>& buffer, int numChannels, int channelIdx)
{
    genDist (buffer, numChannels, channelIdx);
}

void Distortion::genDist (AudioBuffer<float>& buffer, int numChannels, int channelIdx)
{
    /** COPY PASTED GENEXPR FROM MAX
       Algorithms to add:
           x = in1;                        // -1..1
           amount = in2;                   // -1..1
           k = 2 * amount / (1 - amount);
           out1 = (1 + k) * x / (1 + k * abs(x));
    */
    for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        auto* writePtr = buffer.getWritePointer(channelIdx, sample);
        auto amount = mInput;
        auto k = 2 * amount / (1 - amount);
        *writePtr = ((1 + k) * *writePtr / (1 + k * std::abs(*writePtr))) * mOutput;
    }
}
