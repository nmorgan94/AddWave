/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Poly.h"
#include "Effects.h"
//#include "ADSR.h"
//#include <string>


SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_amplitudes;
SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_attackValues;
SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_decayValues;
SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_sustainValues;
SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_releaseValues;

SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_pitchAmount;
SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_pitchAttackValues;
SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_pitchDecayValues;
SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_pitchSustainValues;
SynthAudioProcessor::ParameterVector SynthAudioProcessor::s_pitchReleaseValues;


//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()


#ifndef JucePlugin_PreferredChannelConfigurations
:

m_leftDelay(44100.0f*5.0f,0.0),
m_rightDelay(44100.0f*5.0f,0.0),
m_samplerate(44100),
m_distortion(0),
m_reverbBypass(false),
m_delayBypass(false),
m_filterBypass(false),
m_distortionBypass(false),
m_hpBypass(true),
m_lpBypass(true),
//isAddingFromMidiInput (false),
//m_distortionAmount(nullptr),

AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                
                )
#endif

///Initialises all variables and Parameters
{
    m_harmonic1Phase = 0;
    
    m_synth.setCurrentPlaybackSampleRate(44100.0);
    
    m_synth.addSound(new PolySound());
    
    m_currentWaveshape = WV_COMPLEX;
    

    m_reverbParams.wetLevel = 0.0;
    m_reverbParams.dryLevel = 1.0;
    m_reverbParams.width = 0.0;
    m_reverbParams.damping = 0.0;
    m_reverbParams.roomSize = 0.0;


    m_LPEnvOut = 20000;
    m_HPEnvOut = 20;
    

    m_powerButtonParam = new AudioParameterBool("powerButton", "PowerButton", true);
    addParameter(m_powerButtonParam);
    
    m_waveshapeParam = new AudioParameterInt("waveshape", "Waveshape", 1, 5, 1);
    addParameter(m_waveshapeParam);
    
    m_voicesParam = new AudioParameterInt("voices", "Voices", 1, 10, 3);
    addParameter(m_voicesParam);
  
    m_gainParam = new AudioParameterFloat("gain", "Gain", 0, 1, 1);
    addParameter(m_gainParam);
    
    
    m_delayTimeLeft = new AudioParameterFloat("delayTimeLeft", "DelayTimeLeft", 0.05, 5, 0.05);
    addParameter(m_delayTimeLeft);
    
    m_delayTimeRight = new AudioParameterFloat("delayTimeRight", "DelayTimeRight", 0.05, 5, 0.05);
    addParameter(m_delayTimeRight);
    
    m_delayFeedbackLeft = new AudioParameterFloat("delayFeedbackLeft", "DelayFeedbackLeft", 0.0, 0.8, 0.0);
    addParameter(m_delayFeedbackLeft);
    
    m_delayFeedbackRight = new AudioParameterFloat("delayFeedbackRight", "DelayFeebackRight", 0.0, 0.8, 0.0);
    addParameter(m_delayFeedbackRight);
    
    m_wet = new AudioParameterFloat("wetAmount", "WetAmount", 0.0f, 1, 0.0f);
    addParameter(m_wet);
    
    m_distortionAmount = new AudioParameterFloat("distortionAmount", "DistortionAmount", 0.0, 0.99, 0.0);
    addParameter(m_distortionAmount);
    
    m_lpAmount = new AudioParameterFloat("lpEnvelopeAmount", "LpEnvelopeAmount", 20, 20000, 2000);
    addParameter(m_lpAmount);
    m_lpAttack = new AudioParameterFloat("lpAttackAmount", "LpAttackAmount", 0.1, 5.0, 0.1);
    addParameter(m_lpAttack);
    m_lpDecay = new AudioParameterFloat("lpDecayAmount", "LpDecayAmount", 0.1, 5.0, 0.1);
    addParameter(m_lpDecay);
    m_lpSustain = new AudioParameterFloat("lpSustainAmount", "LpSustainAmount", 0.0, 1.0, 1.0);
    addParameter(m_lpSustain);
    m_lpRelease = new AudioParameterFloat("lpReleaseAmount", "LpReleaseAmount", 0.1, 5.000, 0.1);
    addParameter(m_lpRelease);

    m_hpAmount = new AudioParameterFloat("hpEnvelopeAmount", "HpEnvelopeAmount", 20, 20000, 20);
    addParameter(m_hpAmount);
    m_hpAttack = new AudioParameterFloat("hpAttackAmount", "HpAttackAmount", 0.1, 5.000, 0.1);
    addParameter(m_hpAttack);
    m_hpDecay = new AudioParameterFloat("hpDecayAmount", "HpDecayAmount", 0.1, 5.000, 0.1);
    addParameter(m_hpDecay);
    m_hpSustain = new AudioParameterFloat("hpSustainAmount", "HpSustainAmount", 0.0, 1.0, 1.0);
    addParameter(m_hpSustain);
    m_hpRelease = new AudioParameterFloat("hpReleaseAmount", "HpReleaseAmount", 0.1, 5.000, 0.1);
    addParameter(m_hpRelease);
    
    m_reverbWetParam = new AudioParameterFloat("reverbWetAmount", "ReverbWetAmount", 0.0, 1.0, 0.0);
    addParameter(m_reverbWetParam);
    m_reverbDryParam = new AudioParameterFloat("reverbDryAmount", "ReverbDryAmount", 0.0, 1.0, 1.0);
    addParameter(m_reverbDryParam);
    m_reverbDampingParam = new AudioParameterFloat("reverbDampingAmount", "ReverbDampingAmount", 0.0, 1.0, 0.0);
    addParameter(m_reverbDampingParam);
    m_reverbWidthParam = new AudioParameterFloat("reverbWidthAmount", "ReverbWidthAmount", 0.0, 1.0, 0.0);
    addParameter(m_reverbWidthParam);
    m_reverbRoomsizeParam = new AudioParameterFloat ("reverbRoomsizeAmount", "ReverbRoomsizeAmount", 0.0, 1.0, 0.0);
    addParameter(m_reverbRoomsizeParam);
    
    m_lowpassCutoffParam = new AudioParameterFloat("lowpassCutoffAmount", "LowpassCutoffAmount", 20.0, 20000.0, 20000.0);
    addParameter(m_lowpassCutoffParam);
    m_highpassCutoffParam = new AudioParameterFloat("highpassCutoffAmount", "HighpassCutoffmount", 20.0, 20000.0, 20.0);
    addParameter(m_highpassCutoffParam);
    
    m_hpBypassParam = new AudioParameterBool("hpBypassParam", "HpBypassParam", false);
    
    s_amplitudes.clear();
    s_attackValues.clear();
    s_decayValues.clear();
    s_sustainValues.clear();
    s_releaseValues.clear();
    s_pitchAmount.clear();
    s_pitchAttackValues.clear();
    s_pitchDecayValues.clear();
    s_pitchSustainValues.clear();
    s_pitchReleaseValues.clear();
    
    for(int n = 0 ; n < 16;++n){
        
        String harmonicAmplitudeName("amplitudeHarmonic");
        harmonicAmplitudeName += String(n);
        
        AudioParameterFloat* t =new AudioParameterFloat(harmonicAmplitudeName,harmonicAmplitudeName,0,1,1.0f/16) ;
        
        s_amplitudes.push_back(t  );
        addParameter(t);
        
        
        
        String attackName("attackHarmonic");
        attackName += String(n);
        
        AudioParameterFloat* a =new AudioParameterFloat(attackName,attackName,0.1,2,1.5) ;
        
        s_attackValues.push_back(a);
        addParameter(a);
        
        ////std::coutt << a->get() << std::endl;
        

        String decayName("decayHarmonic");
        decayName += String(n);
        
        AudioParameterFloat* d =new AudioParameterFloat(decayName,decayName,0.1,2,1.5) ;
        
        s_decayValues.push_back(d);
        addParameter(d);
        
        
        
        String sustainName("sustainHarmonic");
        sustainName += String(n);
        
        AudioParameterFloat* s =new AudioParameterFloat(sustainName,sustainName,0.0,1,0.5) ;
        
        s_sustainValues.push_back(s);
        addParameter(s);
        
        
        
        String releaseName("ReleaseHarmonic");
        releaseName += String(n);
        
        AudioParameterFloat* r = new AudioParameterFloat(releaseName,releaseName,0.1,2,1.5) ;
        
        s_releaseValues.push_back(r);
        addParameter(r);
        
        
        
        String pitchAmountName("PitchAmountHarmonic");
        pitchAmountName += String(n);
        
        AudioParameterFloat* pam =new AudioParameterFloat(pitchAmountName,pitchAmountName,-10000,10000,0) ;
        
        s_pitchAmount.push_back(pam);
        addParameter(pam);
        
        
        
        String pitchAttackName("PitchAttackHarmonic");
        pitchAttackName += String(n);
        
        AudioParameterFloat* pat =new AudioParameterFloat(pitchAttackName,pitchAttackName,0.1,5,2) ;
        
        s_pitchAttackValues.push_back(pat);
        addParameter(pat);
        
        
        
        String pitchDecayName("PitchDecayHarmonic");
        pitchDecayName += String(n);
        
        AudioParameterFloat* pd =new AudioParameterFloat(pitchDecayName,pitchDecayName,0.1,5,2) ;
        
        s_pitchDecayValues.push_back(pd);
        addParameter(pd);
        
        
        
        String pitchSustainName("PitchSustainHarmonic");
        pitchSustainName += String(n);
        
        AudioParameterFloat* ps =new AudioParameterFloat(pitchSustainName,pitchSustainName,0.1,5,2) ;
        
        s_pitchSustainValues.push_back(ps);
        addParameter(ps);
        
        
        
        String pitchReleaseName("PitchReleaseHarmonic");
        pitchReleaseName += String(n);
        
        AudioParameterFloat* pr =new AudioParameterFloat(pitchReleaseName,pitchReleaseName,0.1,5,2) ;
        
        s_pitchReleaseValues.push_back(pr);
        addParameter(pr);
     
    }
    
    m_synth.clearVoices();
    
        for(int n = 0 ; n < *m_voicesParam; ++n)
        {
            m_synth.addVoice(new PolyVoice( &s_amplitudes, &s_attackValues, &s_decayValues, &s_sustainValues,
                                       &s_releaseValues, &s_pitchAmount, &s_pitchAttackValues, &s_pitchDecayValues, &s_pitchReleaseValues, &s_pitchSustainValues  ));
        }
 
}

