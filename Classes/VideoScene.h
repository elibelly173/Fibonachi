//
//  VideoScene.hpp
//  fibonachi-cpp
//
//  Created by Future on 2/13/17.
//
//

#ifndef __VIDEO_SCENE_H__
#define __VIDEO_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include <stdlib.h>
using namespace std;

class VideoScene : public cocos2d::Layer
{
public:    
    static cocos2d::Scene* createScene();
    CREATE_FUNC(VideoScene);
    
    void gotoMapScene();
    
    virtual bool init();
    void playMusic();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    
    void videoEventCallback(cocos2d::Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType);
private:
    cocos2d::Label* labelTouchInfo;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    
};

#endif // __VIDEO_SCENE_H__

