#pragma once
#include "Checker.h"

class AIControl
{
	std::list<Checker*> *checkerListAI;
	std::list<Checker*> *checkerListUser;

public:
	AIControl(std::list<Checker*> *user, std::list<Checker*> *ai);
	~AIControl(void);

	void MakeTurn();
};

