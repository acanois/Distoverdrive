/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <array>

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "MainPanel.h"

//==============================================================================
/**
*/
class DistoverdriveAudioProcessorEditor : public AudioProcessorEditor
{
public:
    DistoverdriveAudioProcessorEditor(DistoverdriveAudioProcessor&);
    ~DistoverdriveAudioProcessorEditor();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;

private:
    OwnedArray<Slider> mDistControls;
    OwnedArray<AudioProcessorValueTreeState::SliderAttachment> mDistAttachments;
    
    Rectangle<int> mComponentBounds;
    Rectangle<int> sliderBounds;
    
    DistoverdriveAudioProcessor& processor;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistoverdriveAudioProcessorEditor)
};
