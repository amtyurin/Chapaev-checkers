#pragma once
#include "cocos2d.h"
#include "Filenames.h"

class ScoresLayer:
	public cocos2d::CCLayer
{
	cocos2d::CCLayer *animationLayer;
	cocos2d::CCLayer *backGround;

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	CREATE_FUNC(ScoresLayer);

	void DisplayScores();
};

