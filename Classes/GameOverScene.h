#pragma once

#include "cocos2d.h"


class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	virtual bool init();

    CREATE_FUNC(GameOverScene);//выдел€ет экземпл€р нашего класса
};
