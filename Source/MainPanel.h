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

class MainPanel : public Component,
                  Slider::Listener
{
public:
    MainPanel(DistoverdriveAudioProcessor& processor);
    
    void resized() override;
    void paint(Graphics& g) override;
    void sliderValueChanged (Slider* slider) override;
    
    int getComponentHeight() { return mComponentBounds.getHeight(); }
    
private:
    OwnedArray<Slider> mDistControls;
    OwnedArray<AudioProcessorValueTreeState::SliderAttachment> mDistAttachments;
    
    Rectangle<int> mComponentBounds;
    Rectangle<int> sliderBounds;
};
