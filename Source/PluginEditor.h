/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "MultiSlider.h"
#include "EffectController.h"
#include "ReverbControlView.h"
#include "FilterControlView.h"
#include "DelayControlView.h"
#include "DistortionControlView.h"
#include "CustomLook.h"
#include "EnvelopeController.h"
#include "EnvelopeHPFView.h"
#include "EnvelopeLPFView.h"

//==============================================================================
/**
*/
class SynthAudioProcessorEditor  : public AudioProcessorEditor,
                                   private Slider::Listener,
                                   private Button::Listener,
                                   private ComboBox::Listener,
                                   private Timer


{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    
    
   
    
    ~SynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
private:
    
    LookAndFeel_V3 nickFeel;
    
    //MidiKeyboardState keyboardState;
    MidiKeyboardComponent midiKeyboard;
    
    void sliderValueChanged (Slider* slider) override;
    
    void comboBoxChanged (ComboBox* box) override;
    
    void buttonClicked (Button* button) override;
    
    void loadParameters (XmlElement* element);
    
    void set_num_harmonics (int harmonics);
    
    int get_num_harmonics();
    
    void updateUI();
    
    float get_voice_comboBox_Num();
    
    void timerCallback();
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthAudioProcessor& processor;
    
    
    Slider mainVol;
    Label mainVolLabel;
    TextButton powerButton;
    ScopedPointer<TabbedComponent> tab;
    
    Slider AttackCurve;
    Label ADSRCurveLabel;
    
    Slider DecayReleaseCurve;
    
    ComboBox comboBox;
    
    ComboBox presetSelect;
    TextButton presetSave;
    TextButton presetLoad;
    
    ComboBox m_harmonicNumber;
    
    ComboBox m_voiceNumber;

    int m_numHarmonics;
    
    ScopedPointer<MultiSlider> m_ampMultiSlider;
    ScopedPointer<MultiSlider> m_attackMultiSlider;
    ScopedPointer<MultiSlider> m_decayMultiSlider;
    ScopedPointer<MultiSlider> m_sustainMultiSlider;
    ScopedPointer<MultiSlider> m_releaseMultiSlider;
    
    ScopedPointer<MultiSlider> m_pitchEnvelopeMultiSlider;
    
    SynthAudioProcessor& m_attachedProcessor;

    ScopedPointer<EffectsController> m_effectController;
    ScopedPointer<TabbedComponent> m_effectTabView;
    ScopedPointer<FilterControlView> m_filterView;
    ScopedPointer<ReverbControlView> m_reverbView;
    ScopedPointer<DelayControlView> m_delayView;
    ScopedPointer<DistortionControlView> m_distortionView;
    
    ScopedPointer<EnvelopeController> m_envelopeController;
    ScopedPointer<TabbedComponent> m_envTabView;

    ScopedPointer<EnvelopeHPFilterView> m_envHPFilterView;
    ScopedPointer<EnvelopeLPFilterView> m_envLPFilterView;

    CustomLook_V2 m_customLook2;
    
    Customtab m_customTab;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED


