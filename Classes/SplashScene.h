#pragma once

#include "cocos2d.h"


class SplashScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	virtual bool init() override ;
	CREATE_FUNC(SplashScene);//�������� ��������� ������ ������

private:
	void goToMainMenuScene(float dt);
};
