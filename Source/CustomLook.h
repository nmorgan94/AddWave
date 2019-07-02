



/*
 ==============================================================================
 
 CustomLook.h
 Created: 28 Jun 2017 11:33:12pm
 Author:  Nicholas Morgan
 
 ==============================================================================
 */

#ifndef CUSTOMLOOK_H_INCLUDED
#define CUSTOMLOOK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "MultiSlider.h"
#include "PluginProcessor.h"
#include "Poly.h"
//#include "PluginEditor.h"


class CustomLook : public LookAndFeel_V3
/// Creates custom UI elements

{
    
public:
    void 	drawLinearSlider (Graphics & g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider & slider)
    
    {
        
        g.setColour(Colours::lightgrey);
        int thirdH = height * 0.33;
        g.fillRoundedRectangle(x,thirdH,width   ,thirdH,2);
        g.setColour(Colour(125,125,125));
        g.fillRoundedRectangle(x + 2,thirdH +2 ,width - 4   ,thirdH -4,2);
        g.setColour(Colours::white);
        g.fillRect((int)sliderPos, thirdH +2 , 2, thirdH -4);
        
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    ///Draws custom Dials
    {
        const float radius = jmin (width / 2, height / 2) - 4.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::grey);
        g.fillEllipse (rx, ry, rw, rw);
        
        // outline
        // g.setColour (Colours::white);
        //g.drawEllipse (rx, ry, rw, rw, 1.0f);
        
        Path p;
        const float pointerLength = radius * 0.7f;
        const float pointerThickness = 3.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::white);
        g.fillPath (p);
    }
    
};

class CustomLook_V2 : public LookAndFeel_V3
///Creates custom sliders

{
    
    void 	drawLinearSlider (Graphics & g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider & slider){
        
        g.setColour(Colours::white);
        int thirdH = height * 0.33;
        g.fillRoundedRectangle(x,thirdH,width   ,thirdH,2);
        g.setColour(Colour(125,125,125));
        g.fillRoundedRectangle(x + 2,thirdH +2 ,width - 4   ,thirdH -4,2);
        g.setColour(Colours::black);
        g.fillRect((int)sliderPos, thirdH +2 , 2, thirdH -4);
        
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    ///Draws custom dials
    {
        const float radius = jmin (width / 2, height / 2) - 4.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::white);
        g.fillEllipse (rx, ry, rw, rw);
        
        // outline
        g.setColour (Colours::grey);
        g.drawEllipse (rx, ry, rw, rw, 3.0f);
        
        Path p;
        const float pointerLength = radius * 0.7f;
        const float pointerThickness = 3.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::grey);
        g.fillPath (p);
    }
    
    
};


class CustomTabButton  : public Component

///Creates custom tab buttons for the tabbed components


