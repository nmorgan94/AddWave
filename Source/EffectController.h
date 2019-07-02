/*
  ==============================================================================

    EffectController.h
    Created: 23 Mar 2017 3:36:11pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef EFFECTCONTROLLER_H_INCLUDED
#define EFFECTCONTROLLER_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"

#include "PluginProcessor.h"
#include "FilterControlView.h"
#include "ReverbControlView.h"
#include "DelayControlView.h"
#include "DistortionControlView.h"
#include "CustomLook.h"

class EffectsController : public Slider::Listener,
                            public Component

{
    ///Hold all effects manipulation components

    SynthAudioProcessor& m_plugin;
    FilterControlView& m_filterView;
    ReverbControlView& m_reverbView;
    DelayControlView& m_delayView;
    DistortionControlView& m_distortionView;
    
public:
    EffectsController(SynthAudioProcessor& plugin,FilterControlView& filterview, ReverbControlView& reverbview, DelayControlView& delayview, DistortionControlView& distortionView);
    
    void sliderValueChanged(Slider* slider);
    
    void updateSliderPos();

};


#endif  // EFFECTCONTROLLER_H_INCLUDED
