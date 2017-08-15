#include "Scales.h"

Scales::Scales() : userTonic(Tonic::C), userMode(Mode::MAJOR)
{
	setDisplacement();
}

Scales::~Scales()
{
}

Scales::Scales(int t, int m) : userTonic(t), userMode(m)
{
	setDisplacement();
}

int Scales::getModifiedMidiNote(int note)
{
	octaveDegree = note % 12;

	return (note + displacement + modes[userMode][octaveDegree]);
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
