/*
 ==============================================================================
 
 Poly.h
 Created: 22 Feb 2017 12:50:11pm
 Author:  Nicholas Morgan
 
 ==============================================================================
 */

#ifndef POLY_H_INCLUDED
#define POLY_H_INCLUDED
#include "WaveTable.h"
#include "ADSR.h"
//#include "MultiSlider.h"
#include <vector>
#include <memory>
#include "Effects.h"

#include "PluginProcessor.h"


class PolySound : public SynthesiserSound
{
    
public:
    
    PolySound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override    { return true; };
    bool appliesToChannel (int /*midiChannel*/) override    { return true; };
 
};


///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


class PolyVoice : public SynthesiserVoice
///Used for implimenting polyphony

{
    typedef Phasor* PhasorPtr;
    typedef std::vector<PhasorPtr> PhasorVector;
    
    PhasorVector m_phasors;

    static WaveTable* m_table;

    float m_midiVelocity;
    float m_frequency;
    float m_sampleRate;
    float tailOff;
    float m_currentVelocity;

    typedef std::vector<ADSR> ADSRVector;
    ADSRVector m_amplitudeEnvelopes;
    
    typedef std::vector<ADSR> PitchEnvVector;
    PitchEnvVector m_pitchEnvelopes;

    int m_numHarmonics = 16;
    std::vector<float> m_harmonics;
    
//    float m_attackSeconds;
//    float m_decaySeconds;
//    float m_sustainAmount;
//    float m_releaseSeconds;
    
    
    
    float m_delayTimeLeft;
    float m_delayFeedbackLeft;
    
    float m_distortionAmount;
    
   // bool* m_pitchBypass;
    
    bool m_pitchBypass = false;
    
//    enum MidiCC{
//        ATTACK = 20,
//        DECAY,
//        SUSTAIN,
//        RELEASE
//    };
    

public:
    static float m_setTargetRatioA;
    static float m_setTargetRatioDR;

    
private:
    SynthAudioProcessor::ParameterVector* m_harmonicAmplitudes;
    
    SynthAudioProcessor::ParameterVector* m_attackValues;
    SynthAudioProcessor::ParameterVector* m_decayValues;
    SynthAudioProcessor::ParameterVector* m_sustainValues;
    SynthAudioProcessor::ParameterVector* m_releaseValues;
    
    
    SynthAudioProcessor::ParameterVector* m_pitchAmount;
    
    SynthAudioProcessor::ParameterVector* m_pitchAttackValues;
    SynthAudioProcessor::ParameterVector* m_pitchDecayValues;
    SynthAudioProcessor::ParameterVector* m_pitchSustainValues;
    SynthAudioProcessor::ParameterVector* m_pitchReleaseValues;
    
    
    
public:
    
    static WaveTable& get_wavetable()
    {
        return *m_table;
        
    }
    
    PolyVoice(SynthAudioProcessor::ParameterVector* harmonicParams,SynthAudioProcessor::ParameterVector* attackParams, SynthAudioProcessor::ParameterVector* decayParams, SynthAudioProcessor::ParameterVector* sustainParams, SynthAudioProcessor::ParameterVector* releaseParams,  SynthAudioProcessor::ParameterVector* pitchAmountParams, SynthAudioProcessor::ParameterVector* pitchAttackParams, SynthAudioProcessor::ParameterVector* pitchDecayParams, SynthAudioProcessor::ParameterVector* pitchSustainParams,
              SynthAudioProcessor::ParameterVector* pitchReleaseParams):
    
    m_harmonicAmplitudes(harmonicParams),
    m_attackValues(attackParams),
    m_decayValues(decayParams),
    m_sustainValues(sustainParams),
    m_releaseValues(releaseParams),

    m_pitchAmount(pitchAmountParams),
    m_pitchAttackValues(pitchAttackParams),
    m_pitchDecayValues(pitchDecayParams),
    m_pitchSustainValues(pitchSustainParams),
    m_pitchReleaseValues(pitchReleaseParams)
    
        {
        m_sampleRate = 44100.0f;
        //m_midiVelocity = 0;
        
        float root = 440;
        
        for(int n = 0 ; n < m_numHarmonics; ++n)
        {
            m_harmonics.push_back(0);
            
        }

        m_harmonics[0] = 0.0625;
        m_harmonics[1] = 0.125;
        m_harmonics[2] =0.25;
        m_harmonics[3] = 0.5;
        m_harmonics
        [4] = 1;
        
        for(int n = 5 ; n < m_numHarmonics;++n)
        {
            m_harmonics[n] = n;
        }

        
        for(int n = 0;n < m_numHarmonics; ++n)
        {
            m_phasors.push_back(new Phasor(44100,root * m_harmonics[n] ));
            m_amplitudeEnvelopes.push_back( ADSR());
            m_pitchEnvelopes.push_back(ADSR());
   
        }
        
        
        m_table = new WaveTable(512);
        
        m_table->fill_saw();
        
        for(int n = 0 ; n < m_numHarmonics;++n)
        {
            m_amplitudeEnvelopes[n].setTargetRatioA(100);
            m_amplitudeEnvelopes[n].setTargetRatioDR(100);
        }
        
    }
    
    ~PolyVoice()
    {
        
        for(int n = 0;n < m_numHarmonics; ++n){
            delete m_phasors[n];
        }
    }
    
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<PolySound*> (sound) !=nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* /*sound*/, int currentPitchWheelPosition)
    {
        tailOff = 0;
        
        m_frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        m_midiVelocity = velocity;
        
        for(int n = 0;n < m_numHarmonics; ++n)
        {
            m_phasors[n]->set_frequency(m_harmonics[n] * m_frequency);
      //      //std::coutt  << m_phasors[n]->get_frequency() <<std::endl;
        }
       
        
        for(int n = 0; n < m_numHarmonics;++n)
        {
            
            m_amplitudeEnvelopes[n].gate(true);
            m_pitchEnvelopes[n].gate(true);
            
        }
        
    }
    

    void stopNote (float velocity, bool allowTailOff) override
    ///For implimenting release of envelope
    {
        static int stopNote(0);
        
        
        //std::coutt << m_currentVelocity << " vel " << velocity <<std::endl;
    
        
        //m_midiVelocity = 1;
        //m_midiVelocity = velocity;
        // velocity = m_currentVelocity;
        // velocity = 0;
        allowTailOff = true;
        for(int n = 0; n < m_numHarmonics;++n){

        
            m_amplitudeEnvelopes[n].gate(false);
            m_pitchEnvelopes[n].gate(false);
            
        }
        
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.
            
            if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
                // stopNote method could be called more than once.
            {
            tailOff = 1.0;
            }
            
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..
            
            clearCurrentNote();
        }
        
    }
    
    
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    ///Creates a block of samples to be played
    {
        
        float currentSample;

        for(int n = 0 ; n < m_numHarmonics;++n)
        {
            m_amplitudeEnvelopes[n].setAttackRate( (* m_attackValues->at(n) )  * (60000) );
            m_amplitudeEnvelopes[n].setDecayRate(  (*m_decayValues->at(n)  ) * 60000);
            m_amplitudeEnvelopes[n].setSustainLevel (*m_sustainValues->at(n));
            m_amplitudeEnvelopes[n].setReleaseRate(  (*m_releaseValues->at(n)  ) * 60000);
            
            m_pitchEnvelopes[n].setAttackRate( (* m_pitchAttackValues->at(n) )  * 60000);
            m_pitchEnvelopes[n].setDecayRate(  (*m_pitchDecayValues->at(n)  ) * 60000);
            m_pitchEnvelopes[n].setSustainLevel (*m_pitchSustainValues->at(n));
            m_pitchEnvelopes[n].setReleaseRate(  (*m_pitchReleaseValues->at(n)  ) * 60000);
        }

        float val = 0;
        
        
        for(int sample = startSample; sample < numSamples;++sample )
        {
            
            for(int channel = 0; channel < outputBuffer.getNumChannels();++channel)
            {
                
                float* currentBuffer = outputBuffer.getWritePointer(channel);
                
                currentSample = 0;
                
                int numFinished = 0;
                
                for(int n = 0;n < m_numHarmonics; ++n)
                {
                    if(!m_pitchBypass)
                    {
                    
                    m_phasors[n]->set_frequency( m_harmonics[n]*  m_frequency + (m_pitchEnvelopes[n].process() * (*m_pitchAmount->at(n))));
                    
                    }
                    
                    val =   m_table->linear_lookup( m_phasors[n]->get_phase() * m_table->get_table_size())  * m_amplitudeEnvelopes[n].process();
                    
                    val *=   (*m_harmonicAmplitudes->at(n));
                  
                    val *= m_midiVelocity;;
                    
                    currentSample += val;
                    
                    
                    if(m_amplitudeEnvelopes[n].getOutput() <=0)
                    {
                        ++numFinished;
                    }
                    
                }
                currentBuffer[sample] += currentSample;
                
                
                if(numFinished >= m_numHarmonics)
                {
                    clearCurrentNote();
                }

                
            }
            
            for(int n = 0;n < m_numHarmonics; ++n)
            {
                m_phasors[n]->tick();
            }
            
        }
        //std::cout << m_amplitudeEnvelopes[0].getOutput() << std::endl;
        
    }
    
    
    
    bool set_pitch_bypass(int bypass)
    {
   //     m_pitchBypass = bypass;
    }
    
    
    
    virtual void pitchWheelMoved (int newPitchWheelValue)
    {
        
    };
    
    
    
    /** Called to let the voice know that a midi controller has been moved.
     This will be called during the rendering callback, so must be fast and thread-safe.
     */
    virtual void controllerMoved (int controllerNumber, int newControllerValue)
    {   

        
    }

};


WaveTable* PolyVoice::m_table = 0;






#endif  // POLY_H_INCLUDED
