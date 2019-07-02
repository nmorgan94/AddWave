/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MultiSlider.h"
#include "ReverbControlView.h"
#include "FilterControlView.h"
#include "DelayControlView.h"
#include "DistortionControlView.h"
#include "EffectController.h"
//#include <string>

//#include "Poly.h"

MultiSlider*m_backGroundColour;

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p):
AudioProcessorEditor (&p),
processor (p),
midiKeyboard (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
m_attachedProcessor(p),
mainVol("Gain")

{
    
    nickFeel.setColour(Slider::rotarySliderFillColourId, Colours::midnightblue);
    nickFeel.setColour(Slider::thumbColourId, Colours::lightgrey);
    nickFeel.setColour(Slider::trackColourId, Colours::lightgrey);\
    nickFeel.setColour(Slider::rotarySliderOutlineColourId, Colours::white);
    nickFeel.setColour(ComboBox::backgroundColourId, Colours::lightgrey);
    nickFeel.setColour(PopupMenu::backgroundColourId, Colours::lightgrey);
    nickFeel.setColour(PopupMenu::highlightedBackgroundColourId, Colours::grey);
    
    setLookAndFeel(&nickFeel);
    
    mainVol.setSliderStyle(Slider::RotaryVerticalDrag);
    mainVol.setRange(0.0, 1.0 ,0.001);
    mainVol.setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    mainVol.setPopupDisplayEnabled(true, this);
    mainVol.setTextValueSuffix(" Volume");
    mainVol.addListener(this);
    mainVol.setLookAndFeel(&m_customLook2);
    mainVol.setValue(1);
    
    AttackCurve.setSliderStyle(Slider::RotaryVerticalDrag);
    AttackCurve.setRange(0.0001, 100.0, 0.0001);
    AttackCurve.setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    AttackCurve.setPopupDisplayEnabled(false, this);
    AttackCurve.setTextValueSuffix("");
    AttackCurve.addListener(this);
    AttackCurve.setLookAndFeel(&m_customLook2);
    
    DecayReleaseCurve.setSliderStyle(Slider::RotaryVerticalDrag);
    DecayReleaseCurve.setRange(0.0001, 100.0, 0.0001);
    DecayReleaseCurve.setTextBoxStyle(Slider::NoTextBox, false, 50, 50);
    DecayReleaseCurve.setPopupDisplayEnabled(false, this);
    DecayReleaseCurve.setTextValueSuffix("");
    DecayReleaseCurve.addListener(this);
    DecayReleaseCurve.setLookAndFeel(&m_customLook2);
    
    powerButton.getToggleState();
    powerButton.setToggleState(true, sendNotification);
    powerButton.setClickingTogglesState(true);
    powerButton.setButtonText("Power");
    powerButton.addListener(this);
    powerButton.setColour(TextButton::buttonColourId, Colours::grey);
    powerButton.setColour(TextButton::buttonOnColourId, Colours::red);
    
    presetSave.getToggleState();
    presetSave.setToggleState(false, sendNotification);
    presetSave.setClickingTogglesState(true);
    presetSave.setButtonText("Save");
    presetSave.addListener(this);
    presetSave.setColour(TextButton::buttonColourId, Colours::lightgrey);
    presetSave.setColour(TextButton::buttonOnColourId, Colours::lightgrey);
    
    
    presetLoad.getToggleState();
    presetLoad.setToggleState(false, sendNotification);
    presetLoad.setClickingTogglesState(true);
    presetLoad.setButtonText("Load");
    presetLoad.addListener(this);
    presetLoad.setColour(TextButton::buttonColourId, Colours::lightgrey);
    presetLoad.setColour(TextButton::buttonOnColourId, Colours::lightgrey);
    
    comboBox.addItem("Saw", 1);
    comboBox.addItem("Square", 2);
    comboBox.addItem("Complex Sin", 3);
    comboBox.addItem("Sin", 4);
    comboBox.addItem("Triangle", 5);
    comboBox.setSelectedId(1);
    comboBox.setLookAndFeel(&nickFeel);
    comboBox.addListener(this);
    
    presetSelect.addItem("Dancing Keys", 1);
    presetSelect.addItem("Delayed Duck", 2);
    presetSelect.addItem("Dubstep MidBass", 3);
    presetSelect.addItem("Glass Keys", 4);
    presetSelect.addItem("Reset", 5);
    presetSelect.addItem("Roller Coaster", 6);
    presetSelect.addItem("Scary Hall", 7);
    presetSelect.addItem("Spacey Desert", 8);
    presetSelect.setText("Select Preset");
    //presetSelect.setSelectedId(9);
    presetSelect.addListener(this);
    
    m_harmonicNumber.addItem("32", 1);
    m_harmonicNumber.addItem("16", 2);
    m_harmonicNumber.addItem("8", 3);
    m_harmonicNumber.addItem("4", 4);
    m_harmonicNumber.setSelectedId(2);
    m_harmonicNumber.setLookAndFeel(&nickFeel);
    m_harmonicNumber.addListener(this);
    
    m_voiceNumber.addItem("10", 10);
    m_voiceNumber.addItem("9", 9);
    m_voiceNumber.addItem("8", 8);
    m_voiceNumber.addItem("7", 7);
    m_voiceNumber.addItem("6", 6);
    m_voiceNumber.addItem("5", 5);
    m_voiceNumber.addItem("4", 4);
    m_voiceNumber.addItem("3", 3);
    m_voiceNumber.addItem("2", 2);
    m_voiceNumber.addItem("1", 1);
    m_voiceNumber.setSelectedId(3);
    m_voiceNumber.setLookAndFeel(&nickFeel);
    m_voiceNumber.addListener(this);
    
    addAndMakeVisible(&mainVol);
    addAndMakeVisible(&mainVolLabel);
    addAndMakeVisible(powerButton);
    addAndMakeVisible(midiKeyboard);
    addAndMakeVisible(comboBox);
    //addAndMakeVisible(m_harmonicNumber);
    addAndMakeVisible(m_voiceNumber);
    addAndMakeVisible(presetSelect);
    addAndMakeVisible(presetLoad);
    addAndMakeVisible(presetSave);
    
    //MultiSlider Tabs
    tab = new TabbedComponent (TabbedButtonBar::TabsAtTop);
    addAndMakeVisible(tab);
    tab->setOutline(5);
    
    tab->setTabBarDepth(30);
    
    m_numHarmonics = 16;
    
    tab->addTab(TRANS("Amplitudes"), Colours::red, m_ampMultiSlider = new MultiSlider(m_numHarmonics), true);
    m_ampMultiSlider->set_foreground_colour(Colours::red);
    m_ampMultiSlider->set_background_colour(Colours::white);
    
    tab->addTab(TRANS("Attack"), Colours::blue, m_attackMultiSlider = new MultiSlider (m_numHarmonics), true);
    m_attackMultiSlider->set_foreground_colour(Colours::blue);
    m_attackMultiSlider->set_background_colour(Colours::white);
    
    tab->addTab(TRANS("Decay"), Colours::orange, m_decayMultiSlider = new MultiSlider (m_numHarmonics), true);
    m_decayMultiSlider->set_foreground_colour(Colours::orange);
    m_decayMultiSlider->set_background_colour(Colours::white);
    
    tab->addTab(TRANS("Sustain"), Colours::green, m_sustainMultiSlider = new MultiSlider (m_numHarmonics), true);
    m_sustainMultiSlider->set_foreground_colour(Colours::green);
    m_sustainMultiSlider->set_background_colour(Colours::white);
    
    tab->addTab(TRANS("Release"), Colours::indigo, m_releaseMultiSlider = new MultiSlider (m_numHarmonics), true);
    m_releaseMultiSlider->set_foreground_colour(Colours::indigo);
    m_releaseMultiSlider->set_background_colour(Colours::white);
    
    tab->addTab(TRANS("Pitch Envelope"), Colours::cyan, m_pitchEnvelopeMultiSlider = new MultiSlider (m_numHarmonics), false);
    m_pitchEnvelopeMultiSlider->set_foreground_colour(Colours::cyan);
    m_pitchEnvelopeMultiSlider->set_background_colour(Colours::white);
    
    
    tab->getTabbedButtonBar().getTabButton (5)->setExtraComponent (new CustomTabButton_V2(m_pitchEnvelopeMultiSlider ), TabBarButton::afterText);
    
    
    //    Master Effect Tabs
    m_effectTabView = new TabbedComponent(TabbedButtonBar::TabsAtBottom);
    m_filterView = new FilterControlView();
    m_reverbView  = new ReverbControlView();
    m_delayView = new DelayControlView();
    m_distortionView = new DistortionControlView();
    
    m_effectTabView->setOutline(5);
    m_effectTabView->addTab("Filter", Colours::grey,m_filterView , true);
    m_effectTabView->addTab("Reverb", Colours::white, m_reverbView , true);
    m_effectTabView->addTab("Delay", Colours::grey, m_delayView, true);
    m_effectTabView->addTab("Distortion", Colours::white, m_distortionView, true);
    m_effectTabView->setCurrentTabIndex(0);
    addAndMakeVisible(m_effectTabView);
    
    m_effectTabView->getTabbedButtonBar().getTabButton (0)->setExtraComponent (new CustomTabButton(m_attachedProcessor.m_filterBypass), TabBarButton::afterText);
    m_effectTabView->getTabbedButtonBar().getTabButton (1)->setExtraComponent (new CustomTabButton(m_attachedProcessor.m_reverbBypass), TabBarButton::afterText);
    m_effectTabView->getTabbedButtonBar().getTabButton (2)->setExtraComponent (new CustomTabButton(m_attachedProcessor.m_delayBypass), TabBarButton::afterText);
    m_effectTabView->getTabbedButtonBar().getTabButton (3)->setExtraComponent (new CustomTabButton(m_attachedProcessor.m_distortionBypass), TabBarButton::afterText);
    
    
    
    //Master Envelope Tabs
    m_envTabView = new TabbedComponent(TabbedButtonBar::TabsAtBottom);
    
    m_envHPFilterView = new EnvelopeHPFilterView();
    m_envLPFilterView = new EnvelopeLPFilterView();
    
    
    m_envTabView->setOutline(5);
    m_envTabView->addTab("HP Env", Colours::grey, m_envHPFilterView, true);
    m_envTabView->addTab("LP Env", Colours::white, m_envLPFilterView, true);
    //m_envTabView->addTab("Pitch", Colours::grey, m_envPitchView, true);
    
    m_envTabView->setCurrentTabIndex(0);
    addAndMakeVisible(m_envTabView);
    
    m_envTabView->getTabbedButtonBar().getTabButton (0)->setExtraComponent(new CustomTabButton(m_attachedProcessor.m_hpBypass), TabBarButton::afterText);
    m_envTabView->getTabbedButtonBar().getTabButton (1)->setExtraComponent(new CustomTabButton(m_attachedProcessor.m_lpBypass), TabBarButton::afterText);
    
    
    m_effectController = new EffectsController(m_attachedProcessor,*m_filterView, *m_reverbView, *m_delayView, *m_distortionView);
    m_envelopeController = new EnvelopeController(m_attachedProcessor, *m_envHPFilterView, *m_envLPFilterView);
    
    
    m_ampMultiSlider->set_parameter_vector(&SynthAudioProcessor::s_amplitudes);
    
    m_attackMultiSlider->set_parameter_vector(&SynthAudioProcessor::s_attackValues);
    
    m_decayMultiSlider->set_parameter_vector(&SynthAudioProcessor::s_decayValues);
    
    m_sustainMultiSlider->set_parameter_vector(&SynthAudioProcessor::s_sustainValues);
    
    m_releaseMultiSlider->set_parameter_vector(&SynthAudioProcessor::s_releaseValues);
    
    m_pitchEnvelopeMultiSlider->set_parameter_vector(&SynthAudioProcessor::s_pitchAmount);

    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 620);
    
    updateUI();
    
    startTimer(100);

}




SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
    
}

//==============================================================================
void SynthAudioProcessorEditor::paint (Graphics& g)
///Used to add on-screen text
{
    // g.fillAll (Colours::white);
    
    /*
     g.setGradientFill (ColourGradient (Colour (0X0),
     getWidth() * 0.5f,
     getHeight() * 0.5f,
     Colour (0x69000000),
     0.0f, 0.0f, true));
     
     */
    g.setColour(Colours::white);
    g.fillAll();
    
    g.setFont(12.0f);
    g.setColour(Colours::grey);
    g.drawFittedText("Volume", 635, 95, 50, 50, Justification::centred, 1);
    
    
    g.setColour (Colours::grey);
    g.setFont (30.0f);
    g.drawFittedText("Nick Morgan", 50, -35, getWidth(), getHeight(), Justification::bottomLeft, 1);
    
    g.setFont(12.0f);
    g.drawFittedText("Wave Shape", 50, 86, 100, 20, Justification::left, 1);
    //g.drawFittedText("Harmonics", 290, 86, 100, 20, Justification::left, 1);
    g.drawFittedText("Voices", 170, 86, 100, 20, Justification::left, 1);
    
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 15, 10);
    g.drawRoundedRectangle(20, 13, getWidth()-40, 50, 15, 5);
    
    g.setFont(50.0f);
    g.saveState();
    g.reduceClipRegion(getLocalBounds().withWidth(getWidth()/2));
    g.drawFittedText("AddWave", 0, 10, getWidth(), getHeight(), Justification::centredTop, 1);
    
    g.restoreState();
    
    g.setColour (Colours::grey);
    g.reduceClipRegion(getLocalBounds().removeFromRight(getWidth()/2));
    g.drawFittedText("AddWave", 0, 10, getWidth(), getHeight(), Justification::centredTop, 1);
    
 
}

