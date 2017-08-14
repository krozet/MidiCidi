#include "Scales.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

Scales::Scales(Tonic t, Mode m) : userTonic(t), userMode(m)
{
	setDisplacement();
}

int Scales::getModifiedMidiNote(int note)
{
	octaveDegree = note % 12;

	return (displacement + modes[userMode][octaveDegree]);
}

void Scales::setDisplacement()
{
	if (userTonic <= 6) {
		displacement = userTonic;
	}
	else {
		displacement = userTonic - 12;
	}
}
