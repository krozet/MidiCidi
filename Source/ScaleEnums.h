#include "../JuceLibraryCode/JuceHeader.h"

class ScaleEnums
{
public:
	const enum Tonic { C, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B };
	const enum Mode {MAJOR, MINOR, IONIAN, DORIAN, PHRYGIAN, LYDIAN, MIXOLYDIAN, AEOLIAN, LOCRIAN};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaleEnums)
};
