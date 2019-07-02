/*
  ==============================================================================

    FilterControlView.cpp
    Created: 23 Mar 2017 3:30:59pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterControlView.h"

//==============================================================================
FilterControlView::FilterControlView()



///Creates filter Control view
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setLookAndFeel(&m_blackFeel);
    
    addAndMakeVisible(m_lowpassSlider = new Slider("LowPass"));
    m_lowpassSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_lowpassSlider->setRange(20.0, 20000, 1.0);
    m_lowpassSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_lowpassSlider->setPopupDisplayEnabled(true, nullptr);
    m_lowpassSlider->setTextValueSuffix("");
    m_lowpassSlider->setValue(20000);
   
    addAndMakeVisible(m_highpassSlider = new Slider ("HighPass"));
    m_highpassSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_highpassSlider->setValue(20, sendNotificationAsync);
    m_highpassSlider->getValue();
    m_highpassSlider->setRange(20.0, 20000, 1.0);
    m_highpassSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_highpassSlider->setPopupDisplayEnabled(true, nullptr);
    m_highpassSlider->setTextValueSuffix("");

}

FilterControlView::~FilterControlView()
{
    

    
}

void FilterControlView::paint (Graphics& g)
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
    
    g.setFont(10.0f);
    g.setColour(Colours::black);
    
    g.drawText("Filter", area.removeFromTop(13), Justification::centred);
    g.drawFittedText("High Pass", area.removeFromLeft(getWidth()/2), Justification::centredBottom, true);
    g.drawFittedText("Low Pass", area.removeFromLeft(getWidth()/2), Justification::centredBottom, true);

}

void FilterControlView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    auto area = getLocalBounds();

    m_highpassSlider->setBounds(area.removeFromLeft(getWidth()/2).reduced(9, 9));
    m_lowpassSlider->setBounds(area.removeFromLeft(getWidth()/2).reduced(9, 9));

}
