#include "FormationManager.h"
#include "GameSettings.h"

FormationManager::FormationManager(b2World *world)
{
	this->world = world;
}


FormationManager::~FormationManager(void)
{
}

void FormationManager::AddChecker(cocos2d::CCPoint point, std::list<Checker*> *list, CheckerColor color){
	Checker *checker = new Checker(this->world, point, color, GameSettings::checkersMass, GameSettings::checkersRadius, GameSettings::checkersFriction, GameSettings::checkersRestitution);
	list->push_front(checker);
}

std::list<Checker*> * FormationManager::LoadFormation(Player player, FormationTypes type) {
	std::list<Checker*> *checkerList = NULL;
	if (player == Player::user){
		checkerList = new std::list<Checker*>();
		AddChecker(cocos2d::CCPoint(100, 50), checkerList, GameSettings::userColor);
		AddChecker(cocos2d::CCPoint(230, 50), checkerList, GameSettings::userColor);
		AddChecker(cocos2d::CCPoint(350, 50), checkerList, GameSettings::userColor);
		AddChecker(cocos2d::CCPoint(470, 50), checkerList, GameSettings::userColor);
		AddChecker(cocos2d::CCPoint(590, 50), checkerList, GameSettings::userColor);
		AddChecker(cocos2d::CCPoint(610, 50), checkerList, GameSettings::userColor);		
	}
	else if (player == Player::ai){
		checkerList = new std::list<Checker*>();
		AddChecker(cocos2d::CCPoint(100, 250),checkerList, GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black);
		AddChecker(cocos2d::CCPoint(230, 250),checkerList, GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black);
		AddChecker(cocos2d::CCPoint(350, 250),checkerList, GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black);
		AddChecker(cocos2d::CCPoint(470, 250),checkerList, GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black);
		AddChecker(cocos2d::CCPoint(590, 250),checkerList, GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black);
		AddChecker(cocos2d::CCPoint(610, 250),checkerList, GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black);
	}

	return checkerList;
}

