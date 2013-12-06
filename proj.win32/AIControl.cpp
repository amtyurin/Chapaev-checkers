#include "AIControl.h"
#include "GameSettings.h"

using namespace cocos2d;

AIControl::AIControl(std::list<Checker*> *user, std::list<Checker*> *ai)
{
	this->checkerListAI = ai;
	this->checkerListUser = user;
}


AIControl::~AIControl(void)
{
}

void AIControl::MakeTurn(){
	//find min distance
	int minDistance = 1000000;
	Checker *checkerToKick = NULL; 
	Checker *checkerToWhere = NULL; 
	for(std::list<Checker*>::iterator itUser = checkerListUser->begin(); itUser != checkerListUser->end(); itUser++){
		for(std::list<Checker*>::iterator itAI = checkerListAI->begin(); itAI != checkerListAI->end(); itAI++){
			int distance = cocos2d::ccpDistance(ccp((*itUser)->GetPositionX(),(*itUser)->GetPositionY()),
				ccp((*itAI)->GetPositionX(),(*itAI)->GetPositionY()));
			if (distance < minDistance){
				checkerToKick = *itAI;
				checkerToWhere = *itUser;
				minDistance = distance;
			}
		}
	}

	CCPoint startPoint;
	CCPoint stopPoint;
	switch (GameSettings::difficulty){
		case Difficulty::Easy:
			CCPoint startPoint = checkerToKick->GetSprite()->getPosition();
		    CCPoint stopPoint = checkerToWhere->GetSprite()->getPosition();
			break;
		case Difficulty::Medium:
			break;
		case Difficulty::Hard:
			break;
	}

	if(checkerToKick){
		float angle = 0; 		
		angle = ccpToAngle(ccp(stopPoint.x - startPoint.x, stopPoint.y - startPoint.y));

		checkerToKick->ApplyForce(rand() % 50 + 50, angle);
	}
	else{
		checkerListAI->front()->ApplyForce(rand() % 50 + 50, (rand() % 60) / 10);
	}
}
