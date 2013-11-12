#pragma once
#include "FormationTypes.h"
class GameSettings
{
public:
	GameSettings(void);
	~GameSettings(void);

	static float checkersMass;
	static float checkersFriction;
	static float checkersRestitution;
	static int maxForce;

	static CheckerColor userColor;	

	static const int BOARD_SIZE = 8;
};

