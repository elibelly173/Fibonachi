//
//  MapviewScene.c
//  fibonachi-cpp
//
//  Created by Future on 2/13/17.
//
//

#include "MapviewScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"


using namespace ui;


Scene* MapviewScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MapviewScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapviewScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    this->scrollsize = Director::getInstance()->getWinSize();
    this->scrollframesize = Size(this->scrollsize.width, this->scrollsize.height);
    this->getLevelInfo();
    this->initscroll();
    this->initAddbutton();
    return true;
}

void MapviewScene::getLevelInfo(){
    ValueMap data;
    std::string path = FileUtils::getInstance()->fullPathForFilename("res/plist/levels.plist");
    data = FileUtils::getInstance()->getValueMapFromFile(path);
    this->arrLevels = data.at("levels").asValueVector();

}

void MapviewScene::initscroll(){
    
    //
    auto scrollView = cocos2d::ui::ScrollView::create();
    scrollView->setContentSize(this->scrollframesize);
    scrollView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    scrollView->setBackGroundColor(Color3B(200, 200, 200));
    scrollView->setPosition(Point(0, 0));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    scrollView->setBounceEnabled(false);
    scrollView->setTouchEnabled(true);
    scrollView->setScrollBarEnabled(false);
    auto containerSize = Size(this->scrollframesize.width, this->scrollframesize.width*4.4);
    scrollView->setInnerContainerSize(containerSize);
    
    
    auto background = Sprite::create("mapback.jpg"); //here the background.png is a "red screen" png.
    background->setPosition(this->scrollframesize.width/2, this->scrollframesize.width*2.2);
    
    background->setScale(this->scrollframesize.width/background->getContentSize().width, this->scrollframesize.width*4.4/background->getContentSize().height);
    scrollView->addChild(background);
    
    
    //    float contentH = scrollView->getContentSize().height;
    //    float h = scrollView->getInnerContainerSize().height - contentH;
    //    float y = MIN(228+268*int((gCurrentStage-1)/3)-contentH/2, h);
    scrollView->jumpToPercentVertical(100);
    scrollView->setTag(TAG_MAP_SCROLL);
    this->addChild(scrollView);
}


void MapviewScene::initAddbutton(){
    
    cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
    
    
    for(int ii=0; ii<this->arrLevels.size(); ii++){
        
        ValueMap sdata = (this->arrLevels[ii]).asValueMap();
        float x =  sdata["x"].asFloat();
        float y =  sdata["y"].asFloat();
        Button* button1 = Button::create(StringUtils::format("res/levels_incomplete/%d.png", (ii + 1)),
                                         StringUtils::format("res/levels_incomplete/%d.png", (ii + 1)));
        
        button1->setPosition(Vec2(this->scrollframesize.width * x / 100.0f, this->scrollframesize.width *y/ 100.0f));
        button1->addTouchEventListener(CC_CALLBACK_2(MapviewScene::touchEvent, this, (int)ii+1));
        button1->setScale(this->scrollframesize.width * 0.13f/button1->getContentSize().width);
//        button1->setPressedActionEnabled(true);
        scrollView->addChild(button1);
        
    }

}

