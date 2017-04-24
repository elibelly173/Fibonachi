#include "StartSceen.h"
#include "SimpleAudioEngine.h"
#include "VideoScene.h"

USING_NS_CC;

Scene* StartSceen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartSceen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartSceen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
        
    
    auto winsize = Director::getInstance()->getWinSize();
    auto size = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("start.png"); //here the background.png is a "red screen" png.
    background->setPosition(winsize.width/2, winsize.height/2);
    this->addChild(background);
    
//    background->setScale(0.9f);
    CCLOG("background%f %f", background->getBoundingBox().size.width, background->getBoundingBox().size.height);
    background->setScale(size.width/background->getContentSize().width, size.height/background->getContentSize().height);
    auto touchListener = EventListenerTouchOneByOne::create();
    
    
    
    CCLOG("screen%f %f", size.width, size.height);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(StartSceen::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(StartSceen::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(StartSceen::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(StartSceen::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    
    return true;
}

bool StartSceen::onTouchBegan(Touch* touch, Event* event)
{
    cocos2d::log("touch began");
    return true;
}

void StartSceen::onTouchEnded(Touch* touch, Event* event)
{
    cocos2d::log("touch ended");
    
    
    
    auto myScene = VideoScene::createScene();
    Director::getInstance()->replaceScene(myScene);
//    Director::getInstance()->replaceScene(TransitionSlideInT::create(1, myScene) );
    
    
}

void StartSceen::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");
}

void StartSceen::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}


void StartSceen::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
