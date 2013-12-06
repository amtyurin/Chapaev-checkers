#pragma once
#include "cocos2d.h"
#include "Filenames.h"

class ScoresLayer:
	public cocos2d::CCLayer
{
	cocos2d::CCLayer *animationLayer;
	cocos2d::CCLayer *backGround;

	void DisplayText(char *text, cocos2d::ccColor3B color, cocos2d::CCPoint ccp, int size);
	void DisplayText(int number, cocos2d::ccColor3B color, cocos2d::CCPoint ccp, int size);

	int screenHeight;
	int screenWidth;

	int fontSize;
	static const int leftScoreBorder = 20;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	CREATE_FUNC(ScoresLayer);

	void DisplayScores();
};

