/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Phillips_crystal_a2AudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    Phillips_crystal_a2AudioProcessorEditor (Phillips_crystal_a2AudioProcessor&);
    ~Phillips_crystal_a2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Slider mixSlider;
    Slider freqSlider;
    
    Label freqLabel;
    Label mixLabel;
    
    
    Slider mixSlider2; // attempt at second fader
    Slider ringSlider; // attempt at second fader
    
    Label mixLabel2; // attempt at second label
    Label ringLabel; // attempt at second label
    
    
    void sliderValueChanged(Slider* slider) override;
    
 // if (slider == &freqSlider)
           // mixSlider.setValue (1.0 / freqSlider.getValue(), dontSendNotification);
//  else if (slider == &mixSlider)
         //   freqSlider.setValue (1.0 / mixSlider.getValue(), dontSendNotification);

    Phillips_crystal_a2AudioProcessor& processor;
    
    //Random random;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Phillips_crystal_a2AudioProcessorEditor)

};
