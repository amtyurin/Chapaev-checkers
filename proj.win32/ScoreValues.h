#pragma once
#include "FormationTypes.h"
class ScoreValues
{
	int wins;		
	int scores;
	int shots;
	FormationTypes currentformation;

public:
	ScoreValues(void);
	~ScoreValues(void);

	static Player turn;
};

