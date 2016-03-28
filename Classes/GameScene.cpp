#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "GameOverScene.h"
USING_NS_CC;

using namespace cocostudio::timeline;
GameScene::GameScene()
{

}

Scene* GameScene::createScene()
{
	//ñîçäàåì ñöåíó ñ ôèçèêîé
	auto scene = Scene::createWithPhysics();
	//ïîäêëþ÷àåì ôèçèêó
	//scene-> getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//ïîêàçûâàåò êîëëèçèè
	scene-> getPhysicsWorld()->setGravity(Vect(0,0));
    auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	//äîáàâëÿåì ñëîé íà ñöåíó 
    scene->addChild(layer);
	//è âîçâðàùàåì ñöåíó, êîòîðàÿ ïîòîì ïåðåäàåòñÿ â AppDelegate
    return scene;
}

void  GameScene::setPhysicsWorld(cocos2d::PhysicsWorld *world)
{
	m_sceneWorld = world;
};

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("bgForGame.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);



	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3); //ôîðìà îêíà, êëàññ ôèçè÷åñêèé, è øèðèíà ëèíèè 1 = ïðîçðà÷íûé

	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);//åñëè ñòîêíîâåíèå ñòàâèì òðó

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	this->schedule(schedule_selector(GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);//schedule_selector oòâå÷àåò çà çàïóñê çàïëàíèðîâàííîãî îáðàòíîãî âûçîâà//çàïóñêàåì ôóíêöèþ ñîçäàíèå(ïîðîæäåíèå òðóá) êàæäûå 0.5 ñåê

	bird = new Bird(this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this); //getEventDispatcher ïðèíèìàåò ñîáûòèÿ //èñòàíò ìåíÿåò ñöåíû 
    
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	//ñîçäàåì ïåðåìåííóþ ñîäåðæàùèþ î÷êè
	m_score = 0;
	//çàäàåì ôîðìàò
	__String *tempScore = __String::createWithFormat("%i", m_score);
	//çàäàåì ðàçìåðû è øðèôò
	m_scoreLabel = Label::createWithTTF(tempScore->getCString(), "CyrilicOld.TTF", visibleSize.height * SCORE_FONT_SIZE);
	//çàäàåì öâåò
	m_scoreLabel->setColor(Color3B::BLACK);
	//çàäàåì ïîçèöèþ
	m_scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
	//à òóò õóé ïîéìè ÷å
	this->addChild(m_scoreLabel);

	this->scheduleUpdate();


	return true;
}
//îáúåêòû ñîçäàííûå ñ ïîìîùüþ create ìîæíî íå óäàëÿòü òàê êàê ýòî äåëàþò óìíûå óêàçàòåëè 

void GameScene::spawnPipe(float dt)
{
	pipe.spawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	//ïðîâåðêà ñîïðèêîñíîâåíèÿ ïòè÷êè ñ êîíöîì ýêðàíà èëè ñ òðóáàìè, åñëè äà, òî ìåíÿåì ñöåíó, ñ ïåðåõîäîì 
	if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		//ñîçäàåì ÿðëû÷åê ñ ïîìîùüþ ôóíêöèè ñîçäàíèÿ øðèôòà
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Hit.wav");
		auto scene = GameOverScene::createScene(m_score);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

	else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Point.wav");
		m_score++;
		__String *tempScore = __String::createWithFormat("%i", m_score);
		m_scoreLabel->setString(tempScore->getCString());
	}

	return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	bird->fly();

	this->scheduleOnce(schedule_selector(GameScene::stopFlying), BIRD_FLY_DURATION);

	return true;
}

void GameScene::stopFlying(float dt)
{
	bird->stopFlying();
}

void GameScene::update(float dt)
{
	bird->fall();
}
