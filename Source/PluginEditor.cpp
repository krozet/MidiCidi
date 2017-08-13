/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidiCidiAudioProcessorEditor::MidiCidiAudioProcessorEditor (MidiCidiAudioProcessor& p)
    : AudioProcessorEditor (&p),
	processor (p),
	lastInputIndex(0),
	isAddingFromMidiInput(false), 
	keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard),
	startTime(Time::getMillisecondCounterHiRes() * 0.001)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setOpaque(true);

	addAndMakeVisible(midiInputListLabel);
	midiInputListLabel.setText("MIDI Input:", dontSendNotification);
	midiInputListLabel.attachToComponent(&midiInputList, true);

	addAndMakeVisible(midiInputList);
	midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
	const StringArray midiInputs(MidiInput::getDevices());
	midiInputList.addItemList(midiInputs, 1);
	midiInputList.addListener(this);

	// find the first enabled device and use that by default
	for (int i = 0; i < midiInputs.size(); ++i)
	{
		if (deviceManager.isMidiInputEnabled(midiInputs[i]))
		{
			setMidiInput(i);
			break;
		}
	}

	// if no enabled devices were found just use the first one in the list
	if (midiInputList.getSelectedId() == 0)
		setMidiInput(0);

	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);

	addAndMakeVisible(midiMessagesBox);
	midiMessagesBox.setMultiLine(true);
	midiMessagesBox.setReturnKeyStartsNewLine(true);
	midiMessagesBox.setReadOnly(true);
	midiMessagesBox.setScrollbarsShown(true);
	midiMessagesBox.setCaretVisible(false);
	midiMessagesBox.setPopupMenuEnabled(true);
	midiMessagesBox.setColour(TextEditor::backgroundColourId, Colour(0x32ffffff));
	midiMessagesBox.setColour(TextEditor::outlineColourId, Colour(0x1c000000));
	midiMessagesBox.setColour(TextEditor::shadowColourId, Colour(0x16000000));

	setSize(600, 400);
}

MidiCidiAudioProcessorEditor::~MidiCidiAudioProcessorEditor()
{
}

//==============================================================================
void MidiCidiAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MidiCidiAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MidiCidiAudioProcessorEditor::setMidiInput(int index)
{
	const StringArray list(MidiInput::getDevices());

	deviceManager.removeMidiInputCallback(list[lastInputIndex], this);

	const String newInput(list[index]);

	if (!deviceManager.isMidiInputEnabled(newInput))
		deviceManager.setMidiInputEnabled(newInput, true);

	deviceManager.addMidiInputCallback(newInput, this);
	midiInputList.setSelectedId(index + 1, dontSendNotification);

	lastInputIndex = index;
}

void MidiCidiAudioProcessorEditor::comboBoxChanged(ComboBox * box)
{
}

void MidiCidiAudioProcessorEditor::handleIncomingMidiMessage(MidiInput * source, const MidiMessage & message)
{
}

void MidiCidiAudioProcessorEditor::handleNoteOn(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity)
{
}

void MidiCidiAudioProcessorEditor::handleNoteOff(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity)
{
}
