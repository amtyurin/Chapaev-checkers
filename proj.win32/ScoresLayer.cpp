#include "ScoresLayer.h"

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
		
        bRet = true;
    } while (0);

    return bRet;
}

void ScoresLayer::DisplayScores(){
	// TODO
}