SynthAudioProcessor::~SynthAudioProcessor()
{
    for(int n = 0 ; n < s_amplitudes.size();++n){
            //delete s_amplitudes[n];
    }
    //delete s_amplitudes[1];
    //delete SynthAudioProcessor::ParameterVector;
}

//==============================================================================
const String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}



const String SynthAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String SynthAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool SynthAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool SynthAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool SynthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SynthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthAudioProcessor::getProgramName (int index)
{
    return String();
}

void SynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}



//==============================================================================
void SynthAudioProcessor::prepareToPlay (double sampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    m_synth.setCurrentPlaybackSampleRate(sampleRate);
    keyboardState.reset();

    
    //m_samplerate = sampleRate;
    
    sampleRate = m_samplerate;
    
   // //std::coutt << "samplerate: " << sampleRate << std::endl;
    
    m_leftDelay.clear();
    m_rightDelay.clear();
    
    m_reverb.setSampleRate(sampleRate);
    m_reverb.reset();
}

void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
     keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif



void SynthAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
///Master output functions
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
//    
//    PolyVoice::m_setTargetRatioA = m_attackCurve->get();
//    PolyVoice::m_setTargetRatioDR = m_decayReleaseCurve->get();
    

    
    HP_ADSR.setTargetRatioA(100);
    HP_ADSR.setTargetRatioDR(100);
    
    HP_ADSR.setAttackRate(*m_hpAttack * 100);
    HP_ADSR.setDecayRate(*m_hpAttack * 100);
    HP_ADSR.setSustainLevel(*m_hpSustain);
    HP_ADSR.setReleaseRate(*m_hpRelease * 100);
    
    m_HPEnvOut = 20 + ((HP_ADSR.process() * (m_hpAmount->get()-20)));
    
    //std::coutt << "m_HPEnvOut: " << m_HPEnvOut << std::endl;
    
    //std::coutt << LP_ADSR.get_attack_time() <<std::endl;
    
    LP_ADSR.setTargetRatioA(100);
    LP_ADSR.setTargetRatioDR(100);
    
    LP_ADSR.setAttackRate(*m_lpAttack * 100);
    LP_ADSR.setDecayRate(*m_lpDecay * 100);
    LP_ADSR.setSustainLevel(*m_lpSustain);
    LP_ADSR.setReleaseRate(*m_lpRelease * 100);
    
    //std::cout << "attack: " << LP_ADSR.get_attack_time() << std::endl;
    //std::cout << "decay: " << LP_ADSR.get_attack_time() << std::endl;
    //std::cout << "sustain: " << LP_ADSR.get_() << std::endl;
    //std::cout << "release: " << LP_ADSR.get_attack_time() << std::endl;
    
    
    m_LPEnvOut = 20 + ((LP_ADSR.process() * (m_lpAmount->get()-20)));
    
    
   //std::coutt << "m_LPEnvOut: " << m_LPEnvOut << std::endl;
    

    if(!*m_powerButtonParam)return;

    
    const int numSamples = buffer.getNumSamples();
    
    keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);
    
    
    int time =0;
    
    for( MidiBuffer::Iterator it(midiMessages);it.getNextEvent(midiEnv, time);)
    {
        
        if (midiEnv.isNoteOn()){
//            static int numbernoteOn(0);
//            //std::coutt << "Note on  " << numbernoteOn << std::endl;
            LP_ADSR.gate(true);
            HP_ADSR.gate(true);
//            ++numbernoteOn;
        }
        else if (midiEnv.isNoteOff()){
         //   static int numbernoteOff(0);
       //     //std::coutt << "Note Off " << numbernoteOff << std::endl;
            LP_ADSR.gate(false);
            HP_ADSR.gate(false);
//            ++numbernoteOff;
        }
        
    }

    m_synth.renderNextBlock(buffer,midiMessages,0,numSamples);
    
    m_reverb.setParameters(m_reverbParams);
    
    m_LPcoeff = IIRCoefficients::makeLowPass(44100, m_lowpassCutoffParam->get(), 3);
    m_leftLowPassFilter.setCoefficients(m_LPcoeff);
    m_rightLowPassFilter.setCoefficients(m_LPcoeff);
    
    m_HPcoeff = IIRCoefficients::makeHighPass(44100, m_highpassCutoffParam->get(), 3);
    m_leftHighPassFilter.setCoefficients(m_HPcoeff);
    m_rightHighPassFilter.setCoefficients(m_HPcoeff);
    
    m_LPEnvCoeff = IIRCoefficients::makeLowPass(44100, m_LPEnvOut, 3);
    m_leftLowPassEnvelope.setCoefficients(m_LPEnvCoeff);
    m_rightLowPassEnvelope.setCoefficients(m_LPEnvCoeff);
    
    m_HPEnvCoeff = IIRCoefficients::makeHighPass(44100, m_HPEnvOut, 3);
    m_leftHighPassEnvelope.setCoefficients(m_HPEnvCoeff);
    m_rightHighPassEnvelope.setCoefficients(m_HPEnvCoeff);
    
    ////std::coutt << "Lowpass Env Cuttoff: " << m_LPEnvOut << std::endl;
    

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    //int numSamples = buffer.getNumSamples();
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, numSamples);
    
    
    float* LeftChannel = buffer.getWritePointer(0);
    float* RightChannel = buffer.getWritePointer(1);
    
    if(!m_hpBypass){
        m_leftHighPassEnvelope.processSamples(LeftChannel, numSamples);
        m_rightHighPassEnvelope.processSamples(RightChannel, numSamples);
    }
    
    if(!m_lpBypass){
        m_leftLowPassEnvelope.processSamples(LeftChannel, numSamples);
        m_rightLowPassEnvelope.processSamples(RightChannel, numSamples);
    }
    
    
    float leftT(0),rightT(0);
    
    for (int i = 0; i < numSamples; ++i)
    {
        
        currentLeft = buffer.getSample(0, i);
        currentRight = buffer.getSample(1, i);
        
        
        
        if(!m_delayBypass){
            
            m_leftDelay.write(currentLeft,(*m_delayFeedbackLeft) );
            m_rightDelay.write(currentRight,(*m_delayFeedbackRight) );
            
            leftT = m_leftDelay.read(m_samplerate * (*m_delayTimeLeft))+ currentLeft;
            rightT = m_rightDelay.read(m_samplerate * (*m_delayTimeRight)) + currentRight;
            
            currentLeft = leftT;
            currentRight = rightT;
        }
        
        if(!m_distortionBypass){
            currentLeft = m_distortion.distort(currentLeft, m_distortionAmount->get());
            currentRight =  m_distortion.distort(currentRight, m_distortionAmount->get());
        }
        LeftChannel[i] += currentLeft;
        RightChannel[i] += currentRight;
    }
    
    if(!m_filterBypass){
        m_leftLowPassFilter.processSamples(LeftChannel,numSamples);
        m_rightLowPassFilter.processSamples(RightChannel,numSamples);
        
        m_leftHighPassFilter.processSamples(LeftChannel, numSamples);
        m_rightHighPassFilter.processSamples(RightChannel, numSamples);
    }
    if(!m_reverbBypass){
        m_reverb.processStereo(LeftChannel, RightChannel, numSamples);
    }
    
    
    buffer.applyGain(m_gainParam->get());
    
}




