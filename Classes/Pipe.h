#pragma once


#include "cocos2d.h"

class Pipe
{
public:
	Pipe();
	virtual bool init();
	static void create();
	void spawnPipe(cocos2d::Layer *layer);

private:
	cocos2d::Size m_visibleSize;
	cocos2d::Vec2 m_origin;
};
