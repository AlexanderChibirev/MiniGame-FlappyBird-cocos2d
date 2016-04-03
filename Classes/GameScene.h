#pragma once

#include "Pipe.h"
#include "Bird.h"
#include "cocos2d.h"


class GameScene : public cocos2d::Layer
{
public:
	GameScene();
    static cocos2d::Scene* createScene();
	virtual bool init() override;

    CREATE_FUNC(GameScene);//выдел€ет экземпл€р нашего класса

private:
	void setPhysicsWorld(cocos2d::PhysicsWorld *world);


	void spawnPipe(float dt);

	bool onContactBegin(cocos2d::PhysicsContact &contact);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void stopFlying(float dt);
	void update(float dt);

	cocos2d::PhysicsWorld *m_sceneWorld;

	Pipe pipe;

	Bird *m_pBird;
	
	unsigned int m_score;
	
	cocos2d::Label *m_scoreLabel;
};
