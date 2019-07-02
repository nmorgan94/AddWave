/*
  ==============================================================================

    LFOView.h
    Created: 10 Jul 2017 2:52:22pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef LFOVIEW_H_INCLUDED
#define LFOVIEW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomLook.h"

//==============================================================================
/*
*/
class EnvelopeLPFilterView    : public Component
{
public:
    EnvelopeLPFilterView();
    
    ScopedPointer<Slider> m_lpFilterAmountSlider;
    ScopedPointer<Slider> m_lpFilterAttackSlider;
    ScopedPointer<Slider> m_lpFilterDecaySlider;
    ScopedPointer<Slider> m_lpFilterSustainSlider;
    ScopedPointer<Slider> m_lpFilterReleaseSlider;
    
    ~EnvelopeLPFilterView();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    CustomLook_V2 m_LPLook;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeLPFilterView)
};


#endif  // LFOVIEW_H_INCLUDED
