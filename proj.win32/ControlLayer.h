#pragma once
#include "cocos2d.h"
#include "Filenames.h"
#include "Checker.h"

class ControlLayer:
	public cocos2d::CCLayer
{	
	std::list<Checker*> *checkerList;

	cocos2d::CCSprite *arrowSprite;
	cocos2d::CCSprite *movingSprite;

	void AddDebugString(char *str, int pos);	
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	CREATE_FUNC(ControlLayer);

	void AddCheckerList(std::list<Checker*> *checkerList);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

