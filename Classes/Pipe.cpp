#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::spawnPipe(cocos2d::Layer *layer)
{
	auto topPipe = Sprite::create("kaktus.png");
	auto bottomPipe = Sprite::create("kaktus.png");

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

	auto random = CCRANDOM_0_1();

	if (random < LOWER_SCREEN_PIPE_THRESHOLD)
	{
		random = float(LOWER_SCREEN_PIPE_THRESHOLD);
	}
	else if (random > UPPER_SCREEN_PIPE_THRESHOLD)
	{
		random = float(UPPER_SCREEN_PIPE_THRESHOLD);
	}

	auto topPipePosition = (random * m_visibleSize.height) + (topPipe->getContentSize().height/2);

	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);

	bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);//задаем параметры контакта (расстояние)
	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	topPipeBody->setContactTestBitmask(true); //если стокновение ставим тру
	bottomPipeBody->setContactTestBitmask(true);

	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	topPipe->setPosition(Point(m_visibleSize.width + topPipe->getContentSize().width + m_origin.x, topPipePosition));
	bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - (Sprite::create("birdForGame.png")->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));

	layer->addChild(topPipe);
	layer->addChild(bottomPipe);

	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * m_visibleSize.width, Point(-m_visibleSize.width * 1.5, 0));
	auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * m_visibleSize.width, Point(-m_visibleSize.width * 1.5, 0));

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);

	//создаем тело между трубами, если птичка задевает это тело, то очки добавл 
	auto pointNode = Node::create();
	auto pointBody = PhysicsBody::createBox(Size(0, Sprite::create("birdForGame.png")->getContentSize().height * PIPE_GAP));

	pointBody->setDynamic(false);
	pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
	pointBody->setContactTestBitmask(true);

	pointNode->setPhysicsBody(pointBody);
	pointNode->setPosition(Point(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe->getContentSize().height / 2) - ((Sprite::create("birdForGame.png")->getContentSize().height * PIPE_GAP) / 2)));

	layer->addChild(pointNode);

	auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * m_visibleSize.width, Point(-m_visibleSize.width * 1.5, 0));

	pointNode->runAction(pointNodeAction);
}


