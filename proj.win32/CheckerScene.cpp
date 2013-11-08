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
		formationManager = new FormationManager(boardLayer->getBox2World());		
		checkerListUser = formationManager->LoadFormation(Player::user, (FormationTypes)1);
		checkerListAI = formationManager->LoadFormation(Player::ai, (FormationTypes)1);
		for(std::list<Checker*>::iterator it = checkerListUser->begin(); it != checkerListUser->end(); it++){
			this->addChild((*it)->GetSprite(), 1000);
		}
		for(std::list<Checker*>::iterator it = checkerListAI->begin(); it != checkerListAI->end(); it++){
			this->addChild((*it)->GetSprite(), 1000);
		}
		
		controlLayer->AddCheckerList(checkerListUser);
		ai = new AIControl(checkerListUser, checkerListAI);

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


void CheckerScene::tick(float dt){
	bool anyMovement = false;
	for(std::list<Checker*>::iterator it = checkerListUser->begin(); it != checkerListUser->end(); it++){
		(it._Ptr)->_Myval->tick(dt);

		if (!anyMovement){
			Checker *checker = (it._Ptr)->_Myval;
			// check for ai turn
			if (checker->GetLinearVelocity() == 0.0f && checker->GetAngularVelocity() == 0){
				
			}
			else {
				anyMovement = true;
			}
		}
	}
	for(std::list<Checker*>::iterator it = checkerListAI->begin(); it != checkerListAI->end(); it++){
		(it._Ptr)->_Myval->tick(dt);

		if (!anyMovement){
			Checker *checker = (it._Ptr)->_Myval;
			// check for ai turn
			if (checker->GetLinearVelocity() == 0.0f && checker->GetAngularVelocity() == 0){
				
			}
			else {
				anyMovement = true;
			}
		}
	}
	
	if (!anyMovement){
		// remove checkers out of board
		for(std::list<Checker*>::iterator it = checkerListUser->begin(); it != checkerListUser->end(); it++){
		}
		for(std::list<Checker*>::iterator it = checkerListAI->begin(); it != checkerListAI->end(); it++){
		}

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
}
