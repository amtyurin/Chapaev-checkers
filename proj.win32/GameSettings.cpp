#include "GameSettings.h"


float GameSettings::checkersMass = 1.3f;
float GameSettings::checkersFriction = 1.0f;
float GameSettings::checkersRestitution = 0.7f;
CheckerColor GameSettings::userColor = CheckerColor::white;
int GameSettings::maxForce = 150;

GameSettings::GameSettings(void)
{
}

GameSettings::~GameSettings(void)
{
}
