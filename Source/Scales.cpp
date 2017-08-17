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

int Scales::getUserTonic()
{
	return userTonic;
}

int Scales::getUserMode()
{
	return userMode;
}

int Scales::getModifiedMidiNote(int note)
{
	octaveDegree = note % 12;

	return (note + displacement + modes[userMode][octaveDegree]);
}

std::vector<int> Scales::getUserScale()
{
	newScale.clear();
	for (int i = 0; i < 12; i++)
	{
		if (i != 1 && i != 3 && i != 6 && i != 8 && i != 10)
		{
			newScale.push_back((userTonic + i + modes[userMode][i]) % 12);
		}
	}
	return newScale;
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

void Scales::setUserTonic(int t)
{
	userTonic = t;
	setDisplacement();
}

void Scales::setUserMode(int m)
{
	userMode = m;
}
