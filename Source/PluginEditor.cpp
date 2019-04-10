/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Phillips_crystal_a2AudioProcessorEditor::Phillips_crystal_a2AudioProcessorEditor (Phillips_crystal_a2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    mixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mixSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::skyblue);
    mixSlider.setRange(0.0f, 2000.0f);
    mixSlider.setTextValueSuffix("%");
    mixSlider.addListener(this);
    addAndMakeVisible(mixSlider);
    
    //Second Slider
    mixSlider2.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mixSlider2.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colours::greenyellow);
    mixSlider2.setTextValueSuffix("%");
    addAndMakeVisible(mixSlider2);
    
    ringSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 80, 12);
    ringSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    ringSlider.setRange(0.0f, 2000.0f);
    ringSlider.setTextValueSuffix("Hz");
    ringSlider.addListener(this);
    addAndMakeVisible(ringSlider);
    
    
    freqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 80, 12);
    freqSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    freqSlider.setValue (500.0);
    freqSlider.setTextValueSuffix("Hz");
    freqSlider.addListener(this);
    addAndMakeVisible(freqSlider);
    
    addAndMakeVisible(mixLabel);
    mixLabel.setText("Wet/ Dry Mix", dontSendNotification);
    mixLabel.attachToComponent(&mixSlider, false);
    
    addAndMakeVisible(mixLabel2);
    mixLabel2.setText("Ring Freq Sweep", dontSendNotification);
    mixLabel2.attachToComponent(&mixSlider2, false);

}

Phillips_crystal_a2AudioProcessorEditor::~Phillips_crystal_a2AudioProcessorEditor()
{
}


//==============================================================================
void Phillips_crystal_a2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::orangered);

    g.setColour(Colours::indianred);
    //g.drawRect(150, 10, 250, 100);
    g.fillRect(150, 10, 250, 100);
    g.drawEllipse(getWidth()/4, getHeight()/4, 90, 80, 90);
    g.drawEllipse(getWidth()/2, getHeight()/8, 60, 30, 70);
    g.drawEllipse(getWidth()/6, getHeight()/5, 50, 100, 40);
    g.drawEllipse(getWidth()/8, getHeight()/6, 40, 70, 30);
    
    g.setColour(Colours::black);
    g.drawLine(0.0f, 0.0f, getWidth(), getHeight());
    
    g.fillEllipse(getWidth()/2, getHeight()/2, 60, 60);
    
    g.setColour(Colours::black);
    g.setFont(Font("Arial", 20.0f, Font::italic));
    g.drawFittedText("Ur song is ruined lol", 10, 10, getWidth(), 50, Justification:: left, 1);
    
    g.setColour (Colours::black);
    g.setFont (Font ("New Times Roman", 30.0f, Font::italic));
    g.drawFittedText ("Ruin ur song xx", getLocalBounds(), 200, Justification::centred, 1);
    
     mixSlider.setBounds(10, getHeight()-100, 150, 150);
     mixLabel.setBounds(70, getHeight()-100, 80, 80);
    
     mixSlider2.setBounds(10, getHeight()-200, 150, 150);
     mixLabel2.setBounds(70, getHeight()-210, 80, 100);
}

void Phillips_crystal_a2AudioProcessorEditor::resized()
{
    
}


void Phillips_crystal_a2AudioProcessorEditor::sliderValueChanged(Slider* slider){

    if (slider == &mixSlider)
    {
        // This is generally where you'll want to lay out the positions of any
        // subcomponents in your editor..
        
        //processor.mixLevel = mixSlider.getValue();
        processor.mixLevel.setTargetValue(mixSlider.getValue());
    } else if (slider == &freqSlider){
        //get the value on current slider, pass that value to our audio processor
        }
}
