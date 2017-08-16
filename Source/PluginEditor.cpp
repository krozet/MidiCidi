#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>

MidiCidiAudioProcessorEditor::MidiCidiAudioProcessorEditor (MidiCidiAudioProcessor& p)
    : AudioProcessorEditor (&p),
		processor (p)
{
	setOpaque(true);

	tonicListVisibility();
	modeListVisibility();

	setSize(600, 400);
}

MidiCidiAudioProcessorEditor::~MidiCidiAudioProcessorEditor()
{
}

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
	Rectangle<int> area(getLocalBounds());
	Rectangle<int> tonicBox(250, 43, 65, 20);

	modeList.setBounds(area.removeFromTop(36).removeFromRight(getWidth() - 450).reduced(8));
	tonicList.setBounds(tonicBox);
}

void MidiCidiAudioProcessorEditor::tonicListVisibility()
{
	addAndMakeVisible(tonicListLabel);
	tonicListLabel.setText("Select the Tonic note:", dontSendNotification);
	tonicListLabel.attachToComponent(&tonicList, true);

	//Combo box starts id at 1, not 0
	for (int i = 0; i < 12; i++)
	{
		tonicList.addItem(tonics[i], i+1);
	}
	addAndMakeVisible(tonicList);
	tonicList.setSelectedItemIndex(0, dontSendNotification);
	tonicList.addListener(this);
}

void MidiCidiAudioProcessorEditor::modeListVisibility()
{
	addAndMakeVisible(modeListLabel);
	modeListLabel.setText("Select the Mode:", dontSendNotification);
	modeListLabel.attachToComponent(&modeList, true);

	//Combo box starts id at 1, not 0
	for (int i = 0; i < 9; i++)
	{
		if (i == 2)
			modeList.addSeparator();
		modeList.addItem(modes[i], i + 1);
	}
	addAndMakeVisible(modeList);
	modeList.setSelectedItemIndex(0, dontSendNotification);
	modeList.addListener(this);
}

void MidiCidiAudioProcessorEditor::comboBoxChanged(ComboBox * box)
{
	if (box == &tonicList)
	{
		tonicIndex = tonicList.getSelectedItemIndex();
		if (tonicIndex < 0 || tonicIndex > 12) 
			tonicIndex = 0;

		processor.userScale.setUserTonic(tonicIndex);
	}

	if (box == &modeList)
	{
		modeIndex = modeList.getSelectedItemIndex();
		if (modeIndex < 0 || modeIndex > 9)
			modeIndex = 0;
		processor.userScale.setUserMode(modeIndex);
	}
}
