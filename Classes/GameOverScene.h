#pragma once

#include "cocos2d.h"


class GameOverScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene(unsigned int tempScore);
	virtual bool init();

    CREATE_FUNC(GameOverScene);//выдел€ет экземпл€р нашего класса
private:
	void GoToMainMenuScene(cocos2d::Ref *sender);
	void GoToGameScene(cocos2d::Ref *sender);
};
