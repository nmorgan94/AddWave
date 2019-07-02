/*
  ==============================================================================

    EnvelopeFilterView.cpp
    Created: 10 Jul 2017 2:52:02pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeHPFView.h"

//==============================================================================
EnvelopeHPFilterView::EnvelopeHPFilterView()
///Creates the highpass filter design and layout

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setLookAndFeel(&m_HPLook);
    
    m_hpFilterAmountSlider = new Slider();
    addAndMakeVisible(m_hpFilterAmountSlider);
    m_hpFilterAmountSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_hpFilterAmountSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_hpFilterAmountSlider->setRange(20, 20000);
    m_hpFilterAmountSlider->setPopupDisplayEnabled(true, nullptr);
    
    
    m_hpFilterAttackSlider = new Slider();
    addAndMakeVisible(m_hpFilterAttackSlider);
    m_hpFilterAttackSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_hpFilterAttackSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_hpFilterAttackSlider->setRange(0.1, 5);
    m_hpFilterAttackSlider->setPopupDisplayEnabled(true, nullptr);
    
    m_hpFilterDecaySlider = new Slider();
    addAndMakeVisible(m_hpFilterDecaySlider);
    m_hpFilterDecaySlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_hpFilterDecaySlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_hpFilterDecaySlider->setRange(0.1, 5);
    m_hpFilterDecaySlider->setPopupDisplayEnabled(true, nullptr);
    
    m_hpFilterSustainSlider = new Slider();
    addAndMakeVisible(m_hpFilterSustainSlider);
    m_hpFilterSustainSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_hpFilterSustainSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_hpFilterSustainSlider->setRange(0, 1);
    m_hpFilterSustainSlider->setPopupDisplayEnabled(true, nullptr);
    
    m_hpFilterReleaseSlider = new Slider();
    addAndMakeVisible(m_hpFilterReleaseSlider);
    m_hpFilterReleaseSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    m_hpFilterReleaseSlider->setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    m_hpFilterReleaseSlider->setRange(0.1, 5);
    m_hpFilterReleaseSlider->setPopupDisplayEnabled(true, nullptr);


}

EnvelopeHPFilterView::~EnvelopeHPFilterView()
{
}

void EnvelopeHPFilterView::paint (Graphics& g)
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
    
    auto window = getLocalBounds();
    auto width = getWidth()/5;
    
    g.drawText("Highpass Env", window.removeFromTop(13), Justification::centred);
    g.drawText ("Frequency", window.removeFromLeft(width),Justification::centredBottom, true);
    g.drawText ("Attack", window.removeFromLeft(width),Justification::centredBottom, true);
    g.drawText ("Decay", window.removeFromLeft(width),Justification::centredBottom, true);
    g.drawText ("Sustain", window.removeFromLeft(width),Justification::centredBottom, true);
    g.drawText ("Release", window.removeFromLeft(width),Justification::centredBottom, true);
    
}

void EnvelopeHPFilterView::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto window = getLocalBounds();
    auto width = getWidth()/5;
    
    m_hpFilterAmountSlider->setBounds(window.removeFromLeft(width).reduced(9, 9));
    m_hpFilterAttackSlider->setBounds(window.removeFromLeft(width).reduced(9, 9));
    m_hpFilterDecaySlider->setBounds(window.removeFromLeft(width).reduced(9, 9));
    m_hpFilterSustainSlider->setBounds(window.removeFromLeft(width).reduced(9, 9));
    m_hpFilterReleaseSlider->setBounds(window.removeFromLeft(width).reduced(9, 9));

}
