/*
  ==============================================================================

    DelayControlView.h
    Created: 13 Apr 2017 2:41:26pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef DELAYCONTROLVIEW_H_INCLUDED
#define DELAYCONTROLVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLook.h"

//==============================================================================
/*
*/
class DelayControlView    : public Component
{
public:
    DelayControlView();

    
    ~DelayControlView();

    void paint (Graphics&) override;
    void resized() override;
    
    ScopedPointer<Slider> m_leftDelayTime;
    ScopedPointer<Slider> m_rightDelayTime;
    ScopedPointer<Slider> m_leftFeedback;
    ScopedPointer<Slider> m_rightFeedback;

private:
    
    CustomLook m_blackfeel;
        
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayControlView)
};


#endif  // DELAYCONTROLVIEW_H_INCLUDED
