#pragma once
#include "FormationTypes.h"
class GameSettings
{
public:
	GameSettings(void);
	~GameSettings(void);

	static float checkersMass;
	static float checkersRadius;
	static float checkersFriction;
	static float checkersRestitution;
	
	static Player firstTurn;
	static CheckerColor userColor;
};

