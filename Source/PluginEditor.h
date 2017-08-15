/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Scales.h"

//==============================================================================
/**
*/
class MidiCidiAudioProcessorEditor : public AudioProcessorEditor,
	private ComboBox::Listener,
	private MidiInputCallback,
	private MidiKeyboardStateListener

{
public:
	MidiCidiAudioProcessorEditor(MidiCidiAudioProcessor&);
	~MidiCidiAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	MidiCidiAudioProcessor& processor;
	AudioDeviceManager deviceManager;
	ComboBox midiInputList;
	Label midiInputListLabel;
	int lastInputIndex;
	bool isAddingFromMidiInput;

	MidiKeyboardState keyboardState;
	MidiKeyboardComponent keyboardComponent;

	TextEditor midiMessagesBox;
	double startTime;
	void midiMessageBoxVisibility();
	void midiInputListVisibility();
	void midiKeyboardVisibility();

	///working code
	void tonicListVisibility();
	void modeListVisibility();
	ComboBox modeList;
	ComboBox tonicList;
	Label modeListLabel;
	Label tonicListLabel;
	String tonics[12] = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };
	String modes[9] = { "Major", "Minor", "Ionian", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian" };

	void addDataToList(StringArray str);
	int tonicIndex;
	int modeIndex;
	void adjustMessageNoteValue(MidiMessage& message); //take a look at this, remove all instances of this shit
	Scales user;
	Scales &createUserMode();

	void setMidiInput(int index);
	void logMessage(const String& m);
	void postMessageToList(const MidiMessage& message, const String& source);
	void addMessageToList(const MidiMessage& message, const String& source);
	static String getMidiMessageDescription(const MidiMessage& m);

	void comboBoxChanged(ComboBox* box) override;
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

	class IncomingMessageCallback : public CallbackMessage
	{
	public:
		IncomingMessageCallback(MidiCidiAudioProcessorEditor* o, const MidiMessage& m, const String& s)
			: owner(o), message(m), source(s)
		{}

		void messageCallback() override
		{
			if (owner != nullptr) {
				owner->adjustMessageNoteValue(message);
				owner->addMessageToList(message, source);
			}
		}

		Component::SafePointer<MidiCidiAudioProcessorEditor> owner;
		MidiMessage message;
		String source;
	};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCidiAudioProcessorEditor)
};
