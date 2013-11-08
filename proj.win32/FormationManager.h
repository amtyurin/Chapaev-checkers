#pragma once
#include "cocos2d.h"
#include "FormationTypes.h"
#include "Checker.h"

class FormationManager
{
	void FormationManager::CreateChecker(cocos2d::CCPoint point);
public:
	FormationManager(void);
	~FormationManager(void);

	std::list<Checker*> *LoadFormation(Player player, FormationTypes type);
};

