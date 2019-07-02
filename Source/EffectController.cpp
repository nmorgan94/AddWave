/*
  ==============================================================================

    EffectController.cpp
    Created: 23 Mar 2017 3:36:11pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#include "EffectController.h"


EffectsController::EffectsController(SynthAudioProcessor& plugin,FilterControlView& filterview, ReverbControlView& reverbview, DelayControlView& delayview, DistortionControlView& distortionview):

    ///creates and gives reference to the contents of the controller

    m_plugin(plugin),
    m_filterView(filterview),
    m_reverbView(reverbview),
    m_delayView(delayview),
    m_distortionView(distortionview)
{
    m_filterView.m_lowpassSlider->addListener(this);
    m_filterView.m_highpassSlider->addListener(this);
    
    m_reverbView.m_reverbWet->addListener(this);
    m_reverbView.m_reverbDry->addListener(this);
    m_reverbView.m_reverbWidth->addListener(this);
    m_reverbView.m_reverbRoomSize->addListener(this);
    m_reverbView.m_reverbDamping->addListener(this);
    
    m_delayView.m_leftDelayTime->addListener(this);
    m_delayView.m_rightDelayTime->addListener(this);
    m_delayView.m_leftFeedback->addListener(this);
    m_delayView.m_rightFeedback->addListener(this);
    
    m_distortionView.m_distortionAmountSlider->addListener(this);
    
    updateSliderPos();
}


void EffectsController::sliderValueChanged(Slider* slider)
{
    
    
    if(slider == m_filterView.m_lowpassSlider){
       // //std::coutt << "Low Filter "<< slider->getValue()<<std::endl;
        *m_plugin.m_lowpassCutoffParam = slider->getValue();
        
    }
    
    if (slider == m_filterView.m_highpassSlider){
       // //std::coutt << "High Filter " << slider->getValue()<<std::endl;
        *m_plugin.m_highpassCutoffParam = slider->getValue();
    }
    
    if(slider == m_reverbView.m_reverbWet){
       // //std::coutt << "reverb wet "<< slider->getValue()<<std::endl;
        m_plugin.set_reverb_wet(slider->getValue());
    }
    
    if(slider == m_reverbView.m_reverbDry){
       ////std::coutt << "reverb dry " << slider->getValue()<<std::endl;
        m_plugin.set_reverb_dry(slider->getValue());
    }
    if(slider == m_reverbView.m_reverbWidth){
       // //std::coutt << "reverb width " << slider->getValue()<<std::endl;
        m_plugin.set_reverb_width(slider->getValue());
    }
    
    if(slider == m_reverbView.m_reverbRoomSize){
       // //std::coutt << "reverb roomsize " << slider->getValue()<<std::endl;
        m_plugin.set_reverb_roomsize(slider->getValue());
    }
    
    if(slider == m_reverbView.m_reverbDamping){
        
       // //std::coutt << "reverb damping " << slider->getValue() << std::endl;
        m_plugin.set_reverb_damping(slider->getValue());
    }
    
    
    if(slider == m_delayView.m_leftDelayTime){
       // //std::coutt << "Delay time Left" << slider->getValue() << std::endl;
        *m_plugin.m_delayTimeLeft = slider->getValue();
    }
    
    if(slider == m_delayView.m_rightDelayTime){
       // //std::coutt << "Delay time Right" << slider->getValue() << std::endl;
        *m_plugin.m_delayTimeRight = slider->getValue();
    }
    
    if(slider == m_delayView.m_leftFeedback){
       // //std::coutt << "Delay Feedback Left" << slider->getValue() << std::endl;
        *m_plugin.m_delayFeedbackLeft = slider->getValue();
    }
    
    if(slider == m_delayView.m_rightFeedback){
       // //std::coutt << "Delay Feedback Right" << slider->getValue() << std::endl;
        *m_plugin.m_delayFeedbackRight = slider->getValue();
    }
    
//    if(slider == m_delayView.m_wet){
//        //std::coutt << "Delay wet" << slider->getValue() << std::endl;
//        *m_plugin.m_wet = slider->getValue();
//    }
    
    if(slider == m_distortionView.m_distortionAmountSlider){
      //  //std::coutt << "Distortion Amount " << slider->getValue() << std::endl;
        ////std::coutt << m_plugin.m_distortionAmount->get()<< std::endl;
        *m_plugin.m_distortionAmount = slider->getValue();
    }
}

void EffectsController::updateSliderPos()
///Updates the Sliders in the effects tab when UI is reloaded

{
    
    const float distortionSliderVal = m_plugin.get_distortionAmount();
    
    if (distortionSliderVal != (float) m_distortionView.m_distortionAmountSlider->getValue() && ! isMouseButtonDown())
        m_distortionView.m_distortionAmountSlider->setValue(distortionSliderVal);
    
    const float reverbWetSliderVal = m_plugin.get_reverb_wet();
    
    if (reverbWetSliderVal != (float) m_reverbView.m_reverbWet->getValue() && ! isMouseButtonDown())
        m_reverbView.m_reverbWet->setValue(reverbWetSliderVal);
    
    const float reverbDrySliderVal = m_plugin.get_reverb_dry();
    
    if (reverbDrySliderVal != (float) m_reverbView.m_reverbDry->getValue() && ! isMouseButtonDown())
        m_reverbView.m_reverbDry->setValue(reverbDrySliderVal);
    
    const float reverbDampingSliderVal = m_plugin.get_reverb_damping();
    
    if (reverbDampingSliderVal != (float) m_reverbView.m_reverbDamping->getValue() && ! isMouseButtonDown())
        m_reverbView.m_reverbDamping->setValue(reverbDampingSliderVal);
    
    const float reverbWidthSliderVal = m_plugin.get_reverb_width();
    
    if (reverbWidthSliderVal != (float) m_reverbView.m_reverbWidth->getValue() && ! isMouseButtonDown())
        m_reverbView.m_reverbWidth->setValue(reverbWidthSliderVal);
    
    const float reverbRoomsizeSliderVal = m_plugin.get_reverb_roomsize();
    
    if (reverbRoomsizeSliderVal != (float) m_reverbView.m_reverbRoomSize->getValue() && ! isMouseButtonDown())
        m_reverbView.m_reverbRoomSize->setValue(reverbRoomsizeSliderVal);
    
    const float lowpassSliderVal = m_plugin.get_lowpass_cutoff();
    
    if (lowpassSliderVal != (float) m_filterView.m_lowpassSlider->getValue() && ! isMouseButtonDown())
        m_filterView.m_lowpassSlider->setValue(lowpassSliderVal);
    
    const float highpassSliderVal = m_plugin.get_highpass_cutoff();
    
    if (highpassSliderVal != (float) m_filterView.m_highpassSlider->getValue() && ! isMouseButtonDown())
        m_filterView.m_highpassSlider->setValue(highpassSliderVal);
    
    const float leftDelayTimeVal = m_plugin.get_left_delay_time();
    
    if (leftDelayTimeVal != (float) m_delayView.m_leftDelayTime->getValue() && ! isMouseButtonDown())
        m_delayView.m_leftDelayTime->setValue(leftDelayTimeVal);
    
    const float rightDelayTimeVal = m_plugin.get_right_delay_time();
    
    if (rightDelayTimeVal != (float) m_delayView.m_rightDelayTime->getValue() && ! isMouseButtonDown())
        m_delayView.m_rightDelayTime->setValue(rightDelayTimeVal);
    
    const float leftDelayFeedbackVal = m_plugin.get_left_delay_feedback();
    
    if (leftDelayFeedbackVal != (float) m_delayView.m_leftFeedback->getValue() && ! isMouseButtonDown())
        m_delayView.m_leftFeedback->setValue(leftDelayFeedbackVal);
    
    const float rightDelayFeedbackVal = m_plugin.get_right_delay_feedback();
    
    if (rightDelayFeedbackVal != (float) m_delayView.m_rightFeedback->getValue() && ! isMouseButtonDown())
        m_delayView.m_rightFeedback->setValue(rightDelayFeedbackVal);
}
