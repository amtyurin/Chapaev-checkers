#include "AIControl.h"


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
			}
		}
	}

	if(checkerToKick){
		float angle = 0; // TODO
		checkerToKick->ApplyForce(rand() % 200 + 50, angle);
	}
	else{
		checkerListAI->front()->ApplyForce(rand() % 200, (rand() % 60) / 10);
	}
}
