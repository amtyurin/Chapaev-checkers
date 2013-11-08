#include "GameSettings.h"


float GameSettings::checkersMass = 1.5f;
float GameSettings::checkersRadius = 1.0f;
float GameSettings::checkersFriction = 1.0f;
float GameSettings::checkersRestitution = 0.5f;
Player GameSettings::firstTurn = Player::user;
CheckerColor GameSettings::userColor = CheckerColor::white;

GameSettings::GameSettings(void)
{
}

GameSettings::~GameSettings(void)
{
}
