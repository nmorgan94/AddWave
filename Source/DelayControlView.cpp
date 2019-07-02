/*
  ==============================================================================

    DelayControlView.cpp
    Created: 13 Apr 2017 2:41:26pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayControlView.h"
#include "CustomLook.h"
#include "EffectController.h"

//==============================================================================
DelayControlView::DelayControlView()
///Creates delay Controlc view
{
    
    m_leftDelayTime = new Slider();
    m_rightDelayTime = new Slider();
    m_leftFeedback = new Slider();
    m_rightFeedback = new Slider();
    
    setLookAndFeel(&m_blackfeel);
    
    m_leftDelayTime->setSliderStyle(Slider::RotaryVerticalDrag);
    m_leftDelayTime->setRange(0.05, 5);
    m_leftDelayTime->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_leftDelayTime->setPopupDisplayEnabled(true, nullptr);
    m_leftDelayTime->setTextValueSuffix("");
    
    m_rightDelayTime->setSliderStyle(Slider::RotaryVerticalDrag);
    m_rightDelayTime->setRange(0.05, 5);
    m_rightDelayTime->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_rightDelayTime->setPopupDisplayEnabled(true, nullptr);
    m_rightDelayTime->setTextValueSuffix("");

    m_leftFeedback->setSliderStyle(Slider::RotaryVerticalDrag);
    m_leftFeedback->setRange(0.0, 0.8);
    m_leftFeedback->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_leftFeedback->setPopupDisplayEnabled(true, nullptr);
    m_leftFeedback->setTextValueSuffix("");

    m_rightFeedback->setSliderStyle(Slider::RotaryVerticalDrag);
    m_rightFeedback->setRange(0.0, 0.8);
    m_rightFeedback->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_rightFeedback->setPopupDisplayEnabled(true, nullptr);
    m_rightFeedback->setTextValueSuffix("");

    addAndMakeVisible(m_leftDelayTime);
    addAndMakeVisible(m_rightDelayTime);
    addAndMakeVisible(m_leftFeedback);
    addAndMakeVisible(m_rightFeedback);

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

DelayControlView::~DelayControlView()
{
}

void DelayControlView::paint (Graphics& g)
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
    g.drawText("Delay", area.removeFromTop(13), Justification::centred);
    g.drawFittedText("Left Time (ms)", area.removeFromLeft(getWidth()/4), Justification::centredBottom, true);
    g.drawFittedText("Right Time (ms)", area.removeFromLeft(getWidth()/4), Justification::centredBottom, true);
    g.drawFittedText("Left Feedback", area.removeFromLeft(getWidth()/4), Justification::centredBottom, true);
    g.drawFittedText("Right Feedback", area.removeFromLeft(getWidth()/4), Justification::centredBottom, true);

}

void DelayControlView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();
    
    m_leftDelayTime->setBounds(area.removeFromLeft(getWidth()/4).reduced(9, 9));
    m_rightDelayTime->setBounds(area.removeFromLeft(getWidth()/4).reduced(9, 9));
    m_leftFeedback->setBounds(area.removeFromLeft(getWidth()/4).reduced(9, 9));
    m_rightFeedback->setBounds(area.removeFromLeft(getWidth()/4).reduced(9, 9));
}



