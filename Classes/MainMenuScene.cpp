#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainMenuScene::createScene()
{
	//������ ����� ����� ��������� ������ ����� ���������
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
	//��������� ���� �� �����
    scene->addChild(layer);
	//� ���������� �����, ������� ����� ���������� � AppDelegate
    return scene;
}
//������� ����)
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

	//�������� ������
	auto playItem = MenuItemImage::create("Star Button.png", "Start Button Clicked.png", CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
	playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);
	//����� ��������

	this->addChild(menu);
	

    return true;
}
//������� ��������� � ������� create ����� �� ������� ��� ��� ��� ������ ����� ��������� 
//����� �� �������� ������ � ��� ��� ��������� ������, �� ��������� � ��� �������
void MainMenuScene::goToGameScene(cocos2d::Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}