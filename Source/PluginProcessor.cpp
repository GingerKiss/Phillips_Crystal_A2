/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Phillips_crystal_a2AudioProcessor::Phillips_crystal_a2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    currentSampleRate = 0.0f;
    currentAngle = 0.0f;
    angleDelta = 0.0f;
    sinFreq = 0.0f;
    
    
}

Phillips_crystal_a2AudioProcessor::~Phillips_crystal_a2AudioProcessor()
{
}

//==============================================================================
const String Phillips_crystal_a2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Phillips_crystal_a2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Phillips_crystal_a2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Phillips_crystal_a2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Phillips_crystal_a2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Phillips_crystal_a2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Phillips_crystal_a2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Phillips_crystal_a2AudioProcessor::setCurrentProgram (int index)
{
}

const String Phillips_crystal_a2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Phillips_crystal_a2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Phillips_crystal_a2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    currentSampleRate = sampleRate;
    sinFreq = 1.0f;
    updateAngleDelta();
    
    mixLevel.reset(sampleRate, 0.5f);
    mixLevel.setTargetValue(0.15f);
    
    
    gain.setGainDecibels(0.2f);
    
    String message;
    message << "Preparing to play..." << newLine;
    message <<"My sample rate is " << currentSampleRate << newLine;
    message << "Buffer size is " << samplesPerBlock << newLine;
    Logger::getCurrentLogger()->writeToLog(message);
}

void Phillips_crystal_a2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Phillips_crystal_a2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Phillips_crystal_a2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    //set up copy of input buffer so we can keep original
    AudioBuffer<float> wetBuffer(totalNumInputChannels, buffer.getNumSamples());
    wetBuffer.makeCopyOf(buffer);
    
    //we are going each channel
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // put channel 0 audio buffer into channelData variable
        // we are getting an audio block of size 512
        auto* channelData = buffer.getWritePointer (channel);
        auto* wetData = wetBuffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // IN THIS LOOP IS VARIOUS CODES
            
            // CODE 1
            // generating a set of random values to modulate input amplitude
            
            float modulator = random.nextFloat() * 0.5f - 0.25f;
            wetData[sample] = wetData[sample] * modulator; //scaling and offsetting
            
            
            // CODE 2
            //calculate value to put into buffer
            auto currentSinSample = (float) std::sin(currentAngle);
            currentAngle += angleDelta; // currentAngle = currentAngle + angleDelta
            
            //lets make our sine wave wiggle
            modulator = random.nextFloat() * 0.1f - 0.05f;
            wetData[sample] = wetData[sample] * currentSinSample; // + modulator);
            
            //soft-clip with hypobolic tangent
            //auto shapedSample = jlimit((float) -0.8, (float) 0.8, wetData[sample]);
            //auto shapedSample = (float) std::tanh(wetData[sample]);
            //wetData[sample] = shapedSample;
            
            
            //add original dry signal with processed signal into our output buffer (a.k.a input buffer)
            channelData[sample] = channelData[sample] * 0.7f + wetData[sample] * 0.20f;
            //channelData[sample] = jlimit((float) -0.1, (float) 0.1, wetData[sample]);
            
            channelData[sample] = channelData[sample] + wetData[sample] * mixLevel.getNextValue();
            
            //wetData[sample] * mixLevel; //jlimit((float) -0.1, (float) 0.1, wetData[sample]);  * 0.5f; // + wetData[sample] * 0.5f;
            //=======================================================================
        }
    }
    dsp::AudioBlock<float> output(buffer);
    gain.process(dsp::ProcessContextReplacing<float>(output));
    // duplicate buffer for audioVisualComponent
    returnAudioBuffer.makeCopyOf(buffer);
}
//==============================================================================
bool Phillips_crystal_a2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Phillips_crystal_a2AudioProcessor::createEditor()
{
    return new Phillips_crystal_a2AudioProcessorEditor (*this);
}

//==============================================================================
void Phillips_crystal_a2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Phillips_crystal_a2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// User functions

void Phillips_crystal_a2AudioProcessor::updateAngleDelta()
{
    // calculate number of cycles that we will need to complete for each output sample
    auto cyclesPerSample = sinFreq / currentSampleRate;
    // multiply by the length of a whole sin wave cycle
    angleDelta = cyclesPerSample * 2.0f * MathConstants<float>::twoPi;
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Phillips_crystal_a2AudioProcessor();
}
