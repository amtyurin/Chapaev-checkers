#include "GameSettings.h"


float GameSettings::checkersMass = 1.3f;
float GameSettings::checkersFriction = 1.0f;
float GameSettings::checkersRestitution = 0.8f;
CheckerColor GameSettings::userColor = CheckerColor::white;
int GameSettings::maxForce = 100;
Difficulty GameSettings::difficulty = Difficulty::Easy;

GameSettings::GameSettings(void)
{
}

GameSettings::~GameSettings(void)
{
}
