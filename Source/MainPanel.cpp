/*
  ==============================================================================

    MainPanel.cpp
    Created: 20 Jun 2020 11:43:07pm
    Author:  David Richter

  ==============================================================================
*/

#include "MainPanel.h"

MainPanel::MainPanel(DistoverdriveAudioProcessor& processor)
{
    std::array<std::string, 2> controlNames = { "input", "output" };
    
    for (auto name : controlNames)
    {
        auto* slider = new Slider(name);
        auto* sliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getValueTreeState(), name, *slider);
        slider->setSliderStyle(Slider::RotaryVerticalDrag);
        slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
        mDistControls.add(slider);
        mDistAttachments.add(sliderAttachment);
        addAndMakeVisible(slider);
    }
    
    sliderBounds.setBounds(0, 100, 100, 100);
    mComponentBounds.setBounds(0, 0, (sliderBounds.getWidth() * 4), (sliderBounds.getHeight()));
}

void MainPanel::resized()
{
    int xPos = mComponentBounds.getX();
    for (Slider* control : mDistControls) {
        control->setBounds(xPos, mComponentBounds.getY(), sliderBounds.getWidth(), sliderBounds.getHeight());
        xPos += (sliderBounds.getX() + sliderBounds.getWidth() + 10);
    }
}

void MainPanel::paint(Graphics &g)
{
    g.fillAll (Colours::black);
}

void MainPanel::sliderValueChanged (Slider* slider)
{
    
}
