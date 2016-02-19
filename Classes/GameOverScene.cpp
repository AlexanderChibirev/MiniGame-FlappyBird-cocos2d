#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameOverScene::createScene()
{
	//������ ����� ����� ��������� ������ ����� ���������
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
	//��������� ���� �� �����
    scene->addChild(layer);
	//� ���������� �����, ������� ����� ���������� � AppDelegate
    return scene;
}

bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	//////////////////////////////
	//������� ������� � ������� ������� �������� ������
	auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	//������ �������, �.�. ����� ���������������� �� ����� ������ 
	label->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	label->setPosition(960 / 4, 740 / 4);
	//��������� ���� �� �����(�����)
	this->addChild(label, 1);

	////////////////////////////
	//��������� ��������
	auto sprite = Sprite::create("bird.png");
	//������ �������, �.�. ����� ���������������� �� ����� ������ 
	sprite->setAnchorPoint(Vec2(0, 0));
	//������ �� �������
	sprite->setPosition(900/2, 740/2);
	//� ��������� �� ������ 
	this->addChild(sprite, 0);
	//////////////////////////////
    //��������� ����������� �������� � ������� ��
	auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
	///////////////////////////////



    return true;
}
//������� ��������� � ������� create ����� �� ������� ��� ��� ��� ������ ����� ��������� 