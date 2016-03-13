#pragma once

#include "cocos2d.h"


class SplashScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	virtual bool init() override ;
	CREATE_FUNC(SplashScene);//выдел€ет экземпл€р нашего класса

private:
	void goToMainMenuScene(float dt);
};
