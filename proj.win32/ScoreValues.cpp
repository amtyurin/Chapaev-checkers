#include "ScoreValues.h"

Player ScoreValues::turn = Player::none;
int ScoreValues::shots = 0;

ScoreValues::ScoreValues(void)
{
	currentformation = (FormationTypes)1;
	shots = 0;
	scores = 0;
	wins = 0;		
}


ScoreValues::~ScoreValues(void)
{
}
