#include "FormationManager.h"


FormationManager::FormationManager(void)
{
}


FormationManager::~FormationManager(void)
{
}

std::list<Checker*> * FormationManager::LoadFormation(Player player, FormationTypes type){
	if (player == Player::user){
		std::list<Checker*> *checkerListUser = new std::list<Checker*>();
		AddCheckerUser(cocos2d::CCPoint(100, 50));
		AddCheckerUser(cocos2d::CCPoint(230, 50));
		AddCheckerUser(cocos2d::CCPoint(350, 50));
		AddCheckerUser(cocos2d::CCPoint(470, 50));
		AddCheckerUser(cocos2d::CCPoint(590, 50));
		AddCheckerUser(cocos2d::CCPoint(610, 50));
	}
	else if (player == Player::ai){
		AddCheckerAI(cocos2d::CCPoint(100, 250));
		AddCheckerAI(cocos2d::CCPoint(230, 250));
		AddCheckerAI(cocos2d::CCPoint(350, 250));
		AddCheckerAI(cocos2d::CCPoint(470, 250));
		AddCheckerAI(cocos2d::CCPoint(590, 250));
		AddCheckerAI(cocos2d::CCPoint(610, 250));
	}
}

void FormationManager::AddCheckerUser(cocos2d::CCPoint point){
	Checker *checker = new Checker(boardLayer->getBox2World(), this, point, GameSettings::userColor, GameSettings::checkersMass, GameSettings::checkersRadius, GameSettings::checkersFriction, GameSettings::checkersRestitution);
	checkerListUser.push_front(checker);
}

void FormationManager::AddCheckerAI(cocos2d::CCPoint point){
	Checker *checker = new Checker(boardLayer->getBox2World(), this, point, GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black, GameSettings::checkersMass, GameSettings::checkersRadius, GameSettings::checkersFriction, GameSettings::checkersRestitution);
	checkerListAI.push_front(checker);
}