//==============================================================================
bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml ("ParameterTweaker");
    
    for (int i = 0; i < getNumParameters(); ++i)
        if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
            xml.setAttribute (p->paramID, p->getValue());
    
    copyXmlToBinary (xml, destData);
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("ParameterTweaker"))
        {
            
            // Now reload our parameters..
            for (int i = 0; i < getNumParameters(); ++i)
                if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
                    p->setValue ((float) xmlState->getDoubleAttribute (p->paramID, p->getValue()));
        }
    }

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}

void SynthAudioProcessor::set_num_voices(int voices){
    *m_voicesParam = jlimit(1, 10, voices);
    m_synth.clearVoices();
    
    for(int n = 0 ; n < *m_voicesParam; ++n)
    {
    
    m_synth.addVoice(new PolyVoice( &s_amplitudes, &s_attackValues, &s_decayValues, &s_sustainValues,
                                   &s_releaseValues, &s_pitchAmount, &s_pitchAttackValues, &s_pitchDecayValues, &s_pitchReleaseValues, &s_pitchSustainValues  ));
    }
}

int SynthAudioProcessor::get_num_voices(){
    ////std::coutt << "Num Voices = " << *m_voicesParam << std::endl;
    return m_voicesParam->get();
}

void SynthAudioProcessor::set_main_gain(float gain){
    
    *m_gainParam = jlimit(0.0f, 1.0f, gain);
    
}

