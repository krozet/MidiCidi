/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Scales.h"
#include <string>


//==============================================================================
MidiCidiAudioProcessorEditor::MidiCidiAudioProcessorEditor (MidiCidiAudioProcessor& p)
    : AudioProcessorEditor (&p),
		processor (p),
		lastInputIndex(0),
		isAddingFromMidiInput(false), 
		keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard),
		startTime(Time::getMillisecondCounterHiRes() * 0.001)
{
	setOpaque(true);

	midiInputListVisibility();
	midiKeyboardVisibility();
	midiMessageBoxVisibility();
	tonicListVisibility();

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
    g.drawFittedText ("Suck all seven of my dicks", getLocalBounds(), Justification::centred, 1);
}

void MidiCidiAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	Rectangle<int> area(getLocalBounds());
	midiInputList.setBounds(area.removeFromTop(36).removeFromRight(getWidth() - 150).reduced(8));
	tonicList.setBounds(area.removeFromTop(36).removeFromRight(getWidth() - 500).reduced(8));
	keyboardComponent.setBounds(area.removeFromTop(80).reduced(8));
	midiMessagesBox.setBounds(area.reduced(8));
}

void MidiCidiAudioProcessorEditor::midiMessageBoxVisibility()
{
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
}

void MidiCidiAudioProcessorEditor::midiInputListVisibility()
{
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
}

void MidiCidiAudioProcessorEditor::midiKeyboardVisibility()
{
	addAndMakeVisible(keyboardComponent);
	keyboardState.addListener(this);
}

void MidiCidiAudioProcessorEditor::tonicListVisibility()
{
	addAndMakeVisible(tonicListLabel);
	tonicListLabel.setText("Select the Tonic note:", dontSendNotification);
	tonicListLabel.attachToComponent(&tonicList, true);

	for (int i = 0; i < 12; i++)
	{
		tonicList.addItem(tonics[i], i+1);
	}
	addAndMakeVisible(tonicList);
	tonicList.addListener(this);
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

void MidiCidiAudioProcessorEditor::logMessage(const String & m)
{
	midiMessagesBox.moveCaretToEnd();
	midiMessagesBox.insertTextAtCaret(m + newLine);
}

void MidiCidiAudioProcessorEditor::postMessageToList(const MidiMessage & message, const String & source)
{
	(new IncomingMessageCallback(this, message, source))->post();
}

void MidiCidiAudioProcessorEditor::addMessageToList(const MidiMessage & message, const String & source)
{
	const double time = message.getTimeStamp() - startTime;

	const int hours = ((int)(time / 3600.0)) % 24;
	const int minutes = ((int)(time / 60.0)) % 60;
	const int seconds = ((int)time) % 60;
	const int millis = ((int)(time * 1000.0)) % 1000;

	const String timecode(String::formatted("%02d:%02d:%02d.%03d",
		hours,
		minutes,
		seconds,
		millis));

	const int midiNote = message.getNoteNumber();

	const String description(getMidiMessageDescription(message));

	const String midiMessageString(timecode + "  :  " + description + " (" + source + ") " + "Midi Note Number: " + std::to_string(midiNote));
	logMessage(midiMessageString);
}

String MidiCidiAudioProcessorEditor::getMidiMessageDescription(const MidiMessage & m)
{
	if (m.isNoteOn())           return "Note on " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
	if (m.isNoteOff())          return "Note off " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3);
	if (m.isProgramChange())    return "Program change " + String(m.getProgramChangeNumber());
	if (m.isPitchWheel())       return "Pitch wheel " + String(m.getPitchWheelValue());
	if (m.isAftertouch())       return "After touch " + MidiMessage::getMidiNoteName(m.getNoteNumber(), true, true, 3) + ": " + String(m.getAfterTouchValue());
	if (m.isChannelPressure())  return "Channel pressure " + String(m.getChannelPressureValue());
	if (m.isAllNotesOff())      return "All notes off";
	if (m.isAllSoundOff())      return "All sound off";
	if (m.isMetaEvent())        return "Meta event";

	if (m.isController())
	{
		String name(MidiMessage::getControllerName(m.getControllerNumber()));

		if (name.isEmpty())
			name = "[" + String(m.getControllerNumber()) + "]";

		return "Controller " + name + ": " + String(m.getControllerValue());
	}

	return String::toHexString(m.getRawData(), m.getRawDataSize());
}

void MidiCidiAudioProcessorEditor::comboBoxChanged(ComboBox * box)
{
	if (box == &midiInputList)
		setMidiInput(midiInputList.getSelectedItemIndex());
}

void MidiCidiAudioProcessorEditor::handleIncomingMidiMessage(MidiInput * source, const MidiMessage & message)
{
	const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
	keyboardState.processNextMidiEvent(message);
	postMessageToList(message, source->getName());
}

void MidiCidiAudioProcessorEditor::handleNoteOn(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity)
{
	if (!isAddingFromMidiInput)
	{
		MidiMessage m(MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity));
		m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
		postMessageToList(m, "On-Screen Keyboard");
	}
}

void MidiCidiAudioProcessorEditor::handleNoteOff(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity)
{
	if (!isAddingFromMidiInput)
	{
		MidiMessage m(MidiMessage::noteOff(midiChannel, midiNoteNumber));
		m.setTimeStamp(Time::getMillisecondCounterHiRes() * 0.001);
		postMessageToList(m, "On-Screen Keyboard");
	}
}
