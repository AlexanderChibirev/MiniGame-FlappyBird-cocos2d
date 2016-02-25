#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "GameOverScene.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
	//������� ����� � �������
	auto scene = Scene::createWithPhysics();
	//���������� ������
	scene-> getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene-> getPhysicsWorld()->setGravity(Vect(0,0));

    auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	//��������� ���� �� ����� 
    scene->addChild(layer);
	//� ���������� �����, ������� ����� ���������� � AppDelegate
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("bgForGame.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);



	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3); //����� ����, ����� ����������, � ������ ����� 1 = ����������

	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);//���� ����������� ������ ���

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);//schedule_selector o������� �� ������ ���������������� ��������� ������//��������� ������� ��������(���������� ����) ������ 0.5 ���

	bird = new Bird(this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this); //getEventDispatcher ��������� ������� //������ ������ ����� 
    
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	//������� ���������� ���������� ����
	score = 0;
	//������ ������
	__String *tempScore = __String::createWithFormat("%i", score);
	//������ ������� � �����
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "CyrilicOld.TTF", visibleSize.height * SCORE_FONT_SIZE);
	//������ ����
	scoreLabel->setColor(Color3B::WHITE);
	//������ �������
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
	//� ��� ��� ����� ��
	this->addChild(scoreLabel, 10000);

	this->scheduleUpdate();

	return true;
}
//������� ��������� � ������� create ����� �� ������� ��� ��� ��� ������ ����� ��������� 

void GameScene::SpawnPipe(float dt)
{
	pipe.SpawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	//�������� ��������������� ������ � ������ ������ ��� � �������, ���� ��, �� ������ �����, � ��������� 
	if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		//������� ������� � ������� ������� �������� ������

		auto scene = GameOverScene::createScene(score);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

	else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		score++;
		__String *tempScore = __String::createWithFormat("%i", score);
		scoreLabel->setString(tempScore->getCString());
	}

	return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	bird->Fly();

	this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);

	return true;
}

void GameScene::StopFlying(float dt)
{
	bird->StopFlying();
}

void GameScene::update(float dt)
{
	bird->Fall();
}