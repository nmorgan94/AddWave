/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Effects.h"
#include <vector>
#include <memory>
//#include <string>

class Phasor;
class WaveTable;
class ADSR;


//==============================================================================
/**
*/
class SynthAudioProcessor  : public AudioProcessor
                             //public Slider::Listener
                               // private MidiInputCallback,
                                //private MidiKeyboardStateListener
{
public:
    //All functions and classes etc of master output
    enum WaveShape{
        WV_COMPLEX = 0,
        WV_SQUARE,
        WV_SAW,
        WV_SIN,
        WV_TRIANGLE
    };
    

    enum ADSRCurve{
        AttackCurve = 0,
        DecayReleaseCurve
    };
  
    
    typedef std::vector<AudioParameterFloat*> ParameterVector;
    static ParameterVector s_amplitudes;
    static ParameterVector s_attackValues;
    static ParameterVector s_decayValues;
    static ParameterVector s_sustainValues;
    static ParameterVector s_releaseValues;
    static ParameterVector s_pitchAmount;
    static ParameterVector s_pitchAttackValues;
    static ParameterVector s_pitchDecayValues;
    static ParameterVector s_pitchSustainValues;
    static ParameterVector s_pitchReleaseValues;
    
private:
    WaveShape m_currentWaveshape;
    ADSRCurve m_currentCurve;
    Synthesiser m_synth;
    Reverb m_reverb;
    Reverb::Parameters m_reverbParams;
    Delay m_leftDelay,m_rightDelay;
    
    float m_harmonic1Phase;
   
    float m_samplerate;
 
    float currentLeft;
    float currentRight;

    double m_LPEnvOut;
    double m_HPEnvOut;
    
    
    float  m_reverbWetLevel;
    float  m_reverbDryLevel;
    float  m_reverbWidthLevel;
    float  m_reverbRoomSize;
    float  m_reverbDamping;

    
    IIRCoefficients m_LPcoeff;
    IIRCoefficients m_LPEnvCoeff;
    IIRFilter m_leftLowPassFilter,m_rightLowPassFilter;
    IIRFilter m_leftLowPassEnvelope, m_rightLowPassEnvelope;
    
    IIRCoefficients m_HPcoeff;
    IIRCoefficients m_HPEnvCoeff;
    IIRFilter m_leftHighPassFilter, m_rightHighPassFilter;
    IIRFilter m_leftHighPassEnvelope, m_rightHighPassEnvelope;

  
    //bool m_muted;
    
    Distortion m_distortion;
    
    
    
public:
    //==============================================================================
    SynthAudioProcessor();
    
    AudioParameterBool* m_powerButtonParam;
    
    AudioParameterFloat* m_gainParam;
    
    AudioParameterInt* m_waveshapeParam;
    
    AudioParameterInt* m_voicesParam;
    
    AudioParameterFloat* m_delayTimeLeft;
    AudioParameterFloat* m_delayTimeRight;
    AudioParameterFloat* m_delayFeedbackLeft;
    AudioParameterFloat* m_delayFeedbackRight;
    AudioParameterFloat* m_wet;
    
    AudioParameterFloat* m_distortionAmount;
    
    AudioParameterFloat* m_reverbWetParam;
    AudioParameterFloat* m_reverbDryParam;
    AudioParameterFloat* m_reverbWidthParam;
    AudioParameterFloat* m_reverbDampingParam;
    AudioParameterFloat* m_reverbRoomsizeParam;
    
    AudioParameterFloat* m_lowpassCutoffParam;
    AudioParameterFloat* m_highpassCutoffParam;
    
    AudioParameterFloat* m_hpAmount;
    AudioParameterFloat* m_lpAmount;
    AudioParameterFloat* m_hpAttack;
    AudioParameterFloat* m_lpAttack;
    AudioParameterFloat* m_hpDecay;
    AudioParameterFloat* m_lpDecay;
    AudioParameterFloat* m_hpSustain;
    AudioParameterFloat* m_lpSustain;
    AudioParameterFloat* m_hpRelease;
    AudioParameterFloat* m_lpRelease;
    
    AudioParameterBool* m_hpBypassParam;

    MidiMessage midiEnv;
    
    ADSR LP_ADSR;
    ADSR HP_ADSR;
    
    bool m_reverbBypass,m_delayBypass,m_filterBypass, m_distortionBypass;
    bool m_lpBypass, m_hpBypass;
    
    ~SynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;
    
    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    MidiKeyboardState keyboardState;

   // AudioParameterFloat* Amp;

    void set_mute_state(bool state);
    
    void set_main_gain(float gain);
    void set_lowpass_cutoff(float LPcut);
    void set_highpass_cutoff(float HPcut);
    void set_reverb_wet(float ReverbWet);
    void set_reverb_dry(float ReverbDry);
    void set_reverb_width (float ReverbWidth);
    void set_reverb_roomsize (float ReverbRoomSize);
    void set_reverb_damping (float ReverbDamping);
    void set_distortionAmount (float DistortionAmount);
    
    float get_main_gain();
    float get_distortionAmount();
    float get_reverb_wet();
    float get_reverb_dry();
    float get_reverb_width();
    float get_reverb_roomsize();
    float get_reverb_damping();
    float get_left_delay_time();
    float get_right_delay_time();
    float get_left_delay_feedback();
    float get_right_delay_feedback();
    float get_lowpass_cutoff();
    float get_highpass_cutoff();
    int get_waveshapeNumber();
    int get_powerButton_val();
    
    float get_ampMultislider_val();
    
    float get_hp_env_amount();
    float get_hp_env_attack();
    float get_hp_env_decay();
    float get_hp_env_sustain();
    float get_hp_env_release();
    
    float get_lp_env_amount();
    float get_lp_env_attack();
    float get_lp_env_decay();
    float get_lp_env_sustain();
    float get_lp_env_release();
    
    bool get_hp_Bypass();
    
    void set_hp_Bypass(bool);
    
    void set_wave_shape(WaveShape shape);
    void set_square();
    void set_complex_sin();
    void set_saw();
    void set_sin();
    void set_triangle();
    
    void set_ADSR_curve(ADSRCurve curve);
    void set_attack_curve();
    void set_decay_release_curve();
    
    void set_num_voices(int voices);
    void set_num_harmonics(int);
    
    int get_num_voices();
    
    void refresh();
    

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessor)
};




#endif  // PLUGINPROCESSOR_H_INCLUDED
