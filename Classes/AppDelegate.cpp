#include "AppDelegate.h"
#include "SplashScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{

}
void AppDelegate::create() 
{

}
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}
bool AppDelegate::init()
{
	return true;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) 
	{
        glview = GLViewImpl::createWithRect("FlappyBird", Rect(0, 0, 960, 740));//делает окно не увеличива€ и не уменьша€ расширение картинки
		//glview->setFrameSize(640, 480);// делает разрешение экрана меньше 
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
	
	director->setDisplayStats(true);
    director->setAnimationInterval(float(1.0 / 60));
    FileUtils::getInstance()->addSearchPath("res");

    auto scene = SplashScene::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
   Director::getInstance()->startAnimation();
}
