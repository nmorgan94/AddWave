/*
  ==============================================================================

    ReverbControlView.h
    Created: 23 Mar 2017 3:30:30pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef REVERBCONTROLVIEW_H_INCLUDED
#define REVERBCONTROLVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLook.h"

//==============================================================================
/*
*/
class ReverbControlView    : public Component
{
public:
    ReverbControlView();
    ~ReverbControlView();

    void paint (Graphics&) override;
    void resized() override;
    
    ScopedPointer<Slider> m_reverbWet;
    ScopedPointer<Slider> m_reverbDry;
    ScopedPointer<Slider> m_reverbWidth;
    ScopedPointer<Slider> m_reverbRoomSize;
    ScopedPointer<Slider> m_reverbDamping;
    
    CustomLook_V2 m_whiteFeel;
 

private:
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbControlView)
};


#endif  // REVERBCONTROLVIEW_H_INCLUDED
