/*
  ==============================================================================

    GuiElements.h
    Created: 27 Feb 2020 9:30:05pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class GuiElements  : public Component,
                     public AudioProcessorValueTreeState::Listener
{
public:
    void createAttachedSlider (Slider& slider,
                               AudioProcessorValueTreeState::SliderAttachment& sliderAttachment)
    {
        slider.setSliderStyle (Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle (Slider::TextBoxBelow, false, 100, 25);
        
        mControls.add (&slider);
        mAttachments.add (&sliderAttachment);
        addAndMakeVisible (&slider);
    }
    
private:
    OwnedArray<Slider> mControls;
    OwnedArray<AudioProcessorValueTreeState::SliderAttachment> mAttachments;
    
    Rectangle<int> mComponentBounds;
    Rectangle<int> sliderBounds;
};
