#pragma once
#include "FormationTypes.h"
#include "Checker.h"

class ScoreValues
{
	ScoreValues(void);
	~ScoreValues(void);
public:

	static Player turn;	

	static int winsUser;		
	static int scoresUser;
	static int shotsUser;
	static int survivedUser;
	static FormationTypes currentformationUser;

	static int winsAI;		
	static int scoresAI;
	static int shotsAI;
	static int survivedAI;
	static FormationTypes currentformationAI;
	
	static void CountScores(std::list<Checker*> *checkerList, Player player);

	static bool AnyMovementAroundBoard;
};

