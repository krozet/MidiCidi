#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Scales.h"

class MidiCidiAudioProcessorEditor : public AudioProcessorEditor,
									private ComboBox::Listener

{
public:
	MidiCidiAudioProcessorEditor(MidiCidiAudioProcessor&);
	~MidiCidiAudioProcessorEditor();

	void paint(Graphics&) override;
	void resized() override;

private:
	MidiCidiAudioProcessor& processor;
	ComboBox modeList;
	ComboBox tonicList;
	Label modeListLabel;
	Label tonicListLabel;
	int modeIndex;
	int tonicIndex;

	void tonicListVisibility();
	void modeListVisibility();

	void comboBoxChanged(ComboBox* box) override;

	String tonics[12] = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };
	String modes[9] = { "Major", "Minor", "Ionian", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian" };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCidiAudioProcessorEditor)
};
