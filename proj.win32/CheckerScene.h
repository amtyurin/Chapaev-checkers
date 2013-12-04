#ifndef __CHECKER_SCENE_H__
#define __CHECKER_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "Filenames.h"
#include "ScoresLayer.h"
#include "BoardLayer.h"
#include "ControlLayer.h"
#include "AIControl.h"
#include "FormationManager.h"
#include "ScoreValues.h"

class CheckerScene :
	public cocos2d::CCLayer
{
private:
	cocos2d::CCLayer *menuLayer;
		
	ScoresLayer *scoresLayer;	
	ControlLayer *controlLayer;
	BoardLayer *boardLayer;	

	std::list<Checker*> *checkerListUser;
	std::list<Checker*> *checkerListAI;
	std::list<Checker*> *checkerListOutOfBoard;

	AIControl *ai;

	FormationManager *formationManager;

	void gameLogic(float dt);

	void AddCheckerUser(cocos2d::CCPoint point);
	void AddCheckerAI(cocos2d::CCPoint point);

	bool ProcessCheckerList(float dt, std::list<Checker*> *checkerList);
	bool CheckWinCondition();

public:
	CheckerScene(void){};
	~CheckerScene(void){};

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  	

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(CheckerScene);
	
	void CreateScene(CCObject *sender);
	
	void tick(float dt);
	
	void NextScene(float dt);
};

#endif // __CHECKER_SCENE_H__
