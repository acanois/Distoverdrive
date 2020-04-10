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
    std::make_unique<AudioParameterFloat> ("input", "Input", NormalisableRange<float>   (0.f, 0.99f, 0.001f), mInput.get()),
    std::make_unique<AudioParameterFloat> ("output", "Output", NormalisableRange<float> (0.f, 1.f, 0.001f), mOutput.get())
}),
mpDist(std::make_unique<Distortion>(mInput.get(), mOutput.get()))
{
    mValueTree.addParameterListener("input", this);
    mValueTree.addParameterListener("output", this);
}

DistoverdriveAudioProcessor::~DistoverdriveAudioProcessor()
{
}

//==============================================================================
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

const  String DistoverdriveAudioProcessor::getName() const            { return JucePlugin_Name; }
double DistoverdriveAudioProcessor::getTailLengthSeconds() const      { return 0.0; }
int    DistoverdriveAudioProcessor::getNumPrograms()                  { return 1; } // Should return at least 1
int    DistoverdriveAudioProcessor::getCurrentProgram()               { return 0; }
void   DistoverdriveAudioProcessor::setCurrentProgram (int index)     {}
const  String DistoverdriveAudioProcessor::getProgramName (int index) { return {}; }
void   DistoverdriveAudioProcessor::changeProgramName (int index, const String& newName) {}

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
    
    mpDist->setParameters (mInput.get(), mOutput.get());
    for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
        mpDist->processBuffer (buffer, totalNumOutputChannels, channel);
}

void DistoverdriveAudioProcessor::parameterChanged (const String& parameterID, float newValue)
{
    if (parameterID == "input")  mInput.set  (newValue);
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
    auto state = mValueTree.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void DistoverdriveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (mValueTree.state.getType()))
            mValueTree.replaceState (ValueTree::fromXml (*xmlState));
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistoverdriveAudioProcessor();
}
