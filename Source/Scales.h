#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ScaleEnums.h"

/**
Responsible for constructing the scale/mode based on the user's settings
It will take in the midi note, and output the appropriate note to achieve the user's settings
*/
class Scales
{
public:
	Scales(ScaleEnums::Tonic t, ScaleEnums::Mode m);
	~Scales();

	int getModifiedMidiNote(int note);

private:
	int userTonic;
	int userMode;

	int octaveDegree;
	int displacement;

	void setDisplacement();

	//Modes array - row correspond with enum Mode values
	const int modes[9][12] = {
		{ 0, -150, 0, -150, 0, 0, -150, 0, -150, 0, -150, 0 }, //major scale
		{ 0, -150, 0, -150, -1, 0, -150, 0, -150, -1, -150, -1 }, //minor scale 
		{ 0, -150, 0, -150, 0, 0, -150, 0, -150, 0, -150, 0 }, //ionian mode
		{ 2, -150, 2, -150, 1, 2, -150, 2, -150, 2, -150, 2 }, //dorian mode
		{ 4, -150, 3, -150, 3, 4, -150, 4, -150, 3, -150, 3 }, //phrygian mode
		{ 5, -150, 5, -150, 5, 6, -150, 5, -150, 5, -150, 5 }, //lydian mode
		{ 7, -150, 7, -150, 7, 7, -150, 7, -150, 7, -150, 6 }, //mixolydian mode
		{ 9, -150, 9, -150, 8, 9, -150, 9, -150, 8, -150, 8 }, //aeolian mode
		{ 11, -150, 10, -150, 10, 11, -150, 10, -150, 10, -150, 10 } //locrian mode
	};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Scales)
};