float SynthAudioProcessor::get_main_gain(){
    ////std::coutt << "main gain: " << m_gain << std::endl;
    return m_gainParam->get();
}

float SynthAudioProcessor::get_distortionAmount()
{
    return m_distortionAmount->get();
}

float SynthAudioProcessor::get_reverb_dry()
{
    return m_reverbDryParam->get();
}

float SynthAudioProcessor::get_reverb_wet()
{
    return m_reverbWetParam->get();
}

float SynthAudioProcessor::get_reverb_damping()
{
    return m_reverbDampingParam->get();
}

float SynthAudioProcessor::get_reverb_width()
{
    return m_reverbWidthParam->get();
}

float SynthAudioProcessor::get_reverb_roomsize()
{
    return m_reverbRoomsizeParam->get();
}

float SynthAudioProcessor::get_left_delay_time()
{
    return m_delayTimeLeft->get();
}

float SynthAudioProcessor::get_right_delay_time()
{
    return m_delayTimeRight->get();
}

float SynthAudioProcessor::get_left_delay_feedback()
{
    return m_delayFeedbackLeft->get();
}

float SynthAudioProcessor::get_right_delay_feedback()
{
    return m_delayFeedbackRight->get();
}

float SynthAudioProcessor::get_lowpass_cutoff()
{
    return m_lowpassCutoffParam->get();
}

