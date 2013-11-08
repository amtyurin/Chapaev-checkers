#include "Checker.h"
#include "Filenames.h"

using namespace cocos2d;

using cocos2d::CCDirector;

Checker::Checker(b2World *world, cocos2d::CCLayer* scene, cocos2d::CCPoint point, CheckerColor color, float mass, float radius, float friction, float restitution){
	this->mass = mass;
	this->radius = radius;
	this->friction = friction;
	this->restitution = restitution;

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

	scene->addChild(sprite, 1000);
	jetBody->SetUserData(sprite);
}

Checker::~Checker(void)
{
}

void Checker::tick(float dt){
	// This is sprite modifications based on the Box2d object 
	if (jetBody->GetUserData() != NULL) {
		CCSprite* myActor = (CCSprite*)jetBody->GetUserData();
		myActor->setPosition( ccp( jetBody->GetPosition().x * PTM_RATIO, jetBody->GetPosition().y * PTM_RATIO) );
		myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(jetBody->GetAngle()) );			
	}	
}

cocos2d::CCSprite *Checker::GetSprite() const
{
	if (jetBody->GetUserData() != NULL) {
		return (CCSprite*)jetBody->GetUserData();
	}
	return NULL;
}

void Checker::ApplyForce(int force, float angle){
	const float newForceX = force * cos(angle);
	const float newForceY = force * sin(angle);
	
	this->jetBody->ApplyLinearImpulse(b2Vec2(newForceX, newForceY), this->jetBody->GetLocalCenter());
}

float Checker::GetPositionX(void) const{
	return this->jetBody->GetPosition().x;
}

float Checker::GetPositionY(void) const{
	return this->jetBody->GetPosition().y;
}
float Checker::GetLinearVelocity() const{
	return this->jetBody->GetLinearVelocity().Length();
}

float Checker::GetAngularVelocity() const{
	return this->jetBody->GetAngularVelocity();
}
