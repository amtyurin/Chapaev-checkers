#pragma once
#include "FormationTypes.h"
class ScoreValues
{
	FormationTypes currentformation;	
	int scores;
	int wins;	

public:
	ScoreValues(void);
	~ScoreValues(void);

	static Player turn;
	static int shots;
};

