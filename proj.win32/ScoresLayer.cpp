#include "ScoresLayer.h"
#include "GameSettings.h"
#include "ScoreValues.h"

using namespace cocos2d;


// on "init" you need to initialize your instance
bool ScoresLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////    
		CC_BREAK_IF(! CCLayer::init());

		screenHeight = CCDirector::sharedDirector()->getWinSize().height;
		screenWidth = CCDirector::sharedDirector()->getWinSize().width;

		fontSize = screenHeight / 20;
		DisplayText("AI scores:", SCORE_COLOR_CCC3_AI, ccp(leftScoreBorder, screenHeight - leftScoreBorder), fontSize);
		DisplayText("Your scores:", SCORE_COLOR_CCC3_USER, ccp(leftScoreBorder, screenHeight / 2 - leftScoreBorder), fontSize);
		
        bRet = true;
    } while (0);

    return bRet;
}

void ScoresLayer::DisplayScores(){	
	int x = leftScoreBorder;
	int y = screenHeight - leftScoreBorder - fontSize;
	DisplayText("Shots:", SCORE_COLOR_CCC3_AI, ccp(x, y), fontSize);	
	DisplayText("Shots:", SCORE_COLOR_CCC3_USER, ccp(x, y - screenHeight / 2), fontSize);
	x = x + fontSize * 4;
	DisplayText(ScoreValues::shotsAI, SCORE_COLOR_CCC3_AI, ccp(x, y), fontSize);
	DisplayText(ScoreValues::shotsUser, SCORE_COLOR_CCC3_USER, ccp(x, y - screenHeight / 2), fontSize);
	x = x - fontSize * 4;

	y = y - fontSize;
	DisplayText("Wins:", SCORE_COLOR_CCC3_AI, ccp(x, y), fontSize);
	DisplayText("Wins:", SCORE_COLOR_CCC3_USER, ccp(x,  y - screenHeight / 2), fontSize);
	x = x + fontSize * 4;
	DisplayText(ScoreValues::winsAI, SCORE_COLOR_CCC3_AI, ccp(x, y), fontSize);
	DisplayText(ScoreValues::winsUser, SCORE_COLOR_CCC3_USER, ccp(x,  y - screenHeight / 2), fontSize);
	x = x - fontSize * 4;

	y = y - fontSize;
	DisplayText("Survived:", SCORE_COLOR_CCC3_AI, ccp(x, y), fontSize);
	DisplayText("Survived:", SCORE_COLOR_CCC3_USER, ccp(x,  y - screenHeight / 2), fontSize);
	x = x + fontSize * 5;
	DisplayText(ScoreValues::survivedAI, SCORE_COLOR_CCC3_AI, ccp(x, y), fontSize);
	DisplayText(ScoreValues::survivedUser, SCORE_COLOR_CCC3_USER, ccp(x,  y - screenHeight / 2), fontSize);
	x = x - fontSize * 5;

	y = y - fontSize;
	DisplayText("Scores:", SCORE_COLOR_CCC3_AI, ccp(x, y), fontSize);
	DisplayText("Scores:", SCORE_COLOR_CCC3_USER, ccp(x,  y - screenHeight / 2), fontSize);
	x = x + fontSize * 5;
	DisplayText(ScoreValues::scoresAI, SCORE_COLOR_CCC3_AI, ccp(x, y), fontSize);
	DisplayText(ScoreValues::scoresUser, SCORE_COLOR_CCC3_USER, ccp(x,  y - screenHeight / 2), fontSize);
}

void ScoresLayer::DisplayText(char *text, cocos2d::ccColor3B color, cocos2d::CCPoint ccp, int size)
{
	CCLabelTTF* pLabel = CCLabelTTF::create(text, "Arial", size * 2);	
    pLabel->setColor(color);
	pLabel->setScale(0.5);
	pLabel->setPosition(ccp(ccp.x + pLabel->getContentSize().width * pLabel->getScaleX() / 2, ccp.y));

	int tag = ccp.x + ccp.y * 10000;
	this->removeChildByTag(tag);
	this->addChild(pLabel, 10, tag);
}

void ScoresLayer::DisplayText(int number, cocos2d::ccColor3B color, cocos2d::CCPoint ccp, int size)
{
	char text[20];
	itoa(number, text, 10);
	DisplayText(text, color, ccp, size);
}



