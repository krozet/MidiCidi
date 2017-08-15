/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidiCidiv2AudioProcessorEditor::MidiCidiv2AudioProcessorEditor (MidiCidiv2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
	startTimer(1000);
}

MidiCidiv2AudioProcessorEditor::~MidiCidiv2AudioProcessorEditor()
{
}

//==============================================================================
void MidiCidiv2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);

	datLabel.setBounds(getLocalBounds());
	datLabel.setJustificationType(Justification::centred);
	//datLabel.setText("Dat Placeholder Text", dontSendNotification);

	timerLabel.setBounds(getLocalBounds());
	timerLabel.setJustificationType(Justification::bottomRight);
	//timerLabel.setText("Timer Label Text", dontSendNotification);

	addAndMakeVisible(datLabel);
	addAndMakeVisible(timerLabel);

}

void MidiCidiv2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MidiCidiv2AudioProcessorEditor::labelTextChanged(Label* labelThatHasChanged)
{
	labelThatHasChanged->setText("This worked", dontSendNotification);
}

void MidiCidiv2AudioProcessorEditor::hiResTimerCallback()
{
	timerCounter++;
	MidiCidiv2AudioProcessor* daProcessor = getProcessor();

	String daNewText = daProcessor->daString;

	//datLabel.setText(daNewText, dontSendNotification);
	datLabel.setText("Got to Callback", dontSendNotification);

	//timerLabel.setText("Timer Counter: " + (String)timerCounter, dontSendNotification);
	timerLabel.setText(daNewText, dontSendNotification);
}

MidiCidiv2AudioProcessor* MidiCidiv2AudioProcessorEditor::getProcessor() const
{
	return static_cast <MidiCidiv2AudioProcessor*> (getAudioProcessor());
}