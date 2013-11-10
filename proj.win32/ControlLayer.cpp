#include "ControlLayer.h"
#include "ScoreValues.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool ControlLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////    
		CC_BREAK_IF(! CCLayer::init());

		this->setTouchEnabled(true);
		this->movingSprite = NULL;

		arrowSprite = CCSprite::create(IMAGE_SCENE_CONTROL_ARROW);

		int screenWidth = CCDirector::sharedDirector()->getWinSize().width;
		int screenHeight = CCDirector::sharedDirector()->getWinSize().height;

		arrowSprite->setPosition(ccp(0,0));		

		this->addChild(arrowSprite);						

        bRet = true;
    } while (0);

    return bRet;
}

void ControlLayer::AddCheckerList(std::list<Checker*> *checkerList){
	this->checkerList = checkerList;
}

void ControlLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (ScoreValues::turn == Player::user){
		CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
		CCPoint location = touch->getLocation();

		for(std::list<Checker*>::iterator it = checkerList->begin(); it != checkerList->end(); it++){
			if ((*it)->GetSprite()->boundingBox().containsPoint(location)){	
				movingSprite = (*it)->GetSprite();
			}
		}
	}
}

void ControlLayer::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint touchLocation = touch->getLocation();

	if (movingSprite != NULL){
		const float newY = touchLocation.y;
		const float newX = touchLocation.x;
		const float diffX = movingSprite->getPositionX() - newX;
		const float diffY = movingSprite->getPositionY() - newY;

		arrowSprite->setPosition(ccp(movingSprite->getPositionX() + diffX, movingSprite->getPositionY() + diffY));
	} 
}

void ControlLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint touchLocation = touch->getLocation();
	float screenWidth = CCDirector::sharedDirector()->getWinSize().width;
	
	if (movingSprite != NULL){
		float angle = cocos2d::ccpToAngle(ccp(movingSprite->getPositionX() - touchLocation.x, movingSprite->getPositionY() - touchLocation.y));
		float force = cocos2d::ccpDistance(movingSprite->getPosition(), touchLocation);
		((Checker *)(movingSprite->getUserData()))->ApplyForce(force, angle);

		ScoreValues::turn = Player::none;
		ScoreValues::shots++;
	}

	movingSprite = NULL;	
}

void ControlLayer::AddDebugString(char *str, int pos){
	this->removeChildByTag(pos);

	CCSprite *sprite = CCLabelTTF::create(str, "Arial", 20);
	sprite->setPosition(ccp(100 , pos));
	sprite->setTag(pos);
	this->addChild(sprite, 100);
}
