//
//  MapviewScene.h
//  fibonachi-cpp
//
//  Created by Future on 2/13/17.
//
//

#ifndef __MAPVIEW_SCENE_H__
#define __MAPVIEW_SCENE_H__


#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include <stdlib.h>
USING_NS_CC_EXT;
USING_NS_CC;
using namespace std;


#define TAG_MAP_SCROLL      1
#define TAG_MAP_VINEYET      2
#define TAG_MAP_LEVELLAYER      3
#define TAG_MAP_FOOTICON      4
#define TAG_MAP_BUTTON 2000
class MapviewScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    void initscroll();
    void initAddbutton();
    void showLevelExplainacreen(int level);
    void getLevelInfo();
    
    void showPos();
    void movePos(int targetlevel);
    void changeButton(int diff, int insteadlevel);
    
    void playMusic();
    
//    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
//    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
//    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
//    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    
    void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type, int d);
    void scheduleCallback(float delta);
    void onLevelCloseEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type, int d);
    void gotoGameviewCallback(cocos2d::Ref* sender, int state);
public:
    cocos2d::Size scrollsize;
    cocos2d::Size scrollframesize;
    bool onShowLevelFlag= true;
    ValueVector arrLevels;
    int selectedLevel;
    int completedLevel = 0;
    int lockLevel = 0;
    
    bool enterFlag = false;
   
private:
    CREATE_FUNC(MapviewScene);

   
    
};


#endif /* MapviewScene_h */
