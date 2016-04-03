#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird()
{
	
}

void Bird::create( cocos2d::Layer *layer)
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();

	m_flappyBird = Sprite::create("birdForGame.png");
	m_flappyBird->setPosition(Point(m_visibleSize.width / 2 + m_origin.x, m_visibleSize.height / 2 + m_origin.y));

	auto flappyBody = PhysicsBody::createCircle(m_flappyBird->getContentSize().width / 2); //создаем тело с физикой

	flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);

	m_flappyBird->setPhysicsBody(flappyBody);

	layer->addChild(m_flappyBird, 100);

	m_isFalling = true;

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
		m_flappyBird->setPositionX(m_visibleSize.width / 2 + m_origin.x);
		m_flappyBird->setPositionY(m_flappyBird->getPositionY() - (BIRD_FALLING_SPEED * m_visibleSize.height));
	}
	else
	{
		m_flappyBird->setPositionX(m_visibleSize.width / 2 + m_origin.x);
		m_flappyBird->setPositionY(m_flappyBird->getPositionY() + (BIRD_FALLING_SPEED * m_visibleSize.height));
	}
}
