#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "GameOverScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
GameScene::GameScene()
{

}

Scene* GameScene::createScene()
{
	//������� ����� � �������
	auto scene = Scene::createWithPhysics();
	//���������� ������
	//scene-> getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//���������� ��������
	scene-> getPhysicsWorld()->setGravity(Vect(0,0));
    auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	//��������� ���� �� ����� 
    scene->addChild(layer);
	//� ���������� �����, ������� ����� ���������� � AppDelegate
    return scene;
}

void  GameScene::setPhysicsWorld(cocos2d::PhysicsWorld *world)
{
	m_sceneWorld = world;
};

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

	this->schedule(schedule_selector(GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);//schedule_selector o������� �� ������ ���������������� ��������� ������//��������� ������� ��������(���������� ����) ������ 0.5 ���

	m_pBird = new Bird();
	m_pBird->create(this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this); //getEventDispatcher ��������� ������� //������ ������ ����� 
    
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	//������� ���������� ���������� ����
	m_score = 0;
	//������ ������
	__String *tempScore = __String::createWithFormat("%i", m_score);
	//������ ������� � �����
	m_scoreLabel = Label::createWithTTF(tempScore->getCString(), "CyrilicOld.TTF", visibleSize.height * SCORE_FONT_SIZE);
	//������ ����
	m_scoreLabel->setColor(Color3B::BLACK);
	//������ �������
	m_scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
	//� ��� ��� ����� ��
	this->addChild(m_scoreLabel);

	this->scheduleUpdate();


	return true;
}
//������� ��������� � ������� create ����� �� ������� ��� ��� ��� ������ ����� ��������� 

void GameScene::spawnPipe(float dt)
{
	pipe.spawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	//�������� ��������������� ������ � ������ ������ ��� � �������, ���� ��, �� ������ �����, � ��������� 
	if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		//������� ������� � ������� ������� �������� ������
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Hit.wav");
		auto scene = GameOverScene::createScene(m_score);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

	else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Point.wav");
		m_score++;
		__String *tempScore = __String::createWithFormat("%i", m_score);
		m_scoreLabel->setString(tempScore->getCString());
	}

	return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	m_pBird->fly();

	this->scheduleOnce(schedule_selector(GameScene::stopFlying), BIRD_FLY_DURATION);

	return true;
}

void GameScene::stopFlying(float dt)
{
	m_pBird->stopFlying();
}

void GameScene::update(float dt)
{
	m_pBird->fall();
}