/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidiCidiv2AudioProcessor::MidiCidiv2AudioProcessor()
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
	setMidiInput(0);
	outStream = MidiOutput::openDevice(0);
}

MidiCidiv2AudioProcessor::~MidiCidiv2AudioProcessor()
{
}


void MidiCidiv2AudioProcessor::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
	daString = "Note Number Is: " + (String)message.getNoteNumber();

}

void MidiCidiv2AudioProcessor::setMidiInput(int index)
{
	const StringArray list(MidiInput::getDevices());

	daString = "Setting Midi Input Info";

	//deviceManager.removeMidiInputCallback(list[lastInputIndex], this);

	const String newInput(list[index]);

	if (!deviceManager.isMidiInputEnabled(newInput))
		deviceManager.setMidiInputEnabled(newInput, true);

	deviceManager.addMidiInputCallback(newInput, this);

	//lastInputIndex = index;
}

//==============================================================================
const String MidiCidiv2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiCidiv2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiCidiv2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double MidiCidiv2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiCidiv2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiCidiv2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiCidiv2AudioProcessor::setCurrentProgram (int index)
{
}

const String MidiCidiv2AudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiCidiv2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidiCidiv2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MidiCidiv2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiCidiv2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MidiCidiv2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool MidiCidiv2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiCidiv2AudioProcessor::createEditor()
{
    return new MidiCidiv2AudioProcessorEditor (*this);
}

//==============================================================================
void MidiCidiv2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiCidiv2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiCidiv2AudioProcessor();
}
