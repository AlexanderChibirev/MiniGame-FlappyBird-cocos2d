#pragma once

#include "cocos2d.h"


class GameOverScene : public cocos2d::Layer
{
public:
	GameOverScene();
	static cocos2d::Scene* createScene(unsigned int tempScore);
	virtual bool init() override ;

    CREATE_FUNC(GameOverScene);//выдел€ет экземпл€р нашего класса
private:
	void goToMainMenuScene(cocos2d::Ref *sender);
	void goToGameScene(cocos2d::Ref *sender);
};
