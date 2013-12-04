#include "ScoreValues.h"
#include "GameSettings.h"

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

void ScoreValues::CountScores(std::list<Checker*> *checkerList, Player player){
	int startScore = 10;
	int index = 1;
	for(std::list<Checker*>::iterator it = checkerList->begin(); it != checkerList->end(); it++){
		if (player == Player::ai){
			scoresAI += startScore;
			(*it)->RemoveByScore(startScore, index * SCORE_ANIMATION_DELAY, SCORE_COLOR_CCC3_AI);
		}
		else if (player == Player::user){
			scoresUser += startScore;
			(*it)->RemoveByScore(startScore, index * SCORE_ANIMATION_DELAY, SCORE_COLOR_CCC3_USER);
		}		
		
		startScore *= 1.5f;
		index++;
	}
}
