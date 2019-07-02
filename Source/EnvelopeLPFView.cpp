/*
  ==============================================================================

    LFOView.cpp
    Created: 10 Jul 2017 2:52:22pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeLPFView.h"

//==============================================================================
EnvelopeLPFilterView::EnvelopeLPFilterView()
///Creates the highpass filter design and layout

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setLookAndFeel(&m_LPLook);
    
    m_lpFilterAmountSlider = new Slider();
    addAndMakeVisible(m_lpFilterAmountSlider);
    m_lpFilterAmountSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_lpFilterAmountSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_lpFilterAmountSlider->setRange(20, 20000);
    m_lpFilterAmountSlider->setPopupDisplayEnabled(true, nullptr);
    
    
    m_lpFilterAttackSlider = new Slider();
    addAndMakeVisible(m_lpFilterAttackSlider);
    m_lpFilterAttackSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_lpFilterAttackSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_lpFilterAttackSlider->setRange(0.1, 5.0);
    m_lpFilterAttackSlider->setPopupDisplayEnabled(true, nullptr);
    
    m_lpFilterDecaySlider = new Slider();
    addAndMakeVisible(m_lpFilterDecaySlider);
    m_lpFilterDecaySlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_lpFilterDecaySlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_lpFilterDecaySlider->setRange(0.1, 5.0);
    m_lpFilterDecaySlider->setPopupDisplayEnabled(true, nullptr);
    
    m_lpFilterSustainSlider = new Slider();
    addAndMakeVisible(m_lpFilterSustainSlider);
    m_lpFilterSustainSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_lpFilterSustainSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_lpFilterSustainSlider->setRange(0.0, 1.0);
    m_lpFilterSustainSlider->setPopupDisplayEnabled(true, nullptr);
    
    m_lpFilterReleaseSlider = new Slider();
    addAndMakeVisible(m_lpFilterReleaseSlider);
    m_lpFilterReleaseSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_lpFilterReleaseSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_lpFilterReleaseSlider->setRange(0.1, 1.0);
    m_lpFilterReleaseSlider->setPopupDisplayEnabled(true, nullptr);
    

}

EnvelopeLPFilterView::~EnvelopeLPFilterView()
{
}

void EnvelopeLPFilterView::paint (Graphics& g)
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
                Justification::centredTop, true);   // draw some placeholder text

    auto window = getLocalBounds();
    auto width = getWidth()/5;
    g.drawText("Lowpass Env", window.removeFromTop(13), Justification::centred);
    g.drawText ("Frequency", window.removeFromLeft(width),Justification::centredBottom, true);
    g.drawText ("Attack", window.removeFromLeft(width),Justification::centredBottom, true);
    g.drawText ("Decay", window.removeFromLeft(width),Justification::centredBottom, true);
    g.drawText ("Sustain", window.removeFromLeft(width),Justification::centredBottom, true);
    g.drawText ("Release", window.removeFromLeft(width),Justification::centredBottom, true);
    
}


void EnvelopeLPFilterView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto window = getLocalBounds();
    auto width = getWidth()/5;
    
    m_lpFilterAmountSlider->setBounds(window.removeFromLeft(width).reduced(9, 9));
    m_lpFilterAttackSlider->setBounds(window.removeFromLeft(width).reduced(9, 9));
    m_lpFilterDecaySlider->setBounds(window.removeFromLeft(width).reduced(9, 9));
    m_lpFilterSustainSlider->setBounds(window.removeFromLeft(width).reduced(9, 9));
    m_lpFilterReleaseSlider->setBounds(window.removeFromLeft(width).reduced(9, 9));


}
