#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "GameOverScene.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
	//создаем сцену с физикой
	auto scene = Scene::createWithPhysics();
	//подключаем физику
	scene-> getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene-> getPhysicsWorld()->setGravity(Vect(0,0));

    auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	//добавл€ем слой на сцену 
    scene->addChild(layer);
	//и возвращаем сцену, котора€ потом передаетс€ в AppDelegate
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



	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3); //форма окна, класс физический, и ширина линии 1 = прозрачный

	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);//если стокновение ставим тру

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);//schedule_selector oтвечает за запуск запланированного обратного вызова//запускаем функцию создание(порождение труб) каждые 0.5 сек

	bird = new Bird(this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this); //getEventDispatcher принимает событи€ //истант мен€ет сцены 
    
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	//создаем переменную содержащию очки
	score = 0;
	//задаем формат
	__String *tempScore = __String::createWithFormat("%i", score);
	//задаем размеры и шрифт
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "CyrilicOld.TTF", visibleSize.height * SCORE_FONT_SIZE);
	//задаем цвет
	scoreLabel->setColor(Color3B::WHITE);
	//задаем позицию
	scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
	//а тут хуй пойми че
	this->addChild(scoreLabel, 10000);

	this->scheduleUpdate();

	return true;
}
//объекты созданные с помощью create можно не удал€ть так как это делают умные указатели 

void GameScene::SpawnPipe(float dt)
{
	pipe.SpawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	//проверка соприкосновени€ птички с концом экрана или с трубами, если да, то мен€ем сцену, с переходом 
	if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		//создаем €рлычек с помощью функции создани€ шрифта

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