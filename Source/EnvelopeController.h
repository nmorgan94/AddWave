/*
  ==============================================================================

    EnvelopeController.h
    Created: 10 Jul 2017 3:24:32pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef ENVELOPECONTROLLER_H_INCLUDED
#define ENVELOPECONTROLLER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "EnvelopeLPFView.h"
#include "EnvelopeHPFView.h"
#include "ADSR.h"

//==============================================================================
/*
*/
class EnvelopeController    : public Slider::Listener,
                              public Component

{
    SynthAudioProcessor& m_envPlugin;

    EnvelopeHPFilterView& m_envHPFilterView;
    EnvelopeLPFilterView& m_envLPFilterView;
    
public:

    EnvelopeController(SynthAudioProcessor& envPlugin,
                       EnvelopeHPFilterView& envHPFilterView, EnvelopeLPFilterView& envLPFilterView);
    
    void sliderValueChanged(Slider* slider);
    
    void updateEnvSlider();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeController)
};


#endif  // ENVELOPECONTROLLER_H_INCLUDED