void MapviewScene::showLevelExplainacreen(int level){
    
    this->selectedLevel = level;
    // when levelexplainlayer appears, set touch event of scrollview to false.
    cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
    scrollView->setTouchEnabled(false);
    this->onShowLevelFlag = false;
    //Background
    auto levelExpalinBack = Sprite::create("res/title/Vinyet.png"); //here the background.png is a "red screen" png.
    
    levelExpalinBack->setPosition(this->scrollframesize.width/2, this->scrollframesize.height/2);
    
    levelExpalinBack->setScale(this->scrollframesize.width/levelExpalinBack->getContentSize().width, this->scrollframesize.height/levelExpalinBack->getContentSize().height);
    
    levelExpalinBack->setTag(TAG_MAP_VINEYET);
    this->addChild(levelExpalinBack);
    
    // Layer
    auto levelExplainLayer = Layer::create();
    this->addChild(levelExplainLayer);
    levelExplainLayer->setTag(TAG_MAP_LEVELLAYER);
    
    auto levelBg = Sprite::create("res/title/level_ground.png");
//    levelBg->setPosition(this->scrollframesize.width/2 + this->scrollframesize.width*0.05 , this->scrollframesize.height/2);
    
//    levelBg->setScale(this->scrollframesize.width*0.7/levelBg->getContentSize().width, this->scrollframesize.height*0.7/levelBg->getContentSize().height);
    
    levelBg->setPosition(this->scrollframesize.width*3/2 , this->scrollframesize.height/2);
    levelBg->setScale(this->scrollframesize.width*0.7/levelBg->getContentSize().width);
    levelExplainLayer->addChild(levelBg);
    
//    CCLOG("level %d", level);
    //level title
    auto levelTitle = Sprite::create(StringUtils::format("res/title/level/level%d.png", level));
    auto levelBgPos = levelBg->getPosition();
    levelTitle->setPosition(levelBgPos.x - this->scrollframesize.width*0.03, levelBgPos.y + this->scrollframesize.width*0.2);
    levelTitle->setScale(this->scrollframesize.width*0.27/levelTitle->getContentSize().width);

    levelExplainLayer->addChild(levelTitle);
    
    
    //level content
    auto levelContent = Sprite::create(StringUtils::format("res/title/contents/content%d.png", level));
    levelContent->setPosition(levelBgPos.x - this->scrollframesize.width*0.03, levelBgPos.y + this->scrollframesize.width*0.135);
    levelContent->setScale(this->scrollframesize.width*0.5/levelContent->getContentSize().width);
    
    levelExplainLayer->addChild(levelContent);
    
    
    // level continue
    Button* buttonPlay = Button::create("res/title/Continue.png", "res/title/Continue.png");
    
    buttonPlay->setPosition(Vec2(levelBgPos.x - this->scrollframesize.width*0.025, levelBgPos.y - this->scrollframesize.width*0.16));
    buttonPlay->addTouchEventListener(CC_CALLBACK_2(MapviewScene::onLevelCloseEvent, this, (int)1));
    buttonPlay->setScale(this->scrollframesize.width*0.18/buttonPlay->getContentSize().width);
    
    levelExplainLayer->addChild(buttonPlay);
    
    
    
//    auto levelContinue = Sprite::create("res/title/Continue.png");
//    levelContinue->setPosition(levelBgPos.x - this->scrollframesize.width*0.025, levelBgPos.y - this->scrollframesize.width*0.16);
//    levelContinue->setScale(this->scrollframesize.width*0.18/levelContinue->getContentSize().width);
//    
//    levelExplainLayer->addChild(levelContinue);
    
    
    // adding target time and target number
    ValueMap sdata = (this->arrLevels[level]).asValueMap();
    int targetnumber =  sdata["targetnumber"].asInt();
    int targettime =  sdata["targettime"].asInt();
    
    auto levelNumber = Sprite::create(StringUtils::format("res/title/number%d.png", targetnumber));
    levelNumber->setPosition(levelBgPos.x - this->scrollframesize.width*0.21, levelBgPos.y - this->scrollframesize.width*0.02);
    levelNumber->setScale(this->scrollframesize.width*0.13/levelNumber->getContentSize().width);
    
    levelExplainLayer->addChild(levelNumber);
    
    auto levelTime = Sprite::create(StringUtils::format("res/title/number%d.png", targettime));
    levelTime->setPosition(levelBgPos.x + this->scrollframesize.width*0.16, levelBgPos.y - this->scrollframesize.width*0.02);
    levelTime->setScale(this->scrollframesize.width*0.13/levelTime->getContentSize().width);
    
    levelExplainLayer->addChild(levelTime);
    
    // level close
    
    Button* buttonClose = Button::create("res/title/close.png", "res/title/close.png");
    
    buttonClose->setPosition(Vec2(levelBgPos.x + this->scrollframesize.width*0.285, levelBgPos.y + this->scrollframesize.width*0.19));
    buttonClose->addTouchEventListener(CC_CALLBACK_2(MapviewScene::onLevelCloseEvent, this, (int)2));
    buttonClose->setScale(this->scrollframesize.width * 0.06f/buttonClose->getContentSize().width);
    
    levelExplainLayer->addChild(buttonClose);
    
    
    
    
    
//    for (int i = 0; i<15; i++) {
//        for (int j = 0; j<8; j++) {
//            auto spr = Sprite::create("tile.png");
//            spr->setAnchorPoint(Point::ZERO);
//            spr->setPosition(Point(i * 33, j * 49));
//            levelExplainLayer->addChild(spr);
//        }
//    }
    
    auto action_0 = MoveTo::create(0.4, Point(- this->scrollframesize.width*1.1 , 0));
    auto action_1 = MoveTo::create(0.1, Point(- this->scrollframesize.width*0.95 , 0));
    auto action_2 = Sequence::create(action_0, action_1, NULL);
//    auto action_3 = RepeatForever::create(action_2);
    levelExplainLayer->runAction(action_2);
    
    
    
    
    
}


void MapviewScene::touchEvent(Ref *pSender, Widget::TouchEventType type, int d)
{
//    CCLOG("HelloWorld::setCallFunc_2() = %d", (int)d);
    if(this->onShowLevelFlag) {
        this->showLevelExplainacreen(d);
    }
}

void MapviewScene::onLevelCloseEvent(Ref *pSender, Widget::TouchEventType type, int state)
{
    //    CCLOG("HelloWorld::setCallFunc_2() = %d", (int)d);
    
    auto *levelBg = (Sprite*)this->getChildByTag(TAG_MAP_VINEYET);
    this->removeChild(levelBg);
    
    auto *levelLayer = (Layer*)this->getChildByTag(TAG_MAP_LEVELLAYER);
    
    auto action_0 = MoveTo::create(0.1, Point(- this->scrollframesize.width*0.8 , 0));
    auto action_1 = MoveTo::create(0.8, Point(- this->scrollframesize.width*2 , 0));
    
    
    auto action_2 = CallFuncN::create( CC_CALLBACK_1(MapviewScene::gotoGameviewCallback, this, (int)state));
    auto action_3 = Sequence::create(action_0, action_1, action_2, NULL);
    //    auto action_3 = RepeatForever::create(action_2);
    levelLayer->runAction(action_3);
//    this->scheduleOnce(schedule_selector(MapviewScene::scheduleCallback), 0.8);
//    this->removeChild(levelLayer);
    
    
    
    
    
}

void MapviewScene::gotoGameviewCallback(Ref *sender, int state)
{
    
            auto *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
            scrollView->setTouchEnabled(true);
            this->onShowLevelFlag = true;

    if(state == 1){
        
        auto gameScene = GameScene::createScene(this->selectedLevel);
//        Director::getInstance()->replaceScene(gameScene);
        Director::getInstance()->pushScene(gameScene);
        
    } else if(state == 2){
//        auto *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
//        scrollView->setTouchEnabled(true);
//        this->onShowLevelFlag = true;
    }
    auto *levelLayer = (Layer*)this->getChildByTag(TAG_MAP_LEVELLAYER);
    this->removeChild(levelLayer);

    CCLOG("HelloWorld::setCallFunc_2()%d", state);
}



void MapviewScene::scheduleCallback(float delta)
{
    auto *levelLayer = (Layer*)this->getChildByTag(TAG_MAP_LEVELLAYER);
    this->removeChild(levelLayer);
}


