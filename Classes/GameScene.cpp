#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
	//создаем сцену с физикой
	auto scene = Scene::createWithPhysics();
	//подключаем физику
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	//добавляем слой на сцену
    scene->addChild(layer);
	//и возвращаем сцену, которая потом передается в AppDelegate
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

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);//schedule_selector oтвечает за запуск запланированного обратного вызова//запускаем функцию создание(порождение труб) каждые 0.5 сек

	bird = new Bird(this);
    return true;
}
//объекты созданные с помощью create можно не удалять так как это делают умные указатели 

void GameScene::SpawnPipe(float dt)
{
	pipe.SpawnPipe(this);
}