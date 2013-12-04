#include "FormationManager.h"
#include "GameSettings.h"

FormationManager::FormationManager(BoardLayer *boardLayer)
{
	this->boardLayer = boardLayer;

	static const int infantryFormation[GameSettings::BOARD_SIZE][2] =   {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int menInBlueFormation[GameSettings::BOARD_SIZE][2] =  {{1,1},{2,2},{3,1},{4,2},{5,1},{6,2},{7,1},{8,2}};
	static const int marinesFormation[GameSettings::BOARD_SIZE][2] =    {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int tanksFormation[GameSettings::BOARD_SIZE][2] =      {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int heavyTanksFormation[GameSettings::BOARD_SIZE][2] = {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int artilleryFormation[GameSettings::BOARD_SIZE][2] =  {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int cavalryFormation[GameSettings::BOARD_SIZE][2] =    {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int bunkerFormation[GameSettings::BOARD_SIZE][2] =     {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int towerFormation[GameSettings::BOARD_SIZE][2] =      {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int fortressFormation[GameSettings::BOARD_SIZE][2] =   {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};
	static const int katyushaFormation[GameSettings::BOARD_SIZE][2] =   {{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{7,1},{8,1}};

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

	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::infantry,		4) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::menInBlue,	4) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::marines,		4) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::tanks,		3) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::heavyTanks,	3) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::artillery,	3) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::cavalry,		3) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::bunker,		2) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::tower,		2) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::fortress,		2) );
	formationWinsMap.insert ( std::pair<FormationTypes, int> (FormationTypes::katyusha,		2) );
}


FormationManager::~FormationManager(void)
{
}

void FormationManager::AddChecker(cocos2d::CCPoint point, std::list<Checker*> *list, CheckerColor color){
	float newRadius = boardLayer->GetSquareWidth() / 2.0f * 0.8f / PTM_RATIO;
 	Checker *checker = new Checker(boardLayer->getBox2World(), point, color, GameSettings::checkersMass, newRadius, GameSettings::checkersFriction, GameSettings::checkersRestitution);
	list->push_front(checker);
}

FormationTypes FormationManager::GetNextFormation(int wins){
    int index = 0;
	while(formationWinsMap[(FormationTypes)index] <= wins){
		wins -= formationWinsMap[(FormationTypes)index];
		index++;
	}
	
	return (FormationTypes)index;
}

std::list<Checker*> * FormationManager::LoadFormation(Player player, FormationTypes currFormation, int wins) {
	std::list<Checker*> *checkerList = new std::list<Checker*>();
	CheckerColor color = GameSettings::userColor;

	if (player == Player::ai){
		color = GameSettings::userColor == CheckerColor::black ? CheckerColor::white : CheckerColor::black;	
	}

	//get line
	int currentLine = 0;	
	int index = 0;
	while(formationWinsMap[(FormationTypes)index] <= wins){
		wins -= formationWinsMap[(FormationTypes)index];
		index++;
	}
	currentLine = wins;

	for(int i = 0; i < GameSettings::BOARD_SIZE; i++){
		const int posX = formationMap[currFormation][i][0];
		int posY = formationMap[currFormation][i][1] + currentLine;

		if (player == Player::ai){
			posY = GameSettings::BOARD_SIZE + 1 - posY;
		}

		AddChecker(cocos2d::CCPoint(boardLayer->GetCoordXForPosX(posX), boardLayer->GetCoordYForPosY(posY)), checkerList, color);
	}	

	return checkerList;
}

