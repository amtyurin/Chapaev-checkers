#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "FormationTypes.h"
#include "Checker.h"
#include "GameSettings.h"
#include "BoardLayer.h"

class FormationManager
{
	BoardLayer *boardLayer;

	std::map<FormationTypes, const int (*)[2]> formationMap;
	std::map<FormationTypes, int> formationWinsMap;
	
	void AddChecker(cocos2d::CCPoint point, std::list<Checker*> *list, CheckerColor color);
public:
	FormationManager(BoardLayer *boardLayer);
	~FormationManager(void);

	std::list<Checker*> *LoadFormation(Player player, FormationTypes currFormation, int wins);
	FormationTypes GetNextFormation(FormationTypes currFormation, int wins);
};

