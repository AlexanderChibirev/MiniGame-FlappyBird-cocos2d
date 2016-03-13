#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainMenuScene::createScene()
{
	//объект сцены затем экземпл€р нашего класа экземпл€р
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
	//добавл€ем слой на сцену
    scene->addChild(layer);
	//и возвращаем сцену, котора€ потом передаетс€ в AppDelegate
    return scene;
}
//главный инит)
bool MainMenuScene::init()
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

	//создание кнопки
	auto playItem = MenuItemImage::create("Star Button.png", "Start Button Clicked.png", CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);
	//конец создани€

	this->addChild(menu);
	

    return true;
}
//объекты созданные с помощью create можно не удал€ть так как это делают умные указатели 
//когда мы получаем сигнал о том что отпустили кнопку, мы переходим в эту функцию
void MainMenuScene::goToGameScene(cocos2d::Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}