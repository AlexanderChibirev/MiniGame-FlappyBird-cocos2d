#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SplashScene::createScene()
{
	//объект сцены затем экземпл€р нашего класа экземпл€р
    auto scene = Scene::create();
    auto layer = SplashScene::create();
	//добавл€ем слой на сцену
    scene->addChild(layer);
	//и возвращаем сцену, котора€ потом передаетс€ в AppDelegate
    return scene;
}

bool SplashScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//задержка фунеции на 2.5 сек
	this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
	
	
	//////////////////////////////
	//создаем €рлычек с помощью функции создани€ шрифта
	auto nameGame = Label::createWithSystemFont("  Flappy bird", "Arial", 96);
	auto logoSprite = Sprite::create("bird.png");
	auto backgroundSprite = Sprite::create("logoBg.png");
	//задаем середину
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	logoSprite->setPosition(Point(visibleSize.width / 1.9 , visibleSize.height / 4 ));
	nameGame->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);
	this->addChild(nameGame);
	this->addChild(logoSprite);


    return true;
}
//объекты созданные с помощью create можно не удал€ть так как это делают умные указатели 



void SplashScene::GoToMainMenuScene( float dt )
{	
	//объект сцены
    auto scene = MainMenuScene::createScene();
    //возвращает общий экземпл€р
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

