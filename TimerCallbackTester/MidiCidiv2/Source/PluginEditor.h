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
class MidiCidiv2AudioProcessorEditor  : public AudioProcessorEditor,
										public Label::Listener,
										public HighResolutionTimer
{
public:
    MidiCidiv2AudioProcessorEditor (MidiCidiv2AudioProcessor&);
    ~MidiCidiv2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void labelTextChanged(Label* labelThatHasChanged) override;

	void hiResTimerCallback() override;

	MidiCidiv2AudioProcessor * getProcessor() const;

	Label datLabel;
	Label timerLabel;

	int timerCounter = 0;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiCidiv2AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiCidiv2AudioProcessorEditor)
};