void SynthAudioProcessorEditor::resized()
///Sets the size of all GUI components
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    
    auto window = getLocalBounds();
    
    
    auto topSection = window.removeFromTop(50);

    
    powerButton.setBounds(695, 70, 70, 30);
    
    mainVol.setBounds(635, 65, 50, 50);
    
    AttackCurve.setBounds(50, 470, 50, 50);
    
    DecayReleaseCurve.setBounds(135, 470, 50, 50);
    
    m_effectTabView->setBounds(410, 430, 355, 100);
    
    midiKeyboard.setBounds(270, 540, 500, 60);
    
    comboBox.setBounds(50, 70, 100, 20);
    
    m_harmonicNumber.setBounds(290, 70, 100, 20);
    
    m_voiceNumber.setBounds(170, 70, 100, 20);
    
    tab->setBounds(50, 112, 715, 310);
    
    presetSelect.setBounds(475, 70, 150, 20);
    
    presetLoad.setBounds(475, 92, 70, 18);
    
    presetSave.setBounds(555, 92, 70, 18);
    
    m_envTabView->setBounds(50, 430, 355, 100);
 
}




void SynthAudioProcessorEditor::sliderValueChanged (Slider* slider)
///Outputs changes to slider and impliments to the audio
{
    if (slider == &mainVol)
    {
        // mainVol.getValue();
        //std::coutt << "Volume " << mainVol.getValue() << std::endl;
        m_attachedProcessor.set_main_gain(mainVol.getValue());
      
    }
    
    else if (slider == &AttackCurve)
    {
        ////std::coutt << "Attack Curve " << AttackCurve.getValue() << std::endl;
        
        // *m_attachedProcessor.m_attackCurve = AttackCurve.getValue();
        
    }
    
    else if (slider == &DecayReleaseCurve)
    {
        ////std::coutt << "Decay Release Curve " << DecayReleaseCurve.getValue() << std::endl;
        // *m_attachedProcessor.m_decayReleaseCurve = DecayReleaseCurve.getValue();
    }
}

void SynthAudioProcessorEditor::updateUI()
///Updates the UI to match the audio thread
{
    //const int presetVal = presetSelect.getSelectedId();
    
    const float newValue = m_attachedProcessor.get_main_gain();
    
    
    if (newValue != (float) mainVol.getValue() && ! isMouseButtonDown())
        mainVol.setValue (newValue);
    
    const int voiceComboBoxVal =  m_attachedProcessor.get_num_voices();
    
    if (voiceComboBoxVal != (int) m_voiceNumber.getSelectedId())
        m_voiceNumber.setSelectedId(voiceComboBoxVal);
    
    const int waveComboBoxVal = m_attachedProcessor.get_waveshapeNumber();
    
    if (waveComboBoxVal != (int) comboBox.getSelectedId())
        comboBox.setSelectedId(waveComboBoxVal);
    
    const int powerButtonVal = m_attachedProcessor.get_powerButton_val();
    
    if(powerButtonVal != powerButton.getToggleState())
        powerButton.setToggleState(powerButtonVal, sendNotification);
    
    m_ampMultiSlider->refresh();
    m_attackMultiSlider->refresh();
    m_decayMultiSlider->refresh();
    m_sustainMultiSlider->refresh();
    m_releaseMultiSlider->refresh();
    m_pitchEnvelopeMultiSlider->refresh();
    
   // m_attachedProcessor.get_ampMultislider_val();

   
}

