/*
 ==============================================================================
 
 MultiSlider.cpp
 Created: 6 Mar 2017 8:42:45pm
 Author:  Nicholas Morgan
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"
#include "MultiSlider.h"

//==============================================================================
MultiSlider::MultiSlider(int steps):
m_sliderTotal(steps),
m_backGroundColour(Colours::white),
m_foreGroundColour(Colours::red)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    m_values = new float[steps];
    
    Random r;
    for(int n=0 ; n<steps; ++n)
    {
        m_values[n] = 0;
    }
}

MultiSlider::~MultiSlider()
{
    delete [] m_values;
}


void MultiSlider::set_background_colour(juce::Colour col)
///Sets background Colour of multislider tab
{
    
    m_backGroundColour = col;
 
}

void MultiSlider::set_foreground_colour(juce::Colour col)
///Sets colour of multislider sliders
{
    m_foreGroundColour = col;
}


void MultiSlider::paint (Graphics& g)
///Draws multislider content
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    ////std::coutt << " ." <<std::endl;
    g.fillAll (m_backGroundColour);   // clear the background
    
    int stepWidth = getLocalBounds().getWidth()/m_sliderTotal;
    int height = getLocalBounds().getHeight();
    
    
    for(int n=0 ; n < m_sliderTotal; ++n)
    {
        g.saveState();
        AffineTransform trans(AffineTransform::verticalFlip(height));
        g.addTransform(trans);
        
        
        g.setColour(m_foreGroundColour);
        int val = m_values[n] * height;

        
        g.fillRect((int)n*stepWidth ,0 , (int)stepWidth - 2, val);
        
      
        AffineTransform rotation;
        rotation.rotated(3.14159* 1.5);
        g.addTransform(rotation);
        
        String text(*m_attachedParams->at(n));
        g.setColour(Colours::lightgrey);
        g.setColour(m_backGroundColour);
        
       g.restoreState();

        g.drawText(text,(int)n*stepWidth ,height -  val, (int)stepWidth - 2, 30,Justification::centred);
  
    }
 
}

void MultiSlider::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
}


void MultiSlider::mouseDown(const juce::MouseEvent &event)
///Called when a mouse button is pressed
{
    
    Rectangle<int > area = getLocalBounds();
    
    
    int sliderIndex= jlimit(0.0f, (float)m_sliderTotal,float(event.getPosition().getX()/(float)area.getWidth())*m_sliderTotal );
    
    float value =jlimit(0.0f, 1.0f,1.0f- (float
                                          )event.getPosition().getY()/(float)area.getHeight());
    m_values[sliderIndex] = value;
    
    set_parameter_value(sliderIndex, value);
    
    
    repaint();
    

}

void MultiSlider::mouseDrag(const juce::MouseEvent &event)
///Called when the mouse is moved while a button is held down
{
    Rectangle<int > area = getLocalBounds();
    //	//std::coutt << event.getPosition().getX()  << "  "<< event.getPosition().getX()/(float)area.getWidth()   <<std::endl;
    
    int sliderIndex= jlimit(0.0f, (float)m_sliderTotal,float(event.getPosition().getX()/(float)area.getWidth())*m_sliderTotal );
    
    float value =jlimit(0.0f, 1.0f,1.0f- (float
                                          )event.getPosition().getY()/(float)area.getHeight());
    m_values[sliderIndex] = value;
    
    set_parameter_value(sliderIndex, value);
    repaint();
   
}
void MultiSlider::mouseUp(const juce::MouseEvent &event)
///Called when a mouse button is released
{
    Rectangle<int > area = getLocalBounds();
    //	//std::coutt << event.getPosition().getX()  << "  "<< event.getPosition().getX()/(float)area.getWidth()   <<std::endl;
    
    int sliderIndex= jlimit(0.0f, (float)m_sliderTotal,float(event.getPosition().getX()/(float)area.getWidth())*m_sliderTotal );
    
    float value =jlimit(0.0f, 1.0f,1.0f- (float
                                          )event.getPosition().getY()/(float)area.getHeight());
    m_values[sliderIndex] = value;
    
    set_parameter_value(sliderIndex, value);
    
    repaint();
}


void MultiSlider::set_parameter_value(int paramIndex, float value)
///Sets multislider to output usable parameters
{
    
    
    if(m_attachedParams == nullptr) return;
    if(m_attachedParams->empty() == true) return;
    if(paramIndex < 0)return;
    if(paramIndex >= m_attachedParams->size())return;

    NormalisableRange<float> range = m_attachedParams->operator[](paramIndex)->range;
    
    value = range.convertFrom0to1(value);
    //  //std::cout << value << " value" <<std::endl;
    *m_attachedParams->operator[](paramIndex) = value;
    
}

float MultiSlider::getCurrentSliderValue(int index)
///Gets the value of the parameter beig manipulated
/*!
 \param index Outputs which tab of the multislider is being affected
 */
{
    
    return m_values[index];
}


void MultiSlider::set_parameter_vector(SynthAudioProcessor::ParameterVector *params)
///Creates vectors to hold multislider parameters
{
    
    if(params ){
        
        if(params->empty() == true)
        {
            //std::cout << "Invalid parameters passed to multi slider"<<std::endl;
            return;
        }
        m_attachedParams = params;
        //std::cout << "Multi slider params set"<<std::endl;
        
        for(int n=0 ; n<m_sliderTotal; ++n)
        {
            float val = (*params->at(n));
            NormalisableRange<float> range = (*params->at(n)).range;
            m_values[n] = range.convertTo0to1(val);
        }
        repaint();
    }
    
}


void MultiSlider::refresh()
///Used to update the UI to changes in the parameters
{
    
    for(int n=0 ; n<m_sliderTotal; ++n)
    {
        float val = (*m_attachedParams->at(n));
        NormalisableRange<float> range = (*m_attachedParams->at(n)).range;
        m_values[n] = range.convertTo0to1(val);
        repaint();
    }
    repaint();
}

