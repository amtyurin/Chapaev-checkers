#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "FormationTypes.h"
#include "Checker.h"

class FormationManager
{
	b2World *world;
	
	void AddChecker(cocos2d::CCPoint point, std::list<Checker*> *list, CheckerColor color);
public:
	FormationManager(b2World *world);
	~FormationManager(void);

	std::list<Checker*> *LoadFormation(Player player, FormationTypes type);
};

