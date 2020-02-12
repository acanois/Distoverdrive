/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class DistoverdriveAudioProcessor  : public AudioProcessor,
                                     public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    DistoverdriveAudioProcessor();
    ~DistoverdriveAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void parameterChanged (const String& parameterID, float newValue) override;
    AudioProcessorValueTreeState& getValueTreeState() { return mValueTree; }

private:
    //==============================================================================
    Atomic<float> mInput { 1.f };
    Atomic<float> mDrive { 1.f };
    Atomic<float> mOutput { 1.f };
    Atomic<float> mDistCutoff { 3000.f };
    
    AudioProcessorValueTreeState mValueTree;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistoverdriveAudioProcessor)
};
