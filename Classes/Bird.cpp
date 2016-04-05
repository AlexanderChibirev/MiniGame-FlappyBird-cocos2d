 #include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird()
{
	
}

Bird * Bird::create()
{
	Bird *bird = new (std::nothrow) Bird();
	if ( (bird && bird->initWithFile("birdForGame.png")) && (bird->init()) )
	{
		bird->autorelease();
		return bird;
	}
	CC_SAFE_DELETE(bird);
	return nullptr;
}

bool Bird::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();

	setPosition(Point(m_visibleSize.width / 2 + m_origin.x, m_visibleSize.height / 2 + m_origin.y));

	auto flappyBody = PhysicsBody::createCircle(getContentSize().width / 2); //создаем тело с физикой

	flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);

	setPhysicsBody(flappyBody);
	m_isFalling = true;
	return true;
}

void Bird::fly()
{
	m_isFalling = false;
}

void Bird::stopFlying()
{
	m_isFalling = true;
}


void Bird::fall()
{
	if (true == m_isFalling)
	{
		setPositionX(m_visibleSize.width / 2 + m_origin.x);
		setPositionY(getPositionY() - (BIRD_FALLING_SPEED * m_visibleSize.height));
	}
	else
	{
		setPositionX(m_visibleSize.width / 2 + m_origin.x);
		setPositionY(getPositionY() + (BIRD_FALLING_SPEED * m_visibleSize.height));
	}
}
