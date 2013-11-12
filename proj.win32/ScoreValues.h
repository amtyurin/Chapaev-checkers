#pragma once
#include "FormationTypes.h"
class ScoreValues
{


	ScoreValues(void);
	~ScoreValues(void);
public:

	static Player turn;	

	static int winsUser;		
	static int scoresUser;
	static int shotsUser;
	static FormationTypes currentformationUser;

	static int winsAI;		
	static int scoresAI;
	static int shotsAI;
	static FormationTypes currentformationAI;
};

