/*
  ==============================================================================

    DistortionControlView.h
    Created: 26 Apr 2017 2:27:02pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef DISTORTIONCONTROLVIEW_H_INCLUDED
#define DISTORTIONCONTROLVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLook.h"


//==============================================================================
/*
*/
class DistortionControlView    : public Component
{
public:
    DistortionControlView();

    ~DistortionControlView();

    void paint (Graphics&) override;
    void resized() override;

    ScopedPointer <Slider> m_distortionAmountSlider;
    
private:
    
    CustomLook_V2 m_whiteFeel;
    
  
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionControlView)
};




#endif  // DISTORTIONCONTROLVIEW_H_INCLUDED
