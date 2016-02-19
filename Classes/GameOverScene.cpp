#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameOverScene::createScene()
{
	//объект сцены затем экземпл€р нашего класа экземпл€р
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
	//добавл€ем слой на сцену
    scene->addChild(layer);
	//и возвращаем сцену, котора€ потом передаетс€ в AppDelegate
    return scene;
}

bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	//////////////////////////////
	//создаем €рлычек с помощью функции создани€ шрифта
	auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	//мен€ем ориджин, т.е. точку позиционировани€ на левую нижнюю 
	label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	label->setPosition(960 / 4, 740 / 4);
	//добавл€ем слой на сцену(экран)
	this->addChild(label, 1);

	////////////////////////////
	//загружаем картинку
	auto sprite = Sprite::create("bird.png");
	//мен€ем ориджин, т.е. точку позиционировани€ на левую нижнюю 
	sprite->setAnchorPoint(Vec2(0, 0));
	//задаем ей позицию
	sprite->setPosition(900/2, 740/2);
	//и добавл€ем на сценну 
	this->addChild(sprite, 0);
	//////////////////////////////
    //загружаем кокосовскую кортинку и выводим ее
	auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
	///////////////////////////////



    return true;
}
//объекты созданные с помощью create можно не удал€ть так как это делают умные указатели 