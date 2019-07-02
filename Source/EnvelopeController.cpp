/*
 ==============================================================================
 
 EffectController.cpp
 Created: 23 Mar 2017 3:36:11pm
 Author:  Nicholas Morgan
 
 ==============================================================================
 */


#include "EnvelopeController.h"



EnvelopeController::EnvelopeController(SynthAudioProcessor& envPlugin, EnvelopeHPFilterView& envHPFilterView, EnvelopeLPFilterView& envLPFilterView):

m_envPlugin(envPlugin),

m_envHPFilterView(envHPFilterView),
m_envLPFilterView(envLPFilterView)

///creates and gives reference to the contents of the controller

{
    
    m_envHPFilterView.m_hpFilterAmountSlider->addListener(this);
    m_envHPFilterView.m_hpFilterAttackSlider->addListener(this);
    m_envHPFilterView.m_hpFilterDecaySlider->addListener(this);
    m_envHPFilterView.m_hpFilterSustainSlider->addListener(this);
    m_envHPFilterView.m_hpFilterReleaseSlider->addListener(this);
    
    m_envLPFilterView.m_lpFilterAmountSlider->addListener(this);
    m_envLPFilterView.m_lpFilterAttackSlider->addListener(this);
    m_envLPFilterView.m_lpFilterDecaySlider->addListener(this);
    m_envLPFilterView.m_lpFilterSustainSlider->addListener(this);
    m_envLPFilterView.m_lpFilterReleaseSlider->addListener(this);
    
    updateEnvSlider();

}


void EnvelopeController::sliderValueChanged(Slider* slider)
///Called if slider is manipulated by mouse
{
    if(slider == m_envHPFilterView.m_hpFilterAmountSlider)
    {
        ////std::coutt << "HP Amount: " << slider->getValue() << std::endl;
        *m_envPlugin.m_hpAmount = slider->getValue();
        
        
    }
    
    if(slider == m_envHPFilterView.m_hpFilterAttackSlider)
    {
       // //std::coutt << "HP Attack: " << slider->getValue() << std::endl;
        *m_envPlugin.m_hpAttack = slider->getValue();
        
    }
    
    if(slider == m_envHPFilterView.m_hpFilterDecaySlider)
    {
        ////std::coutt << "HP Decay: "<< slider->getValue() << std::endl;
        *m_envPlugin.m_hpDecay = slider->getValue();
        
            
    }

    if(slider == m_envHPFilterView.m_hpFilterSustainSlider)
    {
        ////std::coutt << "HP Sustain: "<< slider->getValue() << std::endl;
        *m_envPlugin.m_hpSustain = slider->getValue();
        
        
    }
    
    if(slider == m_envHPFilterView.m_hpFilterReleaseSlider)
    {
       // //std::coutt << "HP Release: "<< slider->getValue() << std::endl;
        *m_envPlugin.m_hpRelease = slider->getValue();
        
        
    }
    
    if(slider == m_envLPFilterView.m_lpFilterAmountSlider)
    {
      //  //std::coutt << "LP Amount: "<< slider->getValue() << std::endl;
        *m_envPlugin.m_lpAmount = slider->getValue();
        
        
    }
    if(slider == m_envLPFilterView.m_lpFilterAttackSlider)
    {
       // //std::coutt << "LP Attack: "<< slider->getValue() << std::endl;
        *m_envPlugin.m_lpAttack = slider->getValue();
        
    }
    
    if(slider == m_envLPFilterView.m_lpFilterDecaySlider)
    {
      //  //std::coutt << "LP Decay: " << slider->getValue() << std::endl;
        *m_envPlugin.m_lpDecay = slider->getValue();
        
    }
    
    if(slider == m_envLPFilterView.m_lpFilterSustainSlider)
    {
      //  //std::coutt << "LP Sustain: " << slider->getValue() << std::endl;
        *m_envPlugin.m_lpSustain = slider->getValue();
    }
    
    if(slider == m_envLPFilterView.m_lpFilterReleaseSlider)
    {
     //   //std::coutt << "LP Release: " << slider->getValue() << std::endl;
        *m_envPlugin.m_lpRelease = slider->getValue();
        
    }
    
}

