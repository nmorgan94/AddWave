/*
  ==============================================================================

    FilterControlView.h
    Created: 23 Mar 2017 3:30:59pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef FILTERCONTROLVIEW_H_INCLUDED
#define FILTERCONTROLVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLook.h"

//==============================================================================
/*
*/
class FilterControlView    : public Component
{
public:
    FilterControlView();
    ~FilterControlView();

    void paint (Graphics&) override;
    void resized() override;

    ScopedPointer<Slider> m_lowpassSlider;
    ScopedPointer<Slider> m_highpassSlider;

    CustomLook m_blackFeel;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterControlView)
};


#endif  // FILTERCONTROLVIEW_H_INCLUDED