float SynthAudioProcessor::get_highpass_cutoff()
{
    return m_highpassCutoffParam->get();
}

int SynthAudioProcessor::get_waveshapeNumber()
{
    return m_waveshapeParam->get();
}

int SynthAudioProcessor::get_powerButton_val()
{
    return m_powerButtonParam->get();
}

float SynthAudioProcessor::get_hp_env_amount()
{
    return m_hpAmount->get();
}

float SynthAudioProcessor::get_hp_env_attack()
{
    return m_hpAttack->get();
}

float SynthAudioProcessor::get_hp_env_decay()
{
    return m_hpDecay->get();
}

float SynthAudioProcessor::get_hp_env_sustain()
{
    return m_hpSustain->get();
}

float SynthAudioProcessor::get_hp_env_release()
{
    return m_hpRelease->get();
}

float SynthAudioProcessor::get_lp_env_amount()
{
    return m_lpAmount->get();
}

float SynthAudioProcessor::get_lp_env_attack()
{
    return m_lpAttack->get();
    ////std::coutt << "lp attack" << m_lpAttack->get() << std::endl;
}

float SynthAudioProcessor::get_lp_env_decay()
{
    return m_lpDecay->get();
}

float SynthAudioProcessor::get_lp_env_sustain()
{
    return m_lpSustain->get();
}

float SynthAudioProcessor::get_lp_env_release()
{
    return m_lpRelease->get();
}

bool SynthAudioProcessor::get_hp_Bypass()
{
    return m_hpBypassParam->get();
}


