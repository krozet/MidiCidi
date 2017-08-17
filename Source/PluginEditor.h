#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Scales.h"
#include "images.h"
#include <vector>

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

	Image keyboard;
	std::vector<int> userScale;
	Font keys;
	Label cKey;
	Label dKey;
	Label eKey;
	Label fKey;
	Label gKey;
	Label aKey;
	Label bKey;

	ComboBox modeList;
	ComboBox tonicList;
	Label modeListLabel;
	Label tonicListLabel;

	int modeIndex;
	int tonicIndex;

	void tonicListVisibility();
	void modeListVisibility();
	void keysVisibility();

	void changeKeysText();

	void comboBoxChanged(ComboBox* box) override;

	String whiteKeys[7] = { "C", "D", "E", "F", "G", "A", "B" };
	String tonics[12] = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };
	String modes[9] = { "Major", "Minor", "Ionian", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian" };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiCidiAudioProcessorEditor)
};
