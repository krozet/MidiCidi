#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <string>

MidiCidiAudioProcessorEditor::MidiCidiAudioProcessorEditor(MidiCidiAudioProcessor& p)
	: AudioProcessorEditor(&p),
	processor(p),
	comboBoxColor(91, 131, 123),
	comboBoxTextColor(240, 210, 182),
	labelTextColor(249, 210, 182),
	pianoKeysColor(161, 46, 41),
	comboBoxArrowColor(226, 172, 66)
{
	setSize(600, 350);

	background = ImageCache::getFromMemory(images::landonBackgroundthing_png, images::landonBackgroundthing_pngSize);
	keyboard = ImageCache::getFromMemory(images::keyboard_png, images::keyboard_pngSize);

	setOpaque(true);
	changeKeysText();

	tonicListVisibility();
	modeListVisibility();
	keysVisibility();
}

MidiCidiAudioProcessorEditor::~MidiCidiAudioProcessorEditor()
{
}

void MidiCidiAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.drawImage(background, 0, 0, 600, 350, 0, 0, 1215, 763);
	g.drawImage(keyboard, 50, 150, 500, 200, 0, 0, 2000, 1491);

	g.setColour(Colours::white);
	g.setFont(15.0f);
}

void MidiCidiAudioProcessorEditor::resized()
{
	Rectangle<int> area(getLocalBounds());
	Rectangle<int> tonicBox(197, 64, 65, 20);
	Rectangle<int> modeBox(398, 64, 130, 20);

	modeList.setBounds(modeBox);
	tonicList.setBounds(tonicBox);

}

void MidiCidiAudioProcessorEditor::tonicListVisibility()
{
	addAndMakeVisible(tonicListLabel);
	tonicListLabel.setText("Select the Tonic note:", dontSendNotification);
	tonicListLabel.attachToComponent(&tonicList, true);
	tonicListLabel.setColour(Label::textColourId, labelTextColor);

	//Combo box starts id at 1, not 0
	for (int i = 0; i < 12; i++)
	{
		tonicList.addItem(tonics[i], i + 1);
	}
	addAndMakeVisible(tonicList);
	tonicList.setSelectedItemIndex(processor.tonicIndex, dontSendNotification);
	tonicList.addListener(this);
	tonicList.setColour(ComboBox::backgroundColourId, comboBoxColor);
	tonicList.setColour(ComboBox::textColourId, comboBoxTextColor);
	tonicList.setColour(ComboBox::arrowColourId, comboBoxArrowColor);
}

void MidiCidiAudioProcessorEditor::modeListVisibility()
{
	addAndMakeVisible(modeListLabel);
	modeListLabel.setText("Select the Mode:", dontSendNotification);
	modeListLabel.attachToComponent(&modeList, true);
	modeListLabel.setColour(Label::textColourId, labelTextColor);

	//Combo box starts id at 1, not 0
	for (int i = 0; i < 9; i++)
	{
		if (i == 2)
			modeList.addSeparator();
		modeList.addItem(modes[i], i + 1);
	}
	addAndMakeVisible(modeList);
	modeList.setSelectedItemIndex(processor.modeIndex, dontSendNotification);
	modeList.addListener(this);
	modeList.setColour(ComboBox::backgroundColourId, comboBoxColor);
	modeList.setColour(ComboBox::textColourId, comboBoxTextColor);
	modeList.setColour(ComboBox::arrowColourId, comboBoxArrowColor);
}

void MidiCidiAudioProcessorEditor::keysVisibility()
{
	changeKeysText();
	keys.bold;
	keys.setHeight(21.5f);

	addAndMakeVisible(cKey);
	cKey.setBounds(79, 292, 50, 50);
	cKey.setColour(Label::textColourId, pianoKeysColor);
	cKey.setFont(keys);

	addAndMakeVisible(dKey);
	dKey.setBounds(148, 292, 50, 50);
	dKey.setColour(Label::textColourId, pianoKeysColor);
	dKey.setFont(keys);

	addAndMakeVisible(eKey);
	eKey.setBounds(220, 292, 50, 50);
	eKey.setColour(Label::textColourId, pianoKeysColor);
	eKey.setFont(keys);

	addAndMakeVisible(fKey);
	fKey.setBounds(292, 292, 50, 50);
	fKey.setColour(Label::textColourId, pianoKeysColor);
	fKey.setFont(keys);

	addAndMakeVisible(gKey);
	gKey.setBounds(362, 292, 50, 50);
	gKey.setColour(Label::textColourId, pianoKeysColor);
	gKey.setFont(keys);

	addAndMakeVisible(aKey);
	aKey.setBounds(434, 292, 50, 50);
	aKey.setColour(Label::textColourId, pianoKeysColor);
	aKey.setFont(keys);


	addAndMakeVisible(bKey);
	bKey.setBounds(506, 292, 50, 50);
	bKey.setColour(Label::textColourId, pianoKeysColor);
	bKey.setFont(keys);
}

void MidiCidiAudioProcessorEditor::changeKeysText()
{
	userScale.clear();
	userScale = processor.userScale.getUserScale();
	cKey.setText(tonics[userScale[0]], dontSendNotification);
	dKey.setText(tonics[userScale[1]], dontSendNotification);
	eKey.setText(tonics[userScale[2]], dontSendNotification);
	fKey.setText(tonics[userScale[3]], dontSendNotification);
	gKey.setText(tonics[userScale[4]], dontSendNotification);
	aKey.setText(tonics[userScale[5]], dontSendNotification);
	bKey.setText(tonics[userScale[6]], dontSendNotification);
}

void MidiCidiAudioProcessorEditor::comboBoxChanged(ComboBox * box)
{
	if (box == &tonicList)
	{
		tonicIndex = processor.tonicIndex = tonicList.getSelectedItemIndex();
		if (tonicIndex < 0 || tonicIndex > 12)
			tonicIndex = processor.tonicIndex = 0;

		processor.userScale.setUserTonic(tonicIndex);
		changeKeysText();
	}

	if (box == &modeList)
	{
		modeIndex = processor.modeIndex = modeList.getSelectedItemIndex();
		if (modeIndex < 0 || modeIndex > 9)
			modeIndex = processor.modeIndex = 0;

		processor.userScale.setUserMode(modeIndex);
		changeKeysText();
	}
}