void SynthAudioProcessor::set_hp_Bypass(bool hpBypass)
{
    *m_hpBypassParam = m_hpBypass;
}


void SynthAudioProcessor::set_lowpass_cutoff(float LPcut)
///Sets lowpass cutoff frequency
/*!
 \param LPcut Frequency at which lowpass filters audio
 */
{
    *m_lowpassCutoffParam = jlimit(20.0f, 20000.0f, LPcut);
}

void SynthAudioProcessor::set_highpass_cutoff(float HPcut)
///Sets highpass cutoff frequency
/*!
 \param HPcut Frequency at which highpass filters audio
 */
{
    
    *m_highpassCutoffParam = jlimit(20.0f, 20000.0f, HPcut);
}

void SynthAudioProcessor::set_reverb_wet(float ReverbWet)
///Sets Reverb wet amount
/*!
 \param ReverbWet Reverb Amount added
 */
{
    *m_reverbWetParam = jlimit(0.0f, 1.0f, ReverbWet);
    m_reverbParams.wetLevel = *m_reverbWetParam;
}

void SynthAudioProcessor::set_reverb_dry(float ReverbDry)
///Sets Dry mix
/*!
 \param ReverbDry Dry mix level
 */
{
    
    *m_reverbDryParam = jlimit (0.0f, 1.0f, ReverbDry);
    m_reverbParams.dryLevel = *m_reverbDryParam;
}

void SynthAudioProcessor::set_reverb_width(float ReverbWidth)
///Sets Reverb Width
/*!
 \param ReverbWidth Width of reverb
 */
{
    *m_reverbWidthParam = jlimit(0.0f, 1.0f, ReverbWidth);
    m_reverbParams.width = *m_reverbWidthParam;
}

void SynthAudioProcessor::set_reverb_roomsize(float ReverbRoomSize)
///Sets Reverb Size
/*!
 \param ReverbRoomSize Size of Reverb
 */
{
    
    *m_reverbRoomsizeParam = jlimit(0.0f, 1.0f, ReverbRoomSize);
    m_reverbParams.roomSize = *m_reverbRoomsizeParam;
    
}

void SynthAudioProcessor::set_reverb_damping(float ReverbDamping)
///Sets Reverb high frequency feedback
/*!
 \param ReverbDamping Damping amount
 */
{
    
    *m_reverbDampingParam = jlimit(0.0f, 1.0f, ReverbDamping);
    m_reverbParams.damping = *m_reverbDampingParam;
    
}


void SynthAudioProcessor::set_mute_state(bool state)
///Kill Switch
{
    *m_powerButtonParam = state;
    
}

void SynthAudioProcessor::set_wave_shape(WaveShape shape)
///Sets which waveshape to load
{
    
    switch (shape) {
        case WV_COMPLEX:
            PolyVoice::get_wavetable().clear();
            PolyVoice::get_wavetable().fill_complexSin();
            
            break;
        case WV_SAW:
            PolyVoice::get_wavetable().clear();
            PolyVoice::get_wavetable().fill_saw();
            break;
        case WV_SQUARE:
            PolyVoice::get_wavetable().clear();
            PolyVoice::get_wavetable().fill_square();
            break;
        case WV_SIN:
            PolyVoice::get_wavetable().clear();
            PolyVoice::get_wavetable().fill_sin();
            break;
        case WV_TRIANGLE:
            PolyVoice::get_wavetable().clear();
            PolyVoice::get_wavetable().fill_triangle();
            break;
    }
    
}


void SynthAudioProcessor::set_square()
///Sets Square wave
{
    
    set_wave_shape(WaveShape::WV_SQUARE);
    *m_waveshapeParam = 2;
    
}

void SynthAudioProcessor::set_saw()
///Sets Saw wave
{
    set_wave_shape(WaveShape::WV_SAW);
    *m_waveshapeParam = 1;
}

void SynthAudioProcessor::set_complex_sin()
///Sets Complex Sin wave
{
    set_wave_shape(WaveShape::WV_COMPLEX);
    *m_waveshapeParam = 3;
    
}

void SynthAudioProcessor::set_sin()
///Sets Sin wave
{
    set_wave_shape(WaveShape::WV_SIN);
    *m_waveshapeParam = 4;
}

void SynthAudioProcessor::set_triangle()
///Sets Triangle wave
{
    set_wave_shape(WaveShape::WV_TRIANGLE);
    *m_waveshapeParam = 5;
}



