/*
  ==============================================================================

    ReverbControlView.cpp
    Created: 23 Mar 2017 3:30:30pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReverbControlView.h"
#include "CustomLook.h"

//==============================================================================
ReverbControlView::ReverbControlView()
///Creates reverb Control view
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setLookAndFeel(&m_whiteFeel);
    
    m_reverbWet = new Slider();
    m_reverbDry = new Slider();
    m_reverbWidth = new Slider();
    m_reverbRoomSize = new Slider();
    m_reverbDamping = new Slider();
    
    m_reverbWet->setSliderStyle(Slider::RotaryVerticalDrag);
    m_reverbWet->setRange(0, 1);
    m_reverbWet->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_reverbWet->setPopupDisplayEnabled(true, nullptr);
    m_reverbWet->setTextValueSuffix("");
    m_reverbWet->setValue(0.01);
    
    m_reverbDry->setSliderStyle(Slider::RotaryVerticalDrag);
    m_reverbDry->setRange(0, 1);
    m_reverbDry->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_reverbDry->setPopupDisplayEnabled(true, nullptr);
    m_reverbDry->setTextValueSuffix("");
    
    m_reverbWidth->setSliderStyle(Slider::RotaryVerticalDrag);
    m_reverbWidth->setRange(0, 1);
    m_reverbWidth->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_reverbWidth->setPopupDisplayEnabled(true, nullptr);
    m_reverbWidth->setTextValueSuffix("");
    
    m_reverbRoomSize->setSliderStyle(Slider::RotaryVerticalDrag);
    m_reverbRoomSize->setRange(0, 1);
    m_reverbRoomSize->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_reverbRoomSize->setPopupDisplayEnabled(true, nullptr);
    m_reverbRoomSize->setTextValueSuffix("");
    
    m_reverbDamping->setSliderStyle(Slider::RotaryVerticalDrag);
    m_reverbDamping->setRange(0, 1);
    m_reverbDamping->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_reverbDamping->setPopupDisplayEnabled(true, nullptr);
    m_reverbDamping->setTextValueSuffix("");
    
    addAndMakeVisible(m_reverbWet);
    addAndMakeVisible(m_reverbDry);
    addAndMakeVisible(m_reverbWidth);
    addAndMakeVisible(m_reverbRoomSize);
    addAndMakeVisible(m_reverbDamping);
    
}

ReverbControlView::~ReverbControlView()
{
    
}

void ReverbControlView::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    auto area = getLocalBounds();
    
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::black);
    g.setFont (10.0f);
    g.drawText ("", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
    
    g.drawText("Reverb", area.removeFromTop(13), Justification::centred);
    g.drawFittedText("Wet", area.removeFromLeft(getWidth()/5), Justification::centredBottom, true);
    g.drawFittedText("Dry", area.removeFromLeft(getWidth()/5), Justification::centredBottom, true);
    g.drawFittedText("Roomsize", area.removeFromLeft(getWidth()/5), Justification::centredBottom, true);
    g.drawFittedText("Width", area.removeFromLeft(getWidth()/5), Justification::centredBottom, true);
    g.drawFittedText("Damping", area.removeFromLeft(getWidth()/5), Justification::centredBottom, true);

}

void ReverbControlView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    auto area = getLocalBounds();

    m_reverbWet->setBounds(area.removeFromLeft(getWidth()/5).reduced(9, 9));
    m_reverbDry->setBounds(area.removeFromLeft(getWidth()/5).reduced(9, 9));
    m_reverbRoomSize->setBounds(area.removeFromLeft(getWidth()/5).reduced(9, 9));
    m_reverbWidth->setBounds(area.removeFromLeft(getWidth()/5).reduced(9, 9));
    m_reverbDamping->setBounds(area.removeFromLeft(getWidth()/5).reduced(9, 9));

}
