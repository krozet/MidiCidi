#ifndef SCALES_H
#define SCALES_H
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

/**
Responsible for constructing the scale/mode based on the user's settings
It will take in the midi note number, and output the appropriate note number to achieve the user's settings
*/

class Scales
{
public:
	Scales();
	Scales(int t, int m);
	~Scales();

	void setUserTonic(int t);
	void setUserMode(int m);

	int getUserTonic();
	int getUserMode();

	int getModifiedMidiNote(int note);
	std::vector<int> getUserScale();

	const enum Tonic { C = 0, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B };
	const enum Mode { MAJOR = 0, MINOR, IONIAN, DORIAN, PHRYGIAN, LYDIAN, MIXOLYDIAN, AEOLIAN, LOCRIAN };
	
private:
	int userTonic = 0;
	int userMode = 0;
	int octaveDegree;
	int displacement;

	void setDisplacement();
	std::vector<int> newScale;

	//Modes array - row correspond with enum Mode values
	const int modes[9][12] = {
		{ 0, -150, 0, -150, 0, 0, -150, 0, -150, 0, -150, 0 }, //major scale
		{ 0, -150, 0, -150, -1, 0, -150, 0, -150, -1, -150, -1 }, //minor scale 
		{ 0, -150, 0, -150, 0, 0, -150, 0, -150, 0, -150, 0 }, //ionian mode
		{ 0, -150, 0, -150, -1, 0, -150, 0, -150, 0, -150, -1 }, //dorian mode
		{ 0, -150, -1, -150, -1, 0, -150, 0, -150, -1, -150, -1 }, //phrygian mode
		{ 0, -150, 0, -150, 0, 1, -150, 0, -150, 0, -150, 0 }, //lydian mode
		{ 0, -150, 0, -150, 0, 0, -150, 0, -150, 0, -150, -1 }, //mixolydian mode
		{ 0, -150, 0, -150, -1, 0, -150, 0, -150, -1, -150, -1 }, //aeolian mode
		{ 0, -150, -1, -150, -1, 0, -150, -1, -150, -1, -150, -1 } //locrian mode
	};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Scales)
};

#endif