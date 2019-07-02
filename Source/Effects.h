/*
  ==============================================================================

    Effects.h
    Created: 13 Apr 2017 2:03:24pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef EFFECTS_H_INCLUDED
#define EFFECTS_H_INCLUDED

#include "WaveTable.h"
#include <math.h>
#include <stdlib.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "ADSR.h"
#include <vector>

class Delay {

    float* m_delayBuffer;
    int m_maxDelay;
    int m_writePos;
    float m_readPos;
    float m_dry;
    float m_wet;
    float nextSample;
    float outputSample;
    float fraction;
    int readInter;
    
public:

    
    Delay(int delaySize, float wet):
    ///This is where the delay is created
    /*!
     \param delaySize Maximum delay size
     */
    
    m_maxDelay(delaySize),
    m_writePos(0),
    m_readPos(0),
    m_wet(wet),
    m_dry(1-wet)
    
    {
        m_delayBuffer = new float [m_maxDelay];
       // clear();
    }
    
    ~Delay()
    {
//        if(m_delayBuffer != nullptr){
//            delete[] m_delayBuffer;
//        }
    }
    
    void clear()
    ///This clears the delay buffer
    {
        for(int n = 0; n < m_maxDelay; ++n)
        {
            m_delayBuffer[n] = 0.0f;
        }
    }
    
    float read (float time)
    {
        m_readPos = m_writePos - time;
        
        if(m_readPos < 0) {m_readPos += m_maxDelay;}
        if(m_readPos > m_maxDelay) {m_readPos -= m_maxDelay;}
        outputSample = m_delayBuffer[(int)m_readPos];
    
        return outputSample;
    }
    
    void write(float sample, float feedback)
    {
        m_delayBuffer[m_writePos ] = sample + (m_delayBuffer[m_writePos] * feedback);
        
        ++m_writePos;
        
        if(m_writePos >= m_maxDelay)
        {
            m_writePos = 0;
        }
    }
    
    float delayAmount(float drySample, float wetSample)
    {
        return (drySample * m_dry) + (wetSample * m_wet);
    }
    
    float get_delay_size()
    {
        return m_maxDelay;
    }
    
    void set_delay_size(float delaySize)
    ///Sets the size of the delay
    /*!
     \param delaySize Maximum delay size
     */
    {
        m_maxDelay = delaySize;
    }
    
};

class Distortion {
    float m_amount;
    
    
public:
    
    Distortion(float thresh):
    m_amount(thresh)
    
    {
        
    }

    float distort(float sample, float thresh)
    ///This is how the distorion is implimented
    /*!
     \param sample Sample to distort
     */
    /*!
     \param thresh Aggression of distortion
     */
    {
        
        float output;
        float input = sample;
        float k = 2*thresh/ (1-thresh);
        
        output = ((1+k)*input/ (1+k*std::abs(input)));
        
        return output;
        
    }
    
    void set_distortion_amount(float thresh)
    ///Sets the amount of the threshold
    {
        m_amount = thresh;
    }
    
    float get_distortion_amount(float thresh)
    ///Returns the amount of the threshold
    {
        return m_amount;
    }
    
};

#endif  // EFFECTS_H_INCLUDED
