#include "BoardLayer.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool BoardLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////    
		CC_BREAK_IF(! CCLayer::init());
		
        ////////////BOX2d world init
		b2Vec2 gravity;
		gravity.Set(0.0f, 0.0f);
		// create a world object, which will hold and simulate the rigid bodies.
		this->box2world = new b2World(gravity);	
		
		this->addChild(B2DebugDrawLayer::create(this->box2world, PTM_RATIO), 900);

		this->schedule( schedule_selector(BoardLayer::gameLogic), SCHEDULER_TIMER );
		
        bRet = true;
    } while (0);

    return bRet;
}

void BoardLayer::gameLogic(float dt){
	const int velocityIterations = 10;
	const int positionIterations = 8;

	this->box2world->Step(dt, velocityIterations, positionIterations);
}

b2World *BoardLayer::getBox2World() const{
	return this->box2world;
}
