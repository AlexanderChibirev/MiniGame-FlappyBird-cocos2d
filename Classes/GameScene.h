#pragma once

#include "Pipe.h"
#include "Bird.h"
#include "cocos2d.h"


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	virtual bool init();

    CREATE_FUNC(GameScene);//выдел€ет экземпл€р нашего класса

private:
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world)
	{
		sceneWorld = world; 
	};

	void SpawnPipe(float dt);

	cocos2d::PhysicsWorld *sceneWorld;

	Pipe pipe;

	Bird *bird;
};
