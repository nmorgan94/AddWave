/*
  ==============================================================================

    EnvelopeFilterView.h
    Created: 10 Jul 2017 2:52:02pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef ENVELOPEFILTERVIEW_H_INCLUDED
#define ENVELOPEFILTERVIEW_H_INCLUDED

#include "CustomLook.h"

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
*/
class EnvelopeHPFilterView    : public Component
{
public:
    EnvelopeHPFilterView();
    
    ScopedPointer<Slider> m_hpFilterAmountSlider;
    ScopedPointer<Slider> m_hpFilterAttackSlider;
    ScopedPointer<Slider> m_hpFilterDecaySlider;
    ScopedPointer<Slider> m_hpFilterSustainSlider;
    ScopedPointer<Slider> m_hpFilterReleaseSlider;
    
    
    ~EnvelopeHPFilterView();

    void paint (Graphics&) override;
    void resized() override;

private:
    

    CustomLook m_HPLook;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeHPFilterView)
};


#endif  // ENVELOPEFILTERVIEW_H_INCLUDED
