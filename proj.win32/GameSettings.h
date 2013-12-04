#pragma once
#include "FormationTypes.h"

#define SCORE_ANIMATION_DELAY 0.7f

#define SCORE_COLOR_CCC3_USER cocos2d::ccc3(255,127,0)
#define SCORE_COLOR_CCC3_AI cocos2d::ccc3(255,48,48)

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

