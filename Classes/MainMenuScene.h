#pragma once

#include "cocos2d.h"


class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	virtual bool init();

    CREATE_FUNC(MainMenuScene);//выдел€ет экземпл€р нашего класса

private:
	void GoToGameScene(cocos2d::Ref *sender);
};
