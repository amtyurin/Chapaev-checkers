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
		checkerListUser = formationManager->LoadFormation(Player::user, (FormationTypes)1);
		checkerListAI = formationManager->LoadFormation(Player::ai, (FormationTypes)1);
		for(std::list<Checker*>::iterator it = checkerListUser->begin(); it != checkerListUser->end(); it++){
			this->addChild((*it)->GetSprite(), 1000);
		}
		for(std::list<Checker*>::iterator it = checkerListAI->begin(); it != checkerListAI->end(); it++){
			this->addChild((*it)->GetSprite(), 1000);
		}
		
		// add checkers to user and ai controls
		controlLayer->AddCheckerList(checkerListUser);
		ai = new AIControl(checkerListUser, checkerListAI);

		// define first turn
		ScoreValues::turn = GameSettings::firstTurn;

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
			// check for ai turn
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

void CheckerScene::tick(float dt){
	bool anyMovement = ProcessCheckerList(dt, checkerListUser) | 
					   ProcessCheckerList(dt, checkerListAI);

	//wait until out of board checkers are moving 
	for(std::list<Checker*>::iterator it = checkerListOutOfBoard->begin(); it != checkerListOutOfBoard->end(); ){
		if ((*it)->GetLinearVelocity() != 0.0f){			
			anyMovement = true;
			it++;
		}
		else{
			checkerListOutOfBoard->erase(it++);
		}
	}
	
	if (!anyMovement){
		if (ScoreValues::turn == Player::none){
			if (GameSettings::firstTurn == Player::ai || ScoreValues::shots % 2 == 1){
				ScoreValues::turn = Player::ai;
			}
			else {
				ScoreValues::turn = Player::user;
			}
		}
		else if (ScoreValues::turn == Player::ai){
			ScoreValues::turn = Player::none;			
			ai->MakeTurn();		
			ScoreValues::shots++;
		}
	}
	else {
		Player whoWon = Player::none;
		bool wonFlag = false;

		if(checkerListUser->empty() && checkerListAI->empty()){
			wonFlag = true;
		}
		else if (checkerListUser->empty()){
			wonFlag = true;
			whoWon = Player::ai;
		}
		else if (checkerListAI->empty()){
			wonFlag = true;
			whoWon = Player::user;
		}
		
		if (wonFlag){
			this->unschedule( schedule_selector(CheckerScene::tick));

			//animation

			// go to the next level
			CreateScene(this);
		}
	}
}
