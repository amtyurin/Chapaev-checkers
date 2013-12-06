#include "CheckerScene.h"

#include "Checker.h"
#include "GameSettings.h"
#include "ScoreValues.h"

using namespace cocos2d;

CCScene* CheckerScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        CheckerScene *layer = CheckerScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CheckerScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(CheckerScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to CheckerScene layer as a child layer.
        this->addChild(pMenu, 1);        

		scoresLayer = ScoresLayer::create();
		this->addChild(scoresLayer, 2);		

		boardLayer = BoardLayer::create();
		this->addChild(boardLayer, 3);

		controlLayer = ControlLayer::create();
		this->addChild(controlLayer, 4);		
		
		// initialize checkers on the board
		checkerListOutOfBoard = new std::list<Checker *>();
		formationManager = new FormationManager(boardLayer);		
		checkerListUser = formationManager->LoadFormation(Player::user, ScoreValues::currentformationUser, ScoreValues::winsUser);
		checkerListAI = formationManager->LoadFormation(Player::ai, ScoreValues::currentformationAI, ScoreValues::winsAI);
		for(std::list<Checker*>::iterator it = checkerListUser->begin(); it != checkerListUser->end(); it++){
			this->addChild((*it)->GetSprite(), 1000);
		}
		for(std::list<Checker*>::iterator it = checkerListAI->begin(); it != checkerListAI->end(); it++){
			this->addChild((*it)->GetSprite(), 1000);
		}
		
		// add checkers to user and ai controls
		controlLayer->AddCheckerList(checkerListUser);
		ai = new AIControl(checkerListUser, checkerListAI);

		scoresLayer->DisplayScores();

		ScoreValues::AnyMovementAroundBoard = false;

		this->schedule( schedule_selector(CheckerScene::tick), SCHEDULER_TIMER);

        bRet = true;
    } while (0);

    return bRet;
}

void CheckerScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void CheckerScene::CreateScene(CCObject* sender)
{
    CCScene* anScene = CheckerScene::scene(); 
	CCDirector::sharedDirector()->replaceScene(anScene);
}

bool CheckerScene::ProcessCheckerList(float dt, std::list<Checker*> *checkerList){
	bool anyMovement = false;
	for(std::list<Checker*>::iterator it = checkerList->begin(); it != checkerList->end(); ){
		(*it)->tick(dt);

		if (!anyMovement){
			if ((*it)->GetLinearVelocity() != 0.0f || (*it)->GetAngularVelocity() != 0.0f){
				anyMovement = true;
			}
		}

	    //  remove checkers out of board
		if (boardLayer->IsOutOfBorder(ccp((*it)->GetPositionX(), (*it)->GetPositionY()))){
			checkerListOutOfBoard->push_front(*it);
			(*it)->RemoveFromBoard();			
			checkerList->erase(it++);				
		}
		else{
			it++;
		}
	}

	return anyMovement;
}

bool CheckerScene::CheckWinCondition(){
	// 0 - nobody
	// 1 - user
	// 2 - ai
	// 3 - user && ai
	int whoWonFlag = 0;
	if(checkerListUser->empty() && checkerListAI->empty()){
		whoWonFlag = 3;
		//animation
	}
	else if (checkerListUser->empty()){
		whoWonFlag = 2;
		//animation
	}
	else if (checkerListAI->empty()){
		whoWonFlag = 1;
		//animation
	}

	if (whoWonFlag){
		this->unschedule( schedule_selector(CheckerScene::tick));
	}	

	float delay = 0.0f;
	switch(whoWonFlag){
		case 3: // user && ai
		case 1: // user
			ScoreValues::winsUser++;
			ScoreValues::currentformationUser = formationManager->GetNextFormation(ScoreValues::winsUser);
			if (whoWonFlag == 1){
				ScoreValues::CountScores(checkerListUser, Player::user);
				delay = checkerListUser->size();
				ScoreValues::turn = Player::user;
				break;
			}
		case 2: // ai
			ScoreValues::winsAI++;
			ScoreValues::currentformationAI = formationManager->GetNextFormation(ScoreValues::winsAI);
			ScoreValues::CountScores(checkerListAI, Player::ai);
			delay = checkerListAI->size();
			ScoreValues::turn = Player::ai;
			break;
		default: // nobody
			break;
	}
		
	if (whoWonFlag){			
		// go to the next level
		delay = delay * SCORE_ANIMATION_DELAY + SCORE_ANIMATION_DELAY * 4;
		this->schedule( schedule_selector(CheckerScene::NextScene), delay + SCORE_ANIMATION_DELAY);
		scoresLayer->DisplayScores();
		return true;
	}
	return false;
}

void CheckerScene::NextScene(float dt){
	this->unschedule(schedule_selector(CheckerScene::NextScene));
	CreateScene(this);
}

void CheckerScene::tick(float dt){
	bool anyMovement = ProcessCheckerList(dt, checkerListUser) | 
					   ProcessCheckerList(dt, checkerListAI);

	//check if out of board checkers are moving 
	for(std::list<Checker*>::iterator it = checkerListOutOfBoard->begin(); it != checkerListOutOfBoard->end(); ){
		if ((*it)->GetLinearVelocity() != 0.0f){			
			anyMovement = true;
			it++;
		}
		else{
			checkerListOutOfBoard->erase(it++);
		}
	}
	
	ScoreValues::AnyMovementAroundBoard = anyMovement;
	if (!anyMovement){
		if (!CheckWinCondition()){
			if (ScoreValues::turn == Player::ai){
				// to prevent user move
				ScoreValues::AnyMovementAroundBoard = true;
				
				ScoreValues::turn = Player::user;
				ScoreValues::shotsAI++;
				scoresLayer->DisplayScores();
				ai->MakeTurn();			
			}
		}
	}
}