{
public:
    CustomTabButton(bool& state):
    m_state(state)
    /*!
     \param state Outputs which tab of the multislider is being affected
     */
    {
        setSize (20, 20);
    }
    

    
    void paint (Graphics& g) override
    {
        
        Path circle;
        circle.addEllipse(0, 0, 3, 3);
        
        if(m_state == false){
            g.setColour (Colours::red);
        }else{
            g.setColour (Colours::lightblue);
        }
        g.fillPath (circle, circle.getTransformToScaleToFit (getLocalBounds().reduced (2).toFloat(), true));
        
    }
    
    void mouseDown (const MouseEvent&) override
    {
        
        m_state = !m_state;
        
        //std::coutt << "Clicked" << std::endl;
        
        repaint();
    }
    
    private:
     
        bool& m_state;
        };
        

        class CustomTabButton_V2  : public Component
        {
            MultiSlider* m_slider;
            //PolyVoice* m_pitchBypass;
            static PolyVoice* m_pitchBypass;
            
        public:
            CustomTabButton_V2(MultiSlider* slider):
            m_slider(slider)
            //m_pitchBypass(true)
            {
                setSize (20, 20);
                
            }

            void paint (Graphics& g) override
            {

                Path triangle;
                triangle.addTriangle(30, 7, 50, 7, 40, 20);
                
                g.setColour (Colours::grey);
                g.fillPath (triangle, triangle.getTransformToScaleToFit (getLocalBounds().reduced (2).toFloat(), true));
                
            }
            
            void mouseDown (const MouseEvent& e)
            {
                PopupMenu m_popupMenu;
                m_popupMenu.addItem (1, "Reset Amount");
                m_popupMenu.addItem (2, "Pitch Amount");
                m_popupMenu.addItem (3, "Pitch Attack");
                m_popupMenu.addItem (4, "Pitch Decay");
                m_popupMenu.addItem (5, "Pitch Sustain");
                m_popupMenu.addItem (6, "Pitch Release");
                
                
                const int result = m_popupMenu.show();
                if (result == 0)
                {
                    // user dismissed the menu without picking anything
                }
                else if (result == 1)
                {
                    // user picked item 1
                    
                    for (int n=0; n<16; ++n)
                    {
                        m_slider->set_parameter_vector(&SynthAudioProcessor::s_pitchAmount);
                        m_slider->refresh();
                        m_slider->set_parameter_value(n, 0.5);
                        //m_slider->repaint();
                        m_slider->refresh();
                    }
                 
                    
                }
                else if (result == 2)
                {
                    // user picked item 2
                    m_slider->set_parameter_vector(&SynthAudioProcessor::s_pitchAmount);
                }
                else if (result == 3)
                {
                    // user picked item 3
                    m_slider->set_parameter_vector(&SynthAudioProcessor::s_pitchAttackValues);
                }
                else if (result == 4)
                {
                    // user picked item 4
                    m_slider->set_parameter_vector(&SynthAudioProcessor::s_pitchDecayValues);
                }
                else if (result == 5)
                {
                    // user picked item 5
                    m_slider->set_parameter_vector(&SynthAudioProcessor::s_pitchSustainValues);
                }
                else if (result == 6)
                {
                    // user picked item 6
                    m_slider->set_parameter_vector(&SynthAudioProcessor::s_pitchReleaseValues);
                }
                else if (result == 7)
                {
                    // user picked item 7
                }
                else if (result == 8)
                {
                    // user picked item 8
                }
     
            }
            
        private:

        };
        
        
        class Customtab : public LookAndFeel_V3
        {
            

            void drawTabButton	(	TabBarButton & button	,Graphics & g,bool isMouseOver,bool isMouseDown){
                
                const Rectangle<int> activeArea (button.getActiveArea());
                Rectangle<float> backarea(activeArea.getX(),activeArea.getY(),activeArea.getWidth(),activeArea.getHeight());
                
                
                const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();
                
                const Colour bkg (button.getTabBackgroundColour());
                
                if (button.getToggleState())
                {
                    g.setColour (bkg);
                }
                else
                {
                    Point<int> p1, p2;
                    
                    switch (o)
                    {
                        case TabbedButtonBar::TabsAtBottom:   p1 = activeArea.getBottomLeft(); p2 = activeArea.getTopLeft();    break;
                        case TabbedButtonBar::TabsAtTop:      p1 = activeArea.getTopLeft();    p2 = activeArea.getBottomLeft(); break;
                        case TabbedButtonBar::TabsAtRight:    p1 = activeArea.getTopRight();   p2 = activeArea.getTopLeft();    break;
                        case TabbedButtonBar::TabsAtLeft:     p1 = activeArea.getTopLeft();    p2 = activeArea.getTopRight();   break;
                        default:                              jassertfalse; break;
                    }
                    
                    g.setGradientFill (ColourGradient (bkg.brighter (0.8f), (float) p1.x, (float) p1.y,
                                                       bkg.darker (0.4f),   (float) p2.x, (float) p2.y, false));
                }
                g.fillRoundedRectangle(backarea,10.0f);
                //g.fillRect (activeArea);
                
                g.setColour (button.findColour (TabbedButtonBar::tabOutlineColourId));
                
                Rectangle<int> r (activeArea);
                
                if (o != TabbedButtonBar::TabsAtBottom)   g.fillRect (r.removeFromTop (1));
                if (o != TabbedButtonBar::TabsAtTop)      g.fillRect (r.removeFromBottom (1));
                if (o != TabbedButtonBar::TabsAtRight)    g.fillRect (r.removeFromLeft (1));
                if (o != TabbedButtonBar::TabsAtLeft)     g.fillRect (r.removeFromRight (1));
                
                const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
                
                Colour col (bkg.contrasting().withMultipliedAlpha (alpha));
                
                if (TabbedButtonBar* bar = button.findParentComponentOfClass<TabbedButtonBar>())
                {
                    TabbedButtonBar::ColourIds colID = button.isFrontTab() ? TabbedButtonBar::frontTextColourId
                    : TabbedButtonBar::tabTextColourId;
                    
                    if (bar->isColourSpecified (colID))
                        col = bar->findColour (colID);
                    else if (isColourSpecified (colID))
                        col = findColour (colID);
                }
                
                const Rectangle<float> area (button.getTextArea().toFloat());
                
                float length = area.getWidth();
                float depth  = area.getHeight();
                
                if (button.getTabbedButtonBar().isVertical())
                    std::swap (length, depth);
                
                TextLayout textLayout;
                createTabTextLayout (button, length, depth, col, textLayout);
                
                AffineTransform t;
                
                switch (o)
                {
                    case TabbedButtonBar::TabsAtLeft:   t = t.rotated (float_Pi * -0.5f).translated (area.getX(), area.getBottom()); break;
                    case TabbedButtonBar::TabsAtRight:  t = t.rotated (float_Pi *  0.5f).translated (area.getRight(), area.getY()); break;
                    case TabbedButtonBar::TabsAtTop:
                    case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
                    default:                            jassertfalse; break;
                }
                
                g.addTransform (t);
                textLayout.draw (g, Rectangle<float> (length, depth));
            }
            
        };

        
#endif  // CUSTOMLOOK_H_INCLUDED
