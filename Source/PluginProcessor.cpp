/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistoverdriveAudioProcessor::DistoverdriveAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
mValueTree(*this, nullptr, "ValueTree", {
    std::make_unique<AudioParameterFloat>("input", "input", NormalisableRange<float> (1.f, 2.f, 0.001f), mInput.get()),
    std::make_unique<AudioParameterFloat>("drive", "Drive", NormalisableRange<float> (0.f, 3000.f, 0.001f), mDrive.get()),
    std::make_unique<AudioParameterFloat>("output", "output", NormalisableRange<float> (0.f, 1.f, 0.001f), mOutput.get())
})
{
    mValueTree.addParameterListener("input", this);
    mValueTree.addParameterListener("drive", this);
    mValueTree.addParameterListener("output", this);
}

DistoverdriveAudioProcessor::~DistoverdriveAudioProcessor()
{
}

//==============================================================================
const  String DistoverdriveAudioProcessor::getName() const            { return JucePlugin_Name; }
double DistoverdriveAudioProcessor::getTailLengthSeconds() const      { return 0.0; }
int    DistoverdriveAudioProcessor::getNumPrograms()                  { return 1; } // Should return at least 1
int    DistoverdriveAudioProcessor::getCurrentProgram()               { return 0; }
void   DistoverdriveAudioProcessor::setCurrentProgram (int index)     {}
const  String DistoverdriveAudioProcessor::getProgramName (int index) { return {}; }
void   DistoverdriveAudioProcessor::changeProgramName (int index, const String& newName) {}

bool DistoverdriveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistoverdriveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistoverdriveAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}



//==============================================================================
void DistoverdriveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistoverdriveAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistoverdriveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistoverdriveAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // Clear the buffer
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        auto* writePtr = buffer.getWritePointer(channel);
        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            *writePtr *= (mInput.get() * mDrive.get());
            *writePtr = ((2.f / float_Pi) * std::atan(*writePtr)) * mOutput.get();
            
            writePtr++;
        }
    }
}

void DistoverdriveAudioProcessor::parameterChanged (const String& parameterID, float newValue)
{
    if (parameterID == "input")  mInput.set  (newValue);
    if (parameterID == "drive")  mDrive.set  (newValue);
    if (parameterID == "output") mOutput.set (newValue);
}

//==============================================================================
bool DistoverdriveAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* DistoverdriveAudioProcessor::createEditor()
{
    return new DistoverdriveAudioProcessorEditor (*this);
}

//==============================================================================
void DistoverdriveAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistoverdriveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistoverdriveAudioProcessor();
}
