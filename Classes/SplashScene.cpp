#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SplashScene::createScene()
{
	//������ ����� ����� ��������� ������ ����� ���������
    auto scene = Scene::create();
    auto layer = SplashScene::create();
	//��������� ���� �� �����
    scene->addChild(layer);
	//� ���������� �����, ������� ����� ���������� � AppDelegate
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
	//�������� ������� �� 2.5 ���
	this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
	
	
	//////////////////////////////
	//������� ������� � ������� ������� �������� ������
	auto nameGame = Label::createWithSystemFont("  Flappy bird", "Arial", 96);
	auto logoSprite = Sprite::create("bird.png");
	auto backgroundSprite = Sprite::create("logoBg.png");
	//������ ��������
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	logoSprite->setPosition(Point(visibleSize.width / 1.9 , visibleSize.height / 4 ));
	nameGame->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);
	this->addChild(nameGame);
	this->addChild(logoSprite);


    return true;
}
//������� ��������� � ������� create ����� �� ������� ��� ��� ��� ������ ����� ��������� 



void SplashScene::GoToMainMenuScene( float dt )
{	
	//������ �����
    auto scene = MainMenuScene::createScene();
    //���������� ����� ���������
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

