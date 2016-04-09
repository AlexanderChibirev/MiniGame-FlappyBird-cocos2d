#pragma once

#include "cocos2d.h"


class GameOverScene : public cocos2d::Layer
{
public:
	GameOverScene();
	static cocos2d::Scene* createScene();
	virtual bool init() override ;

    CREATE_FUNC(GameOverScene);//�������� ��������� ������ ������
private:
	void goToMainMenuScene(cocos2d::Ref *sender);
	void goToGameScene(cocos2d::Ref *sender);
	unsigned int m_score;
};
