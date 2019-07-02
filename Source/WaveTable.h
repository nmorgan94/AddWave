/*
 ==============================================================================
 
 WaveTable.h
 Created: 14 Feb 2017 12:57:02pm
 Author:  Nicholas Morgan
 CANT CHANGE COMPANY NAME WITHOUT CRASHING, WHY IS THIS?
 ==============================================================================
 */

#ifndef WAVETABLE_H_INCLUDED
#define WAVETABLE_H_INCLUDED


class Phasor
{
    
    float m_sampleRate;
    float m_phase;
    float m_phaseInc;
    float m_frequency;
    
public:
    
    /// Reads through the Wavetables
    /*!
     \param sampleRate Sample Rate
     */
    /*!
     \param Frequency Frequency of signal
     */
    
    Phasor(float SampleRate = 44100,float Frequency = 440):
    m_sampleRate(SampleRate),
    m_phase(0),
    m_frequency(Frequency)
    {
        calculate_inc();
    }
    
    
    void calculate_inc(){
        m_phaseInc = m_frequency/m_sampleRate;
    }
    
    
    void set_frequency(float Frequency)
    ///Sets the frequency
    
    {
        m_frequency = Frequency;
        calculate_inc();
    }
    
    
    void set_samplerate(float SampleRate)
    ///Sets the sample rate
    {
        m_sampleRate = SampleRate;
        calculate_inc();
    }
    
    
    
    
    float get_phase()
    ///Gets the current phase
    {
        return m_phase;
    }
    
    
    
    void reset()
    {
        m_phase = 0;
    }
    void tick()
    ///reads through wave table
    {
        m_phase +=m_phaseInc;
        
        while(m_phase > 1.0)m_phase -= 1.0;
        while(m_phase < 0) m_phase +=1.0;
        
    }
    float get_frequency(){
        return m_frequency;
    }
    
    
};

class WaveTable{
    float* m_table;
    int m_size;
    
    
    
public:
    ///This is where the wavetables are created
    /*!
     \param Size the number of samples to fill the table with
     */
    WaveTable(int size = 512)
    
    {
        m_size = size;
        m_table = new float[m_size];
        fill_complexSin();
    }
    
    ~WaveTable()
    {
        delete [] m_table;
    }
    
    void clear()
    ///Clears table before loading one
    {
        if(m_table == nullptr)
        {
            return;
        }
        
        for(int n = 0 ; n < m_size;++n)
        {
            m_table[n] = 0.0f;
        }
        
        
    }
    
    void fill_saw()
    ///Creates a saw wave
    {
        if(m_table == nullptr)
        {
            return;
        }
        
        for(int n=0; n < m_size; ++n)
        {
            m_table[n] = ((float(n)/m_size) * 2.0) - 1.0;
        }
    }
    
    void fill_triangle()
    ///Creates a triangle wave
    {
        if (m_table == nullptr)
        {
            return;
        }
        
        for (int n=0; n < m_size; ++n)
        {
            m_table[n] = 2.0*fabs(2.0*(float(n)/m_size) - 1.0) -1.0;
        }
    }
    
    void fill_complexSin()
    ///Creates a complex sine wave
    {
        if(m_table == nullptr)
        {
            return;
        }
        
        for (int n=0; n < m_size; ++n)
        {
            m_table[n] = sin((6.28318530781 * float(n)) / float(m_size) ) *0.5;
            m_table[n] += sin((6.28318530781 * float(n * 2)) / float(m_size) ) *03;
            m_table[n] += sin((6.28318530781 * float(n * 6)) / float(m_size) ) *0.3;
        }
    }
    
    void fill_sin()
    ///Creates a sin wave
    {
        if(m_table == nullptr)
        {
            return;
        }
        
        for (int n=0; n < m_size; ++n)
        {
            m_table[n] = sin((6.28318530781 * float(n)) / float(m_size) );
        }
    }
    
    void fill_square()
    ///Creates a square wave
    {
        float val = 0;
        
        for(int n = 0; n < m_size; ++n)
        {
            if (n < m_size/2)
            {
                val = -1.0f;
            }
            else
            {
                val = 1.0f;
            }
            m_table[n] = (val * 2.0) -1.0;
        }
    }
    
    int get_table_size()
    {
        return m_size;
    }

    float linear_lookup(int pos)
    ///used to run the from the sample of the waveshape at the end of the buffer.
    /*!
     \param pos Position in the table
     */
    {
        while(pos > m_size)pos -= m_size;
        while(pos < 0) pos += m_size;
        
        return m_table[pos];
    }  
    
};

#endif  // WAVETABLE_H_INCLUDED
