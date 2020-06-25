/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistoverdriveAudioProcessorEditor::DistoverdriveAudioProcessorEditor (DistoverdriveAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    mMainPanel = std::make_unique<MainPanel>(p);
    addAndMakeVisible(*mMainPanel);
//    std::array<std::string, 2> controlNames = { "input", "output" };
//
//    for (auto name : controlNames)
//    {
//        auto* slider = new Slider(name);
//        auto* sliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), name, *slider);
//        slider->setSliderStyle(Slider::RotaryVerticalDrag);
//        slider->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
//        mDistControls.add(slider);
//        mDistAttachments.add(sliderAttachment);
//        addAndMakeVisible(slider);
//    }
//
//    sliderBounds.setBounds(0, 100, 100, 100);
//    mComponentBounds.setBounds(0, 0, (sliderBounds.getWidth() * 4), (sliderBounds.getHeight()));
    
    setSize(400, 300);
}

DistoverdriveAudioProcessorEditor::~DistoverdriveAudioProcessorEditor()
{
}

//==============================================================================
void DistoverdriveAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    mMainPanel->paint(g);
}

void DistoverdriveAudioProcessorEditor::resized()
{
//    int xPos = mComponentBounds.getX();
//    for (Slider* control : mDistControls) {
//        control->setBounds(xPos, mComponentBounds.getY(), sliderBounds.getWidth(), sliderBounds.getHeight());
//        xPos += (sliderBounds.getX() + sliderBounds.getWidth() + 10);
//    }
}