void SynthAudioProcessorEditor::comboBoxChanged (ComboBox* box)
///Called when a combo box changes state
{
    ////std::cout << comboBox.getSelectedId() << std::endl;
    if(box == &comboBox)
    {
        
        String text =  box->getText();
        //std::cout << text <<std::endl;
        
        
        if(text == "Saw"){
            m_attachedProcessor.set_saw();
            
        }else if(text == "Square"){
            m_attachedProcessor.set_square();
            
        }else if(text == "Complex Sin"){
            m_attachedProcessor.set_complex_sin();
            
        }else if (text == "Sin"){
            m_attachedProcessor.set_sin();
        }
        else if (text == "Triangle"){
            m_attachedProcessor.set_triangle();
        }
        
        
    }
    
    
    if (box == &presetSelect)
    {
        
        String presetText = box->getText();
        //std::coutt << presetText << std::endl;
        
        String xmlString;
        bool valid = false;
        if (presetText == "Dancing Keys")
        {
            xmlString = String(BinaryData::DancingKeys_xml,BinaryData::DancingKeys_xmlSize);
            //  loadParameters(BinaryData::preset2_xml)
            valid = true;
            
        }
        else if (presetText == "Delayed Duck")
        {
            xmlString = String(BinaryData::DelayedDuck_xml,BinaryData::DelayedDuck_xmlSize);
            //  loadParameters(BinaryData::preset2_xml)
            valid = true;
        }
        else if (presetText == "Dubstep MidBass")
        {
            xmlString = String(BinaryData::DubstepMidBass_xml,BinaryData::DubstepMidBass_xmlSize);
            //  loadParameters(BinaryData::preset2_xml)
            valid = true;
        }
        else if (presetText == "Glass Keys")
        {
            xmlString = String(BinaryData::GlassKeys_xml,BinaryData::GlassKeys_xmlSize);
            //  loadParameters(BinaryData::preset2_xml)
            valid = true;
        }
        else if (presetText == "Reset")
        {
            xmlString = String(BinaryData::Reset_xml,BinaryData::Reset_xmlSize);
            //  loadParameters(BinaryData::preset2_xml)
            valid = true;
        }
        else if (presetText == "Roller Coaster")
        {
            xmlString = String(BinaryData::RollerCoaster_xml,BinaryData::RollerCoaster_xmlSize);
            //  loadParameters(BinaryData::preset2_xml)
            valid = true;
        }
        else if (presetText == "Scary Hall")
        {
            xmlString = String(BinaryData::ScaryHall_xml,BinaryData::ScaryHall_xmlSize);
            //  loadParameters(BinaryData::preset2_xml)
            valid = true;
        }
        else if (presetText == "Spacey Desert")
        {
            xmlString = String(BinaryData::SpaceyDesert_xml,BinaryData::SpaceyDesert_xmlSize);
            //  loadParameters(BinaryData::preset2_xml)
            valid = true;
        }

        
        if(valid == true){
            XmlDocument XMLdoc(xmlString);
            try{
                ScopedPointer<XmlElement> mainElement = XMLdoc.getDocumentElement();
                
                if(mainElement == nullptr)
                {
                    String xmlErrorMessage = XMLdoc.getLastParseError();
                    throw presetText + " invalid \n" +xmlErrorMessage;
                }
                
                loadParameters(mainElement);
            } catch ( String message )
            {
                AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Loading preset failed!", message);
            }
        }
        
        
    }
    
    
    if(box == &m_harmonicNumber)
    {
        String harmonicText = box->getText();
        //std::coutt << harmonicText << std::endl;
        
        if (harmonicText == "4")
        {
            set_num_harmonics(4);
            get_num_harmonics();
            
        }
        else if (harmonicText == "8")
        {
            set_num_harmonics(8);
            get_num_harmonics();
        }
        else if (harmonicText == "16")
        {
            set_num_harmonics(16);
            get_num_harmonics();
        }
        else if (harmonicText == "32")
        {
            set_num_harmonics(32);
            get_num_harmonics();
        }

    }
    
    if (box == &m_voiceNumber)
    {
        String voiceText = box->getText();
        ////std::coutt << voiceText << std::endl;
        //std::coutt << m_voiceNumber.getSelectedId() << std::endl;
        
        if (voiceText == "1"){
            m_attachedProcessor.set_num_voices(1);
            //m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "2"){
            m_attachedProcessor.set_num_voices(2);
            //m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "3"){
            m_attachedProcessor.set_num_voices(3);
            //m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "4"){
            m_attachedProcessor.set_num_voices(4);
           // m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "5"){
            m_attachedProcessor.set_num_voices(5);
            //m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "6"){
            m_attachedProcessor.set_num_voices(6);
           // m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "7"){
            m_attachedProcessor.set_num_voices(7);
            //m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "8"){
            m_attachedProcessor.set_num_voices(8);
           // m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "9"){
            m_attachedProcessor.set_num_voices(9);
           // m_attachedProcessor.get_num_voices();
        }
        else if(voiceText == "10"){
            m_attachedProcessor.set_num_voices(10);
           // m_attachedProcessor.get_num_voices();
        }
    }
    
}


