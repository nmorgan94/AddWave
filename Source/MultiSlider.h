/*
  ==============================================================================

    MultiSlider.h
    Created: 6 Mar 2017 8:42:45pm
    Author:  Nicholas Morgan

  ==============================================================================
*/

#ifndef MULTISLIDER_H_INCLUDED
#define MULTISLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


#include "PluginProcessor.h"

//==============================================================================
/*
*/
class MultiSlider    : public Component
{
    
    int m_sliderTotal; /*!< Number of sliders */
    float* m_values;
    
    Colour m_backGroundColour,m_foreGroundColour;
    SynthAudioProcessor::ParameterVector* m_attachedParams;
    
public:
    ///This is the core class for user interaction
    
    /*!
     \param steps the number of sliders required
     */
    MultiSlider(int steps);
    ~MultiSlider();

    void paint (Graphics&) override;
    void resized() override;

    virtual void mouseDown (const MouseEvent &event) override;
    virtual void mouseDrag (const MouseEvent &event) override;
    virtual void mouseUp (const MouseEvent &event) override;
    
    void set_parameter_value(int paramIndex, float value);
    
    void set_background_colour(Colour col);
    void set_foreground_colour(Colour col);
    
    float getCurrentSliderValue(int index);
    
    void set_parameter_vector(SynthAudioProcessor::ParameterVector* params);

    void refresh();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiSlider)
};


#endif  // MULTISLIDER_H_INCLUDED
