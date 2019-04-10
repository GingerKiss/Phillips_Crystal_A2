/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class Phillips_crystal_a2AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Phillips_crystal_a2AudioProcessor();
    ~Phillips_crystal_a2AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioBuffer<float> returnAudioBuffer;
    dsp::Gain<float> gain;
    SmoothedValue<float> mixLevel;
    //float mixLevel;
    
private:
    float currentSampleRate;
    double systemSampleRate;
    float currentAngle;
    float angleDelta;
    float sinFreq;
    
    
    void updateAngleDelta(); //this doesnt return anything just runs whats inside it
    Random random;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Phillips_crystal_a2AudioProcessor)
};