void EnvelopeController::updateEnvSlider()
///Updates UI components when UI reloaded
{
    const float hpEnvAmountSliderVal = m_envPlugin.get_hp_env_amount();
    
    if (hpEnvAmountSliderVal != (float) m_envHPFilterView.m_hpFilterAmountSlider->getValue() && ! isMouseButtonDown())
        m_envHPFilterView.m_hpFilterAmountSlider->setValue(hpEnvAmountSliderVal);
    
    const float hpEnvAttackSliderVal = m_envPlugin.get_hp_env_attack();
    
    if (hpEnvAttackSliderVal != (float) m_envHPFilterView.m_hpFilterAttackSlider->getValue() && ! isMouseButtonDown())
        m_envHPFilterView.m_hpFilterAttackSlider->setValue(hpEnvAttackSliderVal);
    
    const float hpEnvDecaySliderVal = m_envPlugin.get_hp_env_decay();
    
    if (hpEnvDecaySliderVal != (float) m_envHPFilterView.m_hpFilterDecaySlider->getValue() && ! isMouseButtonDown())
        m_envHPFilterView.m_hpFilterDecaySlider->setValue(hpEnvDecaySliderVal);
    
    const float hpEnvSustainSliderVal = m_envPlugin.get_hp_env_sustain();
    
    if (hpEnvSustainSliderVal != (float) m_envHPFilterView.m_hpFilterSustainSlider->getValue() && ! isMouseButtonDown())
        m_envHPFilterView.m_hpFilterSustainSlider->setValue(hpEnvSustainSliderVal);
    
    const float hpEnvReleaseSliderVal = m_envPlugin.get_hp_env_release();
    
    if (hpEnvReleaseSliderVal != (float) m_envHPFilterView.m_hpFilterReleaseSlider->getValue() && ! isMouseButtonDown())
        m_envHPFilterView.m_hpFilterReleaseSlider->setValue(hpEnvReleaseSliderVal);
    
    const float lpEnvAmountSliderVal = m_envPlugin.get_lp_env_amount();
    
    if (lpEnvAmountSliderVal != (float) m_envLPFilterView.m_lpFilterAmountSlider->getValue() && ! isMouseButtonDown())
        m_envLPFilterView.m_lpFilterAmountSlider->setValue(lpEnvAmountSliderVal);
    
    const float lpEnvAttackSliderVal = m_envPlugin.get_lp_env_attack();
    
    if (lpEnvAttackSliderVal != (float) m_envLPFilterView.m_lpFilterAttackSlider->getValue() && ! isMouseButtonDown())
        m_envLPFilterView.m_lpFilterAttackSlider->setValue(lpEnvAttackSliderVal);
    
    const float lpEnvDecaySliderVal = m_envPlugin.get_lp_env_decay();
    
    if (lpEnvDecaySliderVal != (float) m_envLPFilterView.m_lpFilterDecaySlider->getValue() && ! isMouseButtonDown())
        m_envLPFilterView.m_lpFilterDecaySlider->setValue(lpEnvDecaySliderVal);
    
    const float lpEnvSustainSliderVal = m_envPlugin.get_lp_env_sustain();
    
    if (lpEnvSustainSliderVal != (float) m_envLPFilterView.m_lpFilterSustainSlider->getValue() && ! isMouseButtonDown())
        m_envLPFilterView.m_lpFilterSustainSlider->setValue(lpEnvSustainSliderVal);
    
    const float lpEnvReleaseSliderVal = m_envPlugin.get_lp_env_release();
    
    if (lpEnvReleaseSliderVal != (float) m_envLPFilterView.m_lpFilterReleaseSlider->getValue() && ! isMouseButtonDown())
        m_envLPFilterView.m_lpFilterReleaseSlider->setValue(lpEnvReleaseSliderVal);
    
}
