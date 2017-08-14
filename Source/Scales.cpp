#include "Scales.h"

Scales::Scales(ScaleEnums::Tonic t, ScaleEnums::Mode m) : userTonic(t), userMode(m)
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