void SynthAudioProcessorEditor::set_num_harmonics(int harmonics)
///Sets the number of harmonics
{
    
    m_numHarmonics = jlimit(4, 32, harmonics);
    

    m_ampMultiSlider->refresh();
    m_attackMultiSlider->refresh();
    m_decayMultiSlider->refresh();
    m_sustainMultiSlider->refresh();
    m_releaseMultiSlider->refresh();
    
    m_ampMultiSlider->repaint();
    

}

int SynthAudioProcessorEditor::get_num_harmonics()
///Returns the number of harmonics/
{
    //std::coutt << "Number Harmonics = " << m_numHarmonics << std::endl;
}


void SynthAudioProcessorEditor::buttonClicked (Button* button)
{
    if (button == &powerButton)
    {
        
        //std::coutt << "Power Button " << powerButton.getToggleState() <<std::endl;
        m_attachedProcessor.set_mute_state(powerButton.getToggleState());
        
    }

    if (button == &presetLoad)
    {
      
        try
        {
            
            FileChooser chooser("Load XML", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
            
            if(chooser.browseForFileToOpen())
            {
                
                File selectedFile(chooser.getResult());
                
                String filename = selectedFile.getFileName();
                
                if(!selectedFile.existsAsFile())
                {
                    throw filename + " does not exist";
                }
                
                XmlDocument XMLdoc(selectedFile);
                
                ScopedPointer<XmlElement> mainElement = XMLdoc.getDocumentElement();
                
                if(mainElement == nullptr)
                {
                    String xmlErrorMessage = XMLdoc.getLastParseError();
                    throw filename + " invalid \n" +xmlErrorMessage;
                }
                
                loadParameters(mainElement);
                presetSelect.setText("Manual Load");
                
            }
            
        }
        catch ( String message )
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Load XML failed!", message);
        }
        
    }
    else if (button == &presetSave)
        //    {
        //        //std::coutt << "Preset Save Button Clicked" << std::endl;
        //    }
    {
        
        try
        {
            
            FileChooser chooser("Save XML", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
            
            
            if(chooser.browseForFileToSave(true))
                ///Saves data to XML files.
            {
                
                File selectedFile(chooser.getResult());
                
                ScopedPointer<XmlElement> mainXmlElement = new XmlElement("ParameterTweaker");
                
                XmlElement* gainParamElement = mainXmlElement->createNewChildElement("parameter");
                gainParamElement->setAttribute("id", "Gain");
                gainParamElement->setAttribute("value", (double)mainVol.getValueObject().getValue());
                
                XmlElement* lowPassParamElement = mainXmlElement->createNewChildElement("parameter");
                lowPassParamElement->setAttribute("id", "LowPass");
                lowPassParamElement->setAttribute("value", (double)m_filterView->m_lowpassSlider->getValueObject().getValue());
                
                XmlElement* highPassParamElement = mainXmlElement->createNewChildElement("parameter");
                highPassParamElement->setAttribute("id", "HighPass");
                highPassParamElement->setAttribute("value", (double)m_filterView->m_highpassSlider->getValueObject().getValue());
                
                XmlElement* ReverbWetParamElement = mainXmlElement->createNewChildElement("parameter");
                ReverbWetParamElement->setAttribute("id", "ReverbWet");
                ReverbWetParamElement->setAttribute("value", (double)m_reverbView->m_reverbWet->getValueObject().getValue());
                
                XmlElement* ReverbDryParamElement = mainXmlElement->createNewChildElement("parameter");
                ReverbDryParamElement->setAttribute("id", "ReverbDry");
                ReverbDryParamElement->setAttribute("value", (double)m_reverbView->m_reverbDry->getValueObject().getValue());
                
                XmlElement* ReverbWidthParamElement = mainXmlElement->createNewChildElement("parameter");
                ReverbWidthParamElement->setAttribute("id", "ReverbWidth");
                ReverbWidthParamElement->setAttribute("value", (double)m_reverbView->m_reverbWet->getValueObject().getValue());
                
                XmlElement* ReverbRoomsizeParamElement = mainXmlElement->createNewChildElement("parameter");
                ReverbRoomsizeParamElement->setAttribute("id", "ReverbRoomsize");
                ReverbRoomsizeParamElement->setAttribute("value", (double)m_reverbView->m_reverbRoomSize->getValueObject().getValue());
                
                XmlElement* ReverbDampingParamElement = mainXmlElement->createNewChildElement("parameter");
                ReverbDampingParamElement->setAttribute("id", "ReverbDamping");
                ReverbDampingParamElement->setAttribute("value", (double)m_reverbView->m_reverbDamping->getValueObject().getValue());
                
                XmlElement* DelayTimeLeftParamElement = mainXmlElement->createNewChildElement("parameter");
                DelayTimeLeftParamElement->setAttribute("id", "DelayTimeLeft");
                DelayTimeLeftParamElement->setAttribute("value", (double)m_delayView->m_leftDelayTime->getValueObject().getValue());
                
                XmlElement* DelayTimeRightParamElement = mainXmlElement->createNewChildElement("parameter");
                DelayTimeRightParamElement->setAttribute("id", "DelayTimeRight");
                DelayTimeRightParamElement->setAttribute("value", (double)m_delayView->m_rightDelayTime->getValueObject().getValue());
                
                XmlElement* DelayFeedbackLeftParamElement = mainXmlElement->createNewChildElement("parameter");
                DelayFeedbackLeftParamElement->setAttribute("id", "DelayFeedbackLeft");
                DelayFeedbackLeftParamElement->setAttribute("value", (double)m_delayView->m_leftFeedback->getValueObject().getValue());
                
                XmlElement* DelayTimeRightgParamElement = mainXmlElement->createNewChildElement("parameter");
                DelayTimeRightgParamElement->setAttribute("id", "DelayFeedbackLeft");
                DelayTimeRightgParamElement->setAttribute("value", (double)m_delayView->m_rightFeedback->getValueObject().getValue());
                
                XmlElement* DistortionAmountParamElement = mainXmlElement->createNewChildElement("parameter");
                DistortionAmountParamElement->setAttribute("id", "DistortionAmount");
                DistortionAmountParamElement->setAttribute("value", (double)m_distortionView->m_distortionAmountSlider->getValueObject().getValue());
                
                XmlElement* LPFilterEnvAmountParamElement = mainXmlElement->createNewChildElement("parameter");
                LPFilterEnvAmountParamElement->setAttribute("id", "LowPassFilterEnvAmount");
                LPFilterEnvAmountParamElement->setAttribute("value", (double)m_envLPFilterView->m_lpFilterAmountSlider->getValueObject().getValue());
                
                XmlElement* LPFilterEnvAttackParamElement = mainXmlElement->createNewChildElement("parameter");
                LPFilterEnvAttackParamElement->setAttribute("id", "LowPassFilterAttack");
                LPFilterEnvAttackParamElement->setAttribute("value", (double)m_envLPFilterView->m_lpFilterAttackSlider->getValueObject().getValue());
                
                XmlElement* LPFilterEnvDecayParamElement = mainXmlElement->createNewChildElement("parameter");
                LPFilterEnvDecayParamElement->setAttribute("id", "LowPassFilterDecay");
                LPFilterEnvDecayParamElement->setAttribute("value", (double)m_envLPFilterView->m_lpFilterDecaySlider->getValueObject().getValue());
                
                XmlElement* LPFilterSustainParamElement = mainXmlElement->createNewChildElement("parameter");
                LPFilterSustainParamElement->setAttribute("id", "LowPassFilterSustain");
                LPFilterSustainParamElement->setAttribute("value", (double)m_envLPFilterView->m_lpFilterSustainSlider->getValueObject().getValue());
                
                XmlElement* LPFilterReleaseParamElement = mainXmlElement->createNewChildElement("parameter");
                LPFilterReleaseParamElement->setAttribute("id", "LowPassFilterRelease");
                LPFilterReleaseParamElement->setAttribute("value", (double)m_envLPFilterView->m_lpFilterReleaseSlider->getValueObject().getValue());
                
                XmlElement* HPFilterEnvAmountParamElement = mainXmlElement->createNewChildElement("parameter");
                HPFilterEnvAmountParamElement->setAttribute("id", "HighPassFilterEnvAmount");
                HPFilterEnvAmountParamElement->setAttribute("value", (double)m_envHPFilterView->m_hpFilterAmountSlider->getValueObject().getValue());
                
                XmlElement* HPFilterEnvAttackParamElement = mainXmlElement->createNewChildElement("parameter");
                HPFilterEnvAttackParamElement->setAttribute("id", "HighPassFilterAttack");
                HPFilterEnvAttackParamElement->setAttribute("value", (double)m_envHPFilterView->m_hpFilterAttackSlider->getValueObject().getValue());
                
                XmlElement* HPFilterEnvDecayParamElement = mainXmlElement->createNewChildElement("parameter");
                HPFilterEnvDecayParamElement->setAttribute("id", "HighPassFilterDecay");
                HPFilterEnvDecayParamElement->setAttribute("value", (double)m_envHPFilterView->m_hpFilterDecaySlider->getValueObject().getValue());
                
                XmlElement* HPFilterSustainParamElement = mainXmlElement->createNewChildElement("parameter");
                HPFilterSustainParamElement->setAttribute("id", "HighPassFilterSustain");
                HPFilterSustainParamElement->setAttribute("value", (double)m_envHPFilterView->m_hpFilterSustainSlider->getValueObject().getValue());
                
                XmlElement* HPFilterReleaseParamElement = mainXmlElement->createNewChildElement("parameter");
                HPFilterReleaseParamElement->setAttribute("id", "HighPassFilterRelease");
                HPFilterReleaseParamElement->setAttribute("value", (double)m_envHPFilterView->m_hpFilterReleaseSlider->getValueObject().getValue());
                
                XmlElement* WaveTableParamElement = mainXmlElement->createNewChildElement("parameter");
                WaveTableParamElement->setAttribute("id", "table");
                WaveTableParamElement->setAttribute("value", (int)comboBox.getSelectedId());
                
//                XmlElement* HPBypassParamElement = mainXmlElement->createNewChildElement("parameter");
//                HPBypassParamElement->setAttribute("id", "hpBypass");
// //               HPBypassParamElement->setAttribute("value", (bool)CustomTabButton::m_
//                HPBypassParamElement->setAttribute("value", m_attachedProcessor.get_hp_Bypass();
                
                
                XmlElement* amplitudesElement = mainXmlElement->createNewChildElement("amplitudes");
                XmlElement* attackElement = mainXmlElement->createNewChildElement("attack");
                XmlElement* decayElement = mainXmlElement->createNewChildElement("decay");
                XmlElement* sustainElement = mainXmlElement->createNewChildElement("sustain");
                XmlElement* releaseElement = mainXmlElement->createNewChildElement("release");
                XmlElement* pitchAmountElement = mainXmlElement->createNewChildElement("pitchAmount");
                XmlElement* pitchAttackElement = mainXmlElement->createNewChildElement("pitchAttack");
                XmlElement* pitchDecayElement = mainXmlElement->createNewChildElement("pitchDecay");
                XmlElement* pitchSustaintElement = mainXmlElement->createNewChildElement("pitchSustain");
                XmlElement* pitchReleaseElement = mainXmlElement->createNewChildElement("pitchRelease");
                
                
                int numHarmonics = 16;
                
                for(int n = 0 ; n < numHarmonics ;++n){
                    float ampValue = *m_attachedProcessor.s_amplitudes[n];
                    float attackValue = *m_attachedProcessor.s_attackValues[n];
                    float decayValues = *m_attachedProcessor.s_decayValues[n];
                    float sustainValues = *m_attachedProcessor.s_sustainValues[n];
                    float releaseValues = *m_attachedProcessor.s_releaseValues[n];
                    float pitchAmountValues = *m_attachedProcessor.s_pitchAmount[n];
                    float pitchAttackValues = *m_attachedProcessor.s_pitchAttackValues[n];
                    float pitchDecayValues = *m_attachedProcessor.s_pitchDecayValues[n];
                    float pitchSustainValues = *m_attachedProcessor.s_pitchSustainValues[n];
                    float pitchReleaseValues = *m_attachedProcessor.s_pitchReleaseValues[n];
                    
                    String harmonicName("harmonic");
                    String attackName("attack");
                    String decayName("decay");
                    String sustainName("sustain");
                    String releaseName("release");
                    String pitchAmountName("pitchAmount");
                    String pitchAttackName("pitchAttack");
                    String pitchDecayName("pitchDecay");
                    String pitchSustainName("pitchSustain");
                    String pitchReleaseName("pitchRelease");
                    
                    harmonicName += n;
                    attackName += n;
                    decayName += n;
                    sustainName += n;
                    releaseName += n;
                    pitchAmountName += n;
                    pitchAttackName += n;
                    pitchDecayName += n;
                    pitchSustainName += n;
                    pitchReleaseName += n;
                    
                    
                    
                    amplitudesElement->setAttribute(harmonicName, ampValue);
                    attackElement->setAttribute(attackName,attackValue);
                    decayElement->setAttribute(decayName,decayValues);
                    sustainElement->setAttribute(sustainName,sustainValues);
                    releaseElement->setAttribute(releaseName,releaseValues);
                    pitchAmountElement->setAttribute(pitchAmountName, pitchAmountValues);
                    pitchAttackElement->setAttribute(pitchAttackName, pitchAttackValues);
                    pitchDecayElement->setAttribute(pitchDecayName, pitchDecayValues);
                    pitchSustaintElement->setAttribute(pitchSustainName, pitchSustainValues);
                    pitchReleaseElement->setAttribute(pitchReleaseName, pitchReleaseValues);
                    
                }

                mainXmlElement->writeToFile(selectedFile, "");
    
            }
            
            
        }
        
        catch( String message )
        {
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Save XML failed!", message);
            
        }
        
    }
    

}


void SynthAudioProcessorEditor::loadParameters(juce::XmlElement *element)
///Loads data from XML files
{
    
   // presetSelect.setText("Manual Load");
    
    if( element->hasTagName("ParameterTweaker"))
    {
        
        forEachXmlChildElementWithTagName(*element, paramElement, "parameter")
        {
            
            float value = paramElement->getDoubleAttribute("value");
            //std::coutt << value << std::endl;
            
            String paramID = paramElement->getStringAttribute("id");
            
            if(paramID == "Gain")
            {
                mainVol.setValue(value);
            }
            else if(paramID == "LowPass")
            {
                m_filterView->m_lowpassSlider->setValue(value);
            }
            else if (paramID == "HighPass")
            {
                m_filterView->m_highpassSlider->setValue(value);
            }
            else if (paramID == "ReverbWet")
            {
                m_reverbView->m_reverbWet->setValue(value);
            }
            else if (paramID == "ReverbDry")
            {
                m_reverbView->m_reverbDry->setValue(value);
            }
            else if (paramID == "ReverbWidth")
            {
                m_reverbView->m_reverbWidth->setValue(value);
            }
            else if (paramID == "ReverbRoomsize")
            {
                m_reverbView->m_reverbRoomSize->setValue(value);
            }
            else if (paramID == "ReverbDamping")
            {
                m_reverbView->m_reverbDamping->setValue(value);
            }
            else if (paramID == "DelayTimeLeft")
            {
                m_delayView->m_leftDelayTime->setValue(value);
            }
            else if (paramID == "DelayTimeRight")
            {
                m_delayView->m_rightDelayTime->setValue(value);
            }
            else if (paramID == "DelayFeedbackLeft")
            {
                m_delayView->m_leftFeedback->setValue(value);
            }
            else if (paramID == "DelayTimeRight")
            {
                m_delayView->m_rightFeedback->setValue(value);
            }
            else if (paramID == "DistortionAmount")
            {
                m_distortionView->m_distortionAmountSlider->setValue(value);
            }
            else if (paramID == "LowPassFilterEnvAmount")
            {
                m_envLPFilterView->m_lpFilterAmountSlider->setValue(value);
            }
            else if(paramID == "LowPassFilterAttack")
            {
                m_envLPFilterView->m_lpFilterAttackSlider->setValue(value);
            }
            else if (paramID == "LowPassFilterDecay")
            {
                m_envLPFilterView->m_lpFilterDecaySlider->setValue(value);
            }
            else if (paramID == "LowPassFilterSustain")
            {
                m_envLPFilterView->m_lpFilterSustainSlider->setValue(value);
            }
            else if (paramID == "LowPassFilterRelease")
            {
                m_envLPFilterView->m_lpFilterReleaseSlider->setValue(value);
            }
            else if (paramID == "HighPassFilterEnvAmount")
            {
                m_envHPFilterView->m_hpFilterAmountSlider->setValue(value);
            }
            else if(paramID == "HighPassFilterAttack")
            {
                m_envHPFilterView->m_hpFilterAttackSlider->setValue(value);
            }
            else if (paramID == "HighPassFilterDecay")
            {
                m_envHPFilterView->m_hpFilterDecaySlider->setValue(value);
            }
            else if (paramID == "HighPassFilterSustain")
            {
                m_envHPFilterView->m_hpFilterSustainSlider->setValue(value);
            }
            else if (paramID == "HighPassFilterRelease")
            {
                m_envHPFilterView->m_hpFilterReleaseSlider->setValue(value);
            }
            else if (paramID == "table")
            {
                comboBox.setSelectedId(value);
            }
//            else if(paramID == "HPBypass")
//            {
//                m_attachedProcessor.set_hp_Bypass(value);
//            }
            else
            {
                throw String ("Software does not contain the required element ") + paramID;
            }
            
        }
    }
    else
    {
        
        throw String("Could not find ParameterTweaker");
        
    }
    
    forEachXmlChildElementWithTagName(*element, amplitudeElement, "amplitudes")
    {
        for(int n = 0 ; n < 16;++n)
        {
            String harmonicName("harmonic");
            harmonicName += n;
            
            float value = amplitudeElement->getDoubleAttribute(harmonicName);
            *m_attachedProcessor.s_amplitudes[n] = value;
            
        }
        
        
    }
    m_ampMultiSlider->refresh();
    
    forEachXmlChildElementWithTagName(*element, attackElement, "attack")
    {
        for(int n = 0 ; n < 16;++n)
        {
            String attackName("attack");
            attackName += n;
            
            float value = attackElement->getDoubleAttribute(attackName);
            *m_attachedProcessor.s_attackValues[n] = value;
   
        }
        
        
    }
    m_attackMultiSlider->refresh();
    
    forEachXmlChildElementWithTagName(*element, decayElement, "decay")
    {
        for(int n = 0 ; n < 16;++n)
        {
            String decayName("decay");
            decayName += n;
            
            float value = decayElement->getDoubleAttribute(decayName);
            *m_attachedProcessor.s_decayValues[n] = value;
            
        }
        
        
    }
    m_decayMultiSlider->refresh();
    
    forEachXmlChildElementWithTagName(*element, sustainElement, "sustain")
    {
        for(int n = 0 ; n < 16;++n)
        {
            String sustainName("sustain");
            sustainName += n;
            
            float value = sustainElement->getDoubleAttribute(sustainName);
            *m_attachedProcessor.s_sustainValues[n] = value;
            
        }

    }
    m_sustainMultiSlider->refresh();
    
    forEachXmlChildElementWithTagName(*element, releaseElement, "release")
    {
        for(int n = 0 ; n < 16;++n)
        {
            String releaseName("release");
            releaseName += n;
            
            float value = releaseElement->getDoubleAttribute(releaseName);
            *m_attachedProcessor.s_releaseValues[n] = value;
 
        }

    }
    m_releaseMultiSlider->refresh();
    
    
    
    forEachXmlChildElementWithTagName(*element, pitchAmountElement, "pitchAmount")
    {
        for(int n = 0 ; n < 16;++n){
            String pitchAmountName("pitchAmount");
            pitchAmountName += n;
            
            float value = pitchAmountElement->getDoubleAttribute(pitchAmountName);
            *m_attachedProcessor.s_pitchAmount[n] = value;
 
        }
   
    }
    m_pitchEnvelopeMultiSlider->refresh();

    
    forEachXmlChildElementWithTagName(*element, pitchAttackElement, "pitchAttack")
    {
        for(int n = 0 ; n < 16;++n){
            String pitchAttackName("pitchAttack");
            pitchAttackName += n;
            
            float value = pitchAttackElement->getDoubleAttribute(pitchAttackName);
            *m_attachedProcessor.s_pitchAttackValues[n] = value;
            
            
        }
        
        
    }
    m_pitchEnvelopeMultiSlider->refresh();
    
    
    
    forEachXmlChildElementWithTagName(*element, pitchDecayElement, "pitchDecay")
    {
        for(int n = 0 ; n < 16;++n)
        {
            String pitchDecayName("pitchDecay");
            pitchDecayName += n;
            
            float value = pitchDecayElement->getDoubleAttribute(pitchDecayName);
            *m_attachedProcessor.s_pitchDecayValues[n] = value;
   
        }
        
        
    }
    m_pitchEnvelopeMultiSlider->refresh();
    
    
    forEachXmlChildElementWithTagName(*element, pitchSustainElement, "pitchSustain")
    {
        for(int n = 0 ; n < 16;++n){
            String pitchSustainName("pitchSustain");
            pitchSustainName += n;
            
            float value = pitchSustainElement->getDoubleAttribute(pitchSustainName);
            *m_attachedProcessor.s_pitchSustainValues[n] = value;
        }
    }
    m_pitchEnvelopeMultiSlider->refresh();
    
    
    
    forEachXmlChildElementWithTagName(*element, pitchReleaseElement, "pitchRelease")
    {
        for(int n = 0 ; n < 16;++n)
        {
            String pitchReleaseName("pitchRelease");
            pitchReleaseName += n;
            
            float value = pitchReleaseElement->getDoubleAttribute(pitchReleaseName);
            *m_attachedProcessor.s_pitchReleaseValues[n] = value;
        }
    }
    m_pitchEnvelopeMultiSlider->refresh();

}

void SynthAudioProcessorEditor::timerCallback()
///called every 100 millisconds to update UI
{
    updateUI();
    m_effectController->updateSliderPos();
    m_envelopeController->updateEnvSlider();
}







