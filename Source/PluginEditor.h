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
class MidiCidiAudioProcessorEditor : public AudioProcessorEditor,
										private ComboBox::Listener,
										private MidiInputCallback,
										private MidiKeyboardStateListener

{
public:
    MidiCidiAudioProcessorEditor (MidiCidiAudioProcessor&);
    ~MidiCidiAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
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

	void setMidiInput(int index);
	void comboBoxChanged(ComboBox* box) override;
	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;
	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiCidiAudioProcessorEditor)
};
