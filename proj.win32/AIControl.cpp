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
	// TODO
	checkerListAI->front()->ApplyForce(rand() % 100, rand() % 10);
}
