#include "BoardLayer.h"
#include "GameSettings.h"

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

		const int screenHeight = CCDirector::sharedDirector()->getWinSize().height;
		const int screenWidth = CCDirector::sharedDirector()->getWinSize().width;		

		//we suppose that width is always larger than height
		boardWidth = min (3.0f / 4.0f * screenWidth, screenHeight);
		boardWidth = boardWidth - 1.5f * boardWidth / (GameSettings::BOARD_SIZE);
		boardWidth = boardWidth + boardWidth % GameSettings::BOARD_SIZE;
		
		boardCenterY = screenHeight / 2;
		boardCenterX = screenWidth - boardCenterY;
		squareWidth = boardWidth / GameSettings::BOARD_SIZE;

		DrawBoard();
		
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

void BoardLayer::DrawBoard(){
	int cellNum = 1;
	for(int i = 0; i < GameSettings::BOARD_SIZE; i++){
		for(int j = 0; j < GameSettings::BOARD_SIZE; j++){
			CCSprite *sprite = NULL;
			if (cellNum % 2 == 1){
				sprite = CCSprite::create(IMAGE_BOARD_BLACK_SQUARE);
			}
			else {
				sprite = CCSprite::create(IMAGE_BOARD_WHITE_SQUARE);
			}
			sprite->setScale(squareWidth / sprite->getContentSize().width);
			sprite->setPositionX(GetCoordXForPosX(i + 1));
			sprite->setPositionY(GetCoordYForPosY(j + 1));
			this->addChild(sprite, 1);

			cellNum++;
		}
		cellNum++;
	}
}

int BoardLayer::GetCoordXForPosX(int posX){
	const int leftBoardPosX = boardCenterX - boardWidth / 2;
	return (leftBoardPosX + squareWidth / 2 + squareWidth * (posX - 1));
}

int BoardLayer::GetCoordYForPosY(int posY){
	const int leftBoardPosY = boardCenterY - boardWidth / 2;
	return (leftBoardPosY + squareWidth / 2 + squareWidth * (posY - 1));
}

bool BoardLayer::IsOutOfBorder(cocos2d::CCPoint point) const{
	const int leftBoardPosX = boardCenterX - boardWidth / 2;
	const int leftBoardPosY = boardCenterY - boardWidth / 2;

	if (point.x > leftBoardPosX + boardWidth)
		return true;
	if(point.x < leftBoardPosX)
		return true;
	if (point.y > leftBoardPosY + boardWidth)
		return true;
	if(point.y < leftBoardPosY)
		return true;
	return false;
}

int BoardLayer::GetSquareWidth() const{
	return squareWidth;
}