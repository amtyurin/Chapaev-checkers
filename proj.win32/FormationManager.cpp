#include "FormationManager.h"
#include "GameSettings.h"

FormationManager::FormationManager(BoardLayer *boardLayer)
{
	this->boardLayer = boardLayer;

	static const int infantryFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int menInBlueFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int marinesFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int tanksFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int heavyTanksFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int artilleryFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int cavalryFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int bunkerFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int towerFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int fortressFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int katyushaFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};

	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::infantry, infantryFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::menInBlue, menInBlueFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::marines, marinesFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::tanks, tanksFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::heavyTanks, heavyTanksFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::artillery, artilleryFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::cavalry, cavalryFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::bunker, bunkerFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::tower, towerFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::fortress, fortressFormation) );
	formationMap.insert ( std::pair<FormationTypes, const int (*)[2]> (FormationTypes::katyusha, katyushaFormation) );
}


FormationManager::~FormationManager(void)
{
}

void FormationManager::AddChecker(cocos2d::CCPoint point, std::list<Checker*> *list, CheckerColor color){
	float newRadius = boardLayer->GetSquareWidth() / 2.0f * 0.8f / PTM_RATIO;
 	Checker *checker = new Checker(boardLayer->getBox2World(), point, color, GameSettings::checkersMass, newRadius, GameSettings::checkersFriction, GameSettings::checkersRestitution);
	list->push_front(checker);
}

std::list<Checker*> * FormationManager::LoadFormation(Player player, FormationTypes type) {
	std::list<Checker*> *checkerList = new std::list<Checker*>();
	CheckerColor color = GameSettings::userColor;

	if (player == Player::ai){
		color = GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black;	
	}

	for(int i = 0; i < GameSettings::BOARD_SIZE; i++){
		const int posX = formationMap[type][i][0];
		int posY = formationMap[type][i][1];

		if (player == Player::ai){
			posY = GameSettings::BOARD_SIZE + 1 - posY;
		}

		AddChecker(cocos2d::CCPoint(boardLayer->GetCoordXForPosX(posX), boardLayer->GetCoordYForPosY(posY)), checkerList, color);
	}	

	return checkerList;
}

