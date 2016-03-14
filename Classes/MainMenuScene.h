#pragma once

#include "cocos2d.h"


class MainMenuScene : public cocos2d::Layer
{
public:
	MainMenuScene();
    static cocos2d::Scene* createScene();
	virtual bool init() override;

    CREATE_FUNC(MainMenuScene);//�������� ��������� ������ ������

private:
	void goToGameScene(cocos2d::Ref *sender);
};
