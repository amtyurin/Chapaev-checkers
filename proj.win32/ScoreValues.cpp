#include "ScoreValues.h"

Player ScoreValues::turn = Player::none;
int ScoreValues::winsUser = 0;		
int ScoreValues::scoresUser = 0;
int ScoreValues::shotsUser = 0;
FormationTypes ScoreValues::currentformationUser = FormationTypes::infantry;

int ScoreValues::winsAI = 0;		
int ScoreValues::scoresAI = 0;
int ScoreValues::shotsAI = 0;
FormationTypes ScoreValues::currentformationAI = FormationTypes::infantry;

ScoreValues::ScoreValues(void)
{	
}


ScoreValues::~ScoreValues(void)
{
}
