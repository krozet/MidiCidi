/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>

//==============================================================================
MidiCidiAudioProcessor::MidiCidiAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
		), userScale(0, 0)
#endif
{
}

MidiCidiAudioProcessor::~MidiCidiAudioProcessor()
{
}

//==============================================================================
const String MidiCidiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiCidiAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiCidiAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double MidiCidiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiCidiAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiCidiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiCidiAudioProcessor::setCurrentProgram (int index)
{
}

const String MidiCidiAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiCidiAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidiCidiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MidiCidiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiCidiAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MidiCidiAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	buffer.clear();

	MidiBuffer processedMidi;
	int time;
	MidiMessage m;

	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		if (m.isNoteOn())
		{
			
			newNote = userScale.getModifiedMidiNote(oldNote = m.getNoteNumber());
			if (newNote < 0 || newNote > 127)
			{
				newVel = (uint8)0;
			}

			else
			{
				newVel = m.getVelocity();
			}

			m = MidiMessage::noteOn(m.getChannel(), newNote, newVel);

			noteString = "Input Note: " + MidiMessage::getMidiNoteName(oldNote, false, true, 4) + " Note Being Played: " + MidiMessage::getMidiNoteName(newNote, false, true, 4);
		}
		else if (m.isNoteOff())
		{
			newNote = userScale.getModifiedMidiNote(oldNote = m.getNoteNumber());

			m = MidiMessage::noteOff(m.getChannel(), newNote, (uint8)0);
		}
		else if (m.isAftertouch())
		{
		}
		else if (m.isPitchWheel())
		{
		}

		processedMidi.addEvent(m, time);
	}

	midiMessages.swapWith(processedMidi);
}

//==============================================================================
bool MidiCidiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiCidiAudioProcessor::createEditor()
{
    return new MidiCidiAudioProcessorEditor (*this);
}

//==============================================================================
void MidiCidiAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void MidiCidiAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiCidiAudioProcessor();
}
