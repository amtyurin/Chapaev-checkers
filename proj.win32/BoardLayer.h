#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "Filenames.h"

#include "B2DebugDraw\B2DebugDrawLayer.h"

class BoardLayer:
	public cocos2d::CCLayer
{
	b2World *box2world;
	int boardWidth;
	int boardCenterX;
	int boardCenterY;
	int squareWidth;
	
	void gameLogic(float dt);
	void DrawBoard();

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	CREATE_FUNC(BoardLayer);

	b2World *getBox2World() const;

	int GetCoordXForPosX(int posX);
	int GetCoordYForPosY(int posY);

	int GetSquareWidth() const;

	bool IsOutOfBorder(cocos2d::CCPoint point) const;
};


