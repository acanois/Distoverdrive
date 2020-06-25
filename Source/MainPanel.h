/*
  ==============================================================================

    MainPanel.h
    Created: 20 Jun 2020 11:43:07pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class MainPanel : public Component
{
public:
    MainPanel(DistoverdriveAudioProcessor& processor);
    
    void paint(Graphics& g) override;
    
private:
    OwnedArray<Slider> mDistControls;
    OwnedArray<AudioProcessorValueTreeState::SliderAttachment> mDistAttachments;
    
    Rectangle<int> mComponentBounds;
    Rectangle<int> sliderBounds;
};
