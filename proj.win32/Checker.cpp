#include "Checker.h"
#include "Filenames.h"
#include "GameSettings.h"

using namespace cocos2d;

using cocos2d::CCDirector;

Checker::Checker(b2World *world, cocos2d::CCPoint point, CheckerColor color, float mass, float radius, float friction, float restitution){
	this->mass = mass;
	this->radius = radius;
	this->friction = friction;
	this->restitution = restitution;

	isMovingOutOfBoard = false;

	// Create paddle body
	b2BodyDef jetBodyDef;
	jetBodyDef.type = b2_dynamicBody;
	jetBodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);
	jetBody = world->CreateBody(&jetBodyDef);
	jetBody->SetLinearDamping(friction);
	jetBody->SetAngularDamping(friction);

	b2CircleShape circleShape;
	circleShape.m_radius = radius;

	b2FixtureDef jetShapeDef;
	jetShapeDef.shape = &circleShape;
	jetShapeDef.density = mass; // !!!! TODO: need to calculate density from mass
	jetShapeDef.friction = friction;
	jetShapeDef.restitution = restitution;

	jetFixture = this->jetBody->CreateFixture(&jetShapeDef);

	// add sprite
	CCSprite* sprite = CCSprite::create(color == CheckerColor::black ? IMAGE_SCENE_CHECKER_BLACK : IMAGE_SCENE_CHECKER_WHITE);	
	sprite->setPosition( ccp( jetBody->GetPosition().x * PTM_RATIO, jetBody->GetPosition().y * PTM_RATIO) );
	sprite->setScale(2 * radius / sprite->getContentSize().width * PTM_RATIO);
	sprite->setUserData(this);

	jetBody->SetUserData(sprite);
}

Checker::~Checker(void)
{
}

void Checker::tick(float dt){
	// This is sprite modifications based on the Box2d object 
	if (jetBody && jetBody->GetUserData() != NULL) {
		CCSprite* myActor = (CCSprite*)jetBody->GetUserData();
		myActor->setPosition( ccp( jetBody->GetPosition().x * PTM_RATIO, jetBody->GetPosition().y * PTM_RATIO) );
		myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(jetBody->GetAngle()) );			

		if (jetBody->GetLinearVelocity().Length() <= 0.2f){
			jetBody->SetAngularVelocity(0);
			jetBody->SetLinearVelocity(b2Vec2(0,0));
		}
	}	
}

cocos2d::CCSprite *Checker::GetSprite() const
{
	if (jetBody && (jetBody->GetUserData() != NULL)) {
		return (CCSprite*)jetBody->GetUserData();
	}
	return NULL;
}

void Checker::ApplyForce(int force, float angle) const {
	if (jetBody){
		force = min(GameSettings::maxForce, force);

		const float newForceX = force * cos(angle);
		const float newForceY = force * sin(angle);
	
		jetBody->ApplyLinearImpulse(b2Vec2(newForceX, newForceY), this->jetBody->GetLocalCenter());
		jetBody->SetAngularVelocity(0);
	}
}

float Checker::GetPositionX(void) const{
	if (!jetBody)
		return 0;
	return this->jetBody->GetPosition().x * PTM_RATIO;
}

float Checker::GetPositionY(void) const{
	if (!jetBody)
		return 0;
	return this->jetBody->GetPosition().y * PTM_RATIO;
}
float Checker::GetLinearVelocity() const{
	if (isMovingOutOfBoard)
		return 1;
	if (!jetBody)
		return 0;
	return this->jetBody->GetLinearVelocity().Length();
}

float Checker::GetAngularVelocity() const{
	if (!jetBody)
		return 0;
	return this->jetBody->GetAngularVelocity();
}

void Checker::RemoveFromBoard(){
	if (jetBody){
		const float scaleFactor = 3.0f;

		CCSprite * sprite = GetSprite();
		if (sprite){
			// let's define direction
			float newX = jetBody->GetPosition().x + jetBody->GetLinearVelocity().x / jetBody->GetLinearVelocity().Length();
			float newY = jetBody->GetPosition().y + jetBody->GetLinearVelocity().y / jetBody->GetLinearVelocity().Length();

			CCFiniteTimeAction* actionMoveFurther = CCMoveTo::create(0.3f, ccp(newX * PTM_RATIO, newY * PTM_RATIO));
			CCFiniteTimeAction* actionScale = CCScaleTo::create(0.5f, sprite->getScale() / scaleFactor);
			CCFiniteTimeAction* actionMoveDone = CCCallFunc::create(this, callfunc_selector(Checker::MoveDone));
			sprite->runAction( CCSequence::create(actionMoveFurther, actionScale, actionMoveDone, NULL) );

			isMovingOutOfBoard = true;
		}
		
		jetBody->SetUserData(NULL);
		jetBody->GetWorld()->DestroyBody(jetBody);
		jetBody = NULL;
	}
}

void Checker::MoveDone(){
	isMovingOutOfBoard = false;
}

void Checker::RemoveByScore(int scores, float delay, ccColor3B color){
	if (jetBody){
		CCSprite * sprite = GetSprite();
		if (sprite){
			CCFiniteTimeAction* actionFadeOutChecker = cocos2d::CCFadeOut::create(SCORE_ANIMATION_DELAY);
			CCDelayTime* delayAction = CCDelayTime::create(delay);

			sprite->runAction( CCSequence::create(delayAction, actionFadeOutChecker, NULL) );

			// display scores	
			char text[20];
			itoa(scores, text, 10);
			CCLabelTTF* pLabel = CCLabelTTF::create(text, "Arial", CCDirector::sharedDirector()->getWinSize().height * 2 / 30 + 4);
			pLabel->setPositionX(sprite->getPositionX());
            pLabel->setPositionY(sprite->getPositionY());
            pLabel->setColor(color);
			pLabel->setScale(0.4);
			
			CCFiniteTimeAction* actionFadeIn = cocos2d::CCFadeIn::create(SCORE_ANIMATION_DELAY);
			CCFiniteTimeAction* actionMove = CCMoveTo::create(SCORE_ANIMATION_DELAY, ccp(sprite->getPositionX(), sprite->getPositionY() + 20));
			CCFiniteTimeAction* scaleAction = CCScaleTo::create(SCORE_ANIMATION_DELAY * 1, 1);
			CCFiniteTimeAction* actionFadeOut = cocos2d::CCFadeOut::create(SCORE_ANIMATION_DELAY);
			pLabel->runAction(CCSequence::create(delayAction, actionFadeIn, scaleAction, actionFadeOut, NULL));
			pLabel->runAction(CCSequence::create(delayAction, actionFadeIn, actionMove, NULL));

			pLabel->setOpacity(0);
			sprite->getParent()->addChild(pLabel, 1500);
		}
	}
}
