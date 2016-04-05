#pragma once

#include "SimpleAudioEngine.h"  
#include "cocos2d.h"

class Bird: public cocos2d::Sprite
{
public:
	Bird();
	static Bird *create();
	bool init() override;
	void fall();
	void fly();
	void stopFlying();
private:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;

	bool m_isFalling;
};
