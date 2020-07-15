
#include "VideoScene.h"
#include "SimpleAudioEngine.h"
#include "MapviewScene.h"

USING_NS_CC;

Scene* VideoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = VideoScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool VideoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    playMusic();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    cocos2d::experimental::ui::VideoPlayer *videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
    videoPlayer->setFileName("res/video/video2.mp4");
    //    videoPlayer->setURL("../res/video/video2.mp4");
    
    
    videoPlayer->setContentSize(visibleSize);
    videoPlayer->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //    videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //    videoPlayer->setFullScreenEnabled(true);
    videoPlayer->play();
    videoPlayer->addEventListener(CC_CALLBACK_2(VideoScene::videoEventCallback, this));
    this->addChild(videoPlayer);
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(VideoScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(VideoScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(VideoScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(VideoScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void VideoScene::playMusic(){
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("res/music/video.mp3", true);
}

bool VideoScene::onTouchBegan(Touch* touch, Event* event)
{
    cocos2d::log("touch began");
    return true;
}

void VideoScene::onTouchEnded(Touch* touch, Event* event)
{
    cocos2d::log("touch ended");
//    auto Mapviewscene = MapviewScene::createScene();
//    Director::getInstance()->replaceScene(TransitionFade::create(0.5, Mapviewscene, Color3B(0,255,255)));
    
    auto scene = MapviewScene::createScene();
    Director::getInstance()->replaceScene(scene);
//    Director::getInstance()->replaceScene(myScene);
}

void VideoScene::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");
}

void VideoScene::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}


void VideoScene::menuCloseCallback(Ref* pSender)
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
void VideoScene::gotoMapScene(){
    auto scene = MapviewScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void VideoScene::videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType)
{
    switch (eventType) {
        case cocos2d::experimental::ui::VideoPlayer::EventType::PLAYING:
            
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::PAUSED:
            gotoMapScene();
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::STOPPED:
            gotoMapScene();
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::COMPLETED:
            gotoMapScene();
            break;
        default:
            break;
    }
}
