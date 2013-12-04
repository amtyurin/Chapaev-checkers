#ifndef __CHECKER_H__
#define __CHECKER_H__
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "FormationTypes.h"

class Checker : public cocos2d::CCObject
{
private:	
	b2Fixture *jetFixture;
	b2Body *jetBody;

	float mass;
	float radius;
	float friction;
	float restitution;

	bool isMovingOutOfBoard;
	void MoveDone();
	
	Checker(void);
	Checker(const Checker&);
	Checker & operator = (const Checker &);
protected:

public:
	Checker(b2World *world, cocos2d::CCPoint point, CheckerColor color, float mass, float radius, float friction, float restitution);
	~Checker(void);

	void tick(float dt);	

	float GetPositionX(void) const;
	float GetPositionY(void) const;
	float GetLinearVelocity() const;
	float GetAngularVelocity() const;

	void ApplyForce(int force, float angle) const;

	cocos2d::CCSprite *GetSprite() const;

	void RemoveFromBoard();

	void RemoveByScore(int scores, float delay, cocos2d::ccColor3B color);
};

#endif /*__CHECKER_H__*/
