/*
  ==============================================================================

    DistortionControlView.cpp
    Created: 26 Apr 2017 2:27:02pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DistortionControlView.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "EffectController.h"

//==============================================================================
DistortionControlView::DistortionControlView()
///Creates distorition control view
{
    setLookAndFeel(&m_whiteFeel);
    
    m_distortionAmountSlider = new Slider() ;
    
    m_distortionAmountSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_distortionAmountSlider->setRange(0.0, 0.99);
    m_distortionAmountSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_distortionAmountSlider->setPopupDisplayEnabled(true, nullptr);
    m_distortionAmountSlider->setTextValueSuffix("");
    
    addAndMakeVisible(m_distortionAmountSlider);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
 
}

DistortionControlView::~DistortionControlView()
{

    
}

void DistortionControlView::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::black);
    g.setFont (10.0f);
    g.drawText ("", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
    g.drawText("Distortion", getLocalBounds().removeFromTop(13), Justification::centred);
    g.drawFittedText("Amount", getLocalBounds(), Justification::centredBottom, true);
  
}

void DistortionControlView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
       m_distortionAmountSlider->setBounds(getLocalBounds().reduced(9, 9));
       
}


