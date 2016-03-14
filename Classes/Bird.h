#pragma once

#include "SimpleAudioEngine.h"  
#include "cocos2d.h"

class Bird
{
public:
	Bird(cocos2d::Layer *layer);
	virtual bool init();
	static void create();
	void fall();
	void fly();
	void stopFlying();
private:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;

	cocos2d::Sprite *m_flappyBird;

	bool m_isFalling;
};
