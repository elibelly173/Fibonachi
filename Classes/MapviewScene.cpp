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
//
//    UserDefault::getInstance()->setIntegerForKey("completedLevel",0);
//    UserDefault::getInstance()->setIntegerForKey("lockLevel",0);

    
    completedLevel =UserDefault::getInstance()->getIntegerForKey("completedLevel");
    lockLevel = UserDefault::getInstance()->getIntegerForKey("lockLevel");
    
//    CCLOG("completedLevel %d", completedLevel);
    
    scrollsize = Director::getInstance()->getWinSize();
    scrollframesize = Size(scrollsize.width, scrollsize.height);
    getLevelInfo();
    initscroll();
    initAddbutton();
    showPos();
    
    
    return true;
}

void MapviewScene::playMusic(){
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
   
    audio->playBackgroundMusic("res/music/map.mp3", true);
//    audio->playBackgroundMusic("res/music/map.mp3", true);
}



void MapviewScene::initAddbutton(){
    
    cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
    
    
    for(int ii=0; ii<arrLevels.size(); ii++){
        ValueMap sdata = (arrLevels[ii]).asValueMap();
        float x =  sdata["x"].asFloat();
        float y =  sdata["y"].asFloat();
        Button* button1;
        if(ii<completedLevel){
            button1 = Button::create(StringUtils::format("res/levels_complete/%d.png", (ii + 1)),
                                     StringUtils::format("res/levels_complete/%d_selected.png", (ii + 1)));
            button1->setScale(scrollframesize.width * 0.18f/button1->getContentSize().width);
            button1->setPosition(Vec2(scrollframesize.width * x / 100.0f, scrollframesize.width *y/ 100.0f));
            button1->addTouchEventListener(CC_CALLBACK_2(MapviewScene::touchEvent, this, (int)ii+1));
            button1->setTag(TAG_MAP_BUTTON+ii);
            scrollView->addChild(button1);

            
            
            const char *levelstarString = StringUtils::format("level%dstar", ii+1).c_str();
            int starCount = UserDefault::getInstance()->getIntegerForKey(levelstarString, 1);
            
            auto starImage = Sprite::create(StringUtils::format("res/star_levels/%d.png", starCount)); //here the background.png is a "red screen" png.
            starImage->setPosition(Vec2(scrollframesize.width * x / 100.0f, scrollframesize.width *(y - 4.5)/ 100.0f));
            starImage->setScale(scrollframesize.width*0.15f/starImage->getContentSize().width);
            scrollView->addChild(starImage);
        } else {
            
            button1 = Button::create(StringUtils::format("res/levels_incomplete/%d.png", (ii + 1)),
                                     StringUtils::format("res/levels_incomplete/%d.png", (ii + 1)));
            button1->setScale(scrollframesize.width * 0.13f/button1->getContentSize().width);
            button1->setPosition(Vec2(scrollframesize.width * x / 100.0f, scrollframesize.width *y/ 100.0f));
            button1->addTouchEventListener(CC_CALLBACK_2(MapviewScene::touchEvent, this, (int)ii+1));
            button1->setTag(TAG_MAP_BUTTON+ii);
            scrollView->addChild(button1);

        }
        
    }
    
}

void MapviewScene::getLevelInfo(){
    ValueMap data;
    std::string path = FileUtils::getInstance()->fullPathForFilename("res/plist/levels.plist");
    data = FileUtils::getInstance()->getValueMapFromFile(path);
    this->arrLevels = data.at("levels").asValueVector();
    CCLOG("level %d", 55);
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
        
    int zones4 = UserDefault::getInstance()->getIntegerForKey("zones4", 0);
    if (zones4 == 0) {
        auto background5 = Sprite::create("res/mapback/31-32.png"); //here the background.png is a "red screen" png.
        background5->setPosition(this->scrollframesize.width/2, this->scrollframesize.width*3.77);
        
        background5->setScale(this->scrollframesize.width/background5->getContentSize().width);
        scrollView->addChild(background5);
    }
    
    int zones3 = UserDefault::getInstance()->getIntegerForKey("zones3", 0);
    if (zones3 == 0) {
        auto background4 = Sprite::create("res/mapback/25-30.png"); //here the background.png is a "red screen" png.
        background4->setPosition(this->scrollframesize.width/2, this->scrollframesize.width*3.488);

        background4->setScale(this->scrollframesize.width/background4->getContentSize().width);
        scrollView->addChild(background4);
    }
    
    int zones2 = UserDefault::getInstance()->getIntegerForKey("zones2", 0);
    if (zones2 == 0) {
        auto background3 = Sprite::create("res/mapback/19-24.png"); //here the background.png is a "red screen" png.
        background3->setPosition(this->scrollframesize.width/2, this->scrollframesize.width*2.607);

        background3->setScale(this->scrollframesize.width/background3->getContentSize().width);
        scrollView->addChild(background3);
    }
    
    int zones1 = UserDefault::getInstance()->getIntegerForKey("zones1", 0);
    if (zones1 == 0) {
        auto background2 = Sprite::create("res/mapback/13-18.png"); //here the background.png is a "red screen" png.
        background2->setPosition(this->scrollframesize.width/2, this->scrollframesize.width*1.717);

        background2->setScale(this->scrollframesize.width/background2->getContentSize().width);
        scrollView->addChild(background2);
    }
    
    int zones0 = UserDefault::getInstance()->getIntegerForKey("zones0", 0);
    if (zones0 == 0) {
        auto background1 = Sprite::create("res/mapback/7-12.png"); //here the background.png is a "red screen" png.
        background1->setPosition(this->scrollframesize.width/2, this->scrollframesize.width*1.013);
        
        background1->setScale(this->scrollframesize.width/background1->getContentSize().width);
        scrollView->addChild(background1);
    }
    
    //    float contentH = scrollView->getContentSize().height;
    //    float h = scrollView->getInnerContainerSize().height - contentH;
    //    float y = MIN(228+268*int((gCurrentStage-1)/3)-contentH/2, h);
    float z = 100.0f;
    if(lockLevel>0){
        ValueMap sdata = (arrLevels[lockLevel-1]).asValueMap();
        z =  sdata["z"].asFloat();
    } 
    
    
    //float scrollPos = 100 - y/420;//(scrollframesize.width*4.4 - y)*100/(scrollframesize.width*4.4);
    
    scrollView->jumpToPercentVertical(z);
    //scrollView->scrollToPercentVertical(70, 10, true);
    scrollView->setTag(TAG_MAP_SCROLL);
    this->addChild(scrollView);
}

void MapviewScene::showPos(){
    if(lockLevel<32){
        cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
        ValueMap sdata = (arrLevels[lockLevel]).asValueMap();
        float x =  sdata["x"].asFloat();
        float y =  sdata["y"].asFloat();
        
        auto footSpr = Sprite::create("res/levelicon.png"); //here the background.png is a "red screen" png.
        footSpr->setPosition(Vec2(scrollframesize.width * x/100.0f, scrollframesize.width *y/100.0f));
        footSpr->setTag(TAG_MAP_FOOTICON);
        footSpr->setAnchorPoint(Point(0.5f,0.1f));
        scrollView->addChild(footSpr);
        footSpr->setScale(scrollsize.width * 0.1/footSpr->getContentSize().width);
    }
    
}

void MapviewScene::onEnterTransitionDidFinish() {
    playMusic();
/*
    if(!enterFlag){
        enterFlag = true;
    } else{
        int insteadlevel = UserDefault::getInstance()->getIntegerForKey("lockLevel");
        int insCompletedLevel = UserDefault::getInstance()->getIntegerForKey("completedLevel");
        
        if(insCompletedLevel > completedLevel){
            int diff = insCompletedLevel - completedLevel;
            completedLevel = insCompletedLevel;
            changeButton(diff, insteadlevel);
        } else {
            changeButton(1, insteadlevel);
        }
    
        movePos(insteadlevel);
        
    }
*/
}
void MapviewScene::changeButton(int diff, int insteadlevel){
    cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
    
    for(int ii=0; ii<diff; ii++){
        ValueMap sdata1 = (arrLevels[completedLevel-1 - ii]).asValueMap();
        float xx =  sdata1["x"].asFloat();
        float yy =  sdata1["y"].asFloat();
        auto *button = (Button*)scrollView->getChildByTag(TAG_MAP_BUTTON+completedLevel-1 - ii);
        scrollView->removeChild(button);
        
        Button* button1;
        button1 = Button::create(StringUtils::format("res/levels_complete/%d.png", completedLevel -ii),
                                 StringUtils::format("res/levels_complete/%d_selected.png", completedLevel -ii));
        button1->setScale(this->scrollframesize.width * 0.18f/button1->getContentSize().width);
        button1->setPosition(Vec2(this->scrollframesize.width * xx / 100.0f, scrollframesize.width *yy/ 100.0f));
        button1->addTouchEventListener(CC_CALLBACK_2(MapviewScene::touchEvent, this, completedLevel- ii));
        button1->setTag(TAG_MAP_BUTTON+completedLevel-1 -ii);
        scrollView->addChild(button1);
        
        const char *levelstarString = StringUtils::format("level%dstar", completedLevel -ii).c_str();
        int starCount = UserDefault::getInstance()->getIntegerForKey(levelstarString, 0);
        
        auto starImage = Sprite::create(StringUtils::format("res/star_levels/%d.png", starCount)); //here the background.png is a "red screen" png.
        starImage->setPosition(Vec2(scrollframesize.width * xx / 100.0f, scrollframesize.width *(yy - 4.5)/ 100.0f));
        starImage->setScale(scrollframesize.width*0.15f/starImage->getContentSize().width);
        scrollView->addChild(starImage);       
        
    }
//    movePos(insteadlevel);

    
}



void MapviewScene::movePos(int targetlevel){
    if(lockLevel<32){
        cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
        auto footSpr = (Sprite*) scrollView->getChildByTag(TAG_MAP_FOOTICON);
        scrollView->removeChild(footSpr);
        
        
        ValueMap sdata = (arrLevels[lockLevel]).asValueMap();
        float x =  sdata["x"].asFloat();
        float y =  sdata["y"].asFloat();
        
        
        footSpr = Sprite::create("res/levelicon.png"); //here the background.png is a "red screen" png.
        footSpr->setPosition(Vec2(scrollframesize.width * x/100.0f, scrollframesize.width *y/100.0f));
        footSpr->setTag(TAG_MAP_FOOTICON);
        footSpr->setAnchorPoint(Point(0.5f,0.1f));
        scrollView->addChild(footSpr);
        footSpr->setScale(scrollsize.width * 0.1/footSpr->getContentSize().width);
        
        
        sdata = (arrLevels[targetlevel]).asValueMap();
        x =  sdata["x"].asFloat();
        y =  sdata["y"].asFloat();
        
        lockLevel = targetlevel;
        
        
        
        auto action_0 = MoveTo::create(0.4, Point(scrollframesize.width * x / 100.0f, scrollframesize.width *y/ 100.0f));
        footSpr->runAction(action_0);
        
    }
}

void MapviewScene::showLockLevelExplain(int level){
    auto lockLevel = level;
    
    cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
    scrollView->setTouchEnabled(false);
    onShowLevelFlag = false;
    showingLevel = true;
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
    
    auto levelBg = Sprite::create("res/locked/Level/Level_Screen.png");
    
    levelBg->setPosition(this->scrollframesize.width*3/2 , this->scrollframesize.height/2);
    levelBg->setScale(this->scrollframesize.width*0.9/levelBg->getContentSize().width);
    levelExplainLayer->addChild(levelBg);
    
    auto levelBgPos = levelBg->getPosition();
    if (lockLevel < 10) {
        auto levelTitle = Sprite::create(StringUtils::format("res/locked/Level/Level_Numbers/%d.png", level - 1));
        
        levelTitle->setPosition(levelBgPos.x, levelBgPos.y + this->scrollframesize.width * 0.002);
        levelTitle->setScale(this->scrollframesize.width*0.077/levelTitle->getContentSize().width);

        levelExplainLayer->addChild(levelTitle);
    } else {
        auto levelTitle = Sprite::create(StringUtils::format("res/locked/Level/Level_Numbers/%d.png", level % 10 - 1));
        
        levelTitle->setPosition(levelBgPos.x + this->scrollframesize.width * 0.035, levelBgPos.y + this->scrollframesize.width * 0.002);
        levelTitle->setScale(this->scrollframesize.width*0.077/levelTitle->getContentSize().width);

        levelExplainLayer->addChild(levelTitle);
        
        auto levelTitle2 = Sprite::create(StringUtils::format("res/locked/Level/Level_Numbers/%d.png", level / 10));
        
        levelTitle2->setPosition(levelBgPos.x - this->scrollframesize.width * 0.035, levelBgPos.y + this->scrollframesize.width * 0.002);
        levelTitle2->setScale(this->scrollframesize.width*0.077/levelTitle->getContentSize().width);

        levelExplainLayer->addChild(levelTitle2);
    }
    Button* buttonClose = Button::create("res/title/close.png", "res/title/close.png");
        
    buttonClose->setPosition(Vec2(levelBgPos.x + this->scrollframesize.width*0.36, levelBgPos.y + this->scrollframesize.width*0.198));
    buttonClose->addTouchEventListener(CC_CALLBACK_2(MapviewScene::onLevelCloseEvent, this, (int)2));
    buttonClose->setScale(this->scrollframesize.width * 0.06f/buttonClose->getContentSize().width);
    
    levelExplainLayer->addChild(buttonClose);
    
    
    auto action_1 = MoveTo::create(0.6, Point(- this->scrollframesize.width*1.0 , 0));
    auto move_ease_in = EaseElasticOut::create(action_1->clone());
//    auto action_2 = Sequence::create(action_0, action_1, NULL);
//    auto action_3 = RepeatForever::create(action_2);
    levelExplainLayer->runAction(move_ease_in);
}

void MapviewScene::showZoneExplain(int level){
    
    auto lockLevel = level;
    cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
    scrollView->setTouchEnabled(false);
    onShowLevelFlag = false;
    showingLevel = true;
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
    
    auto levelBg = Sprite::create("res/locked/Zone/Zone_Screen.png");
    
    levelBg->setPosition(this->scrollframesize.width*3/2 , this->scrollframesize.height/2);
    levelBg->setScale(this->scrollframesize.width*0.9/levelBg->getContentSize().width);
    levelExplainLayer->addChild(levelBg);
    
    auto levelBgPos = levelBg->getPosition();
    
    auto levelTitle = Sprite::create(StringUtils::format("res/locked/Zone/Zone_Numbers/%d-%d.png", lockLevel - 6, lockLevel - 1));
    
    levelTitle->setPosition(levelBgPos.x, levelBgPos.y + this->scrollframesize.width * 0.002);
    levelTitle->setScale(this->scrollframesize.width*0.095/levelTitle->getContentSize().height);

    levelExplainLayer->addChild(levelTitle);
    
    Button* buttonClose = Button::create("res/title/close.png", "res/title/close.png");
        
    buttonClose->setPosition(Vec2(levelBgPos.x + this->scrollframesize.width*0.36, levelBgPos.y + this->scrollframesize.width*0.198));
    buttonClose->addTouchEventListener(CC_CALLBACK_2(MapviewScene::onLevelCloseEvent, this, (int)2));
    buttonClose->setScale(this->scrollframesize.width * 0.06f/buttonClose->getContentSize().width);
    
    levelExplainLayer->addChild(buttonClose);
    
    
//    auto action_0 = MoveTo::create(0.4, Point(- this->scrollframesize.width*1.1 , 0));
    auto action_1 = MoveTo::create(0.6, Point(- this->scrollframesize.width*1.0 , 0));
    auto move_ease_in = EaseElasticOut::create(action_1->clone());
//    auto action_2 = Sequence::create(action_0, action_1, NULL);
//    auto action_3 = RepeatForever::create(action_2);
    levelExplainLayer->runAction(move_ease_in);
}

void MapviewScene::showLevelExplainacreen(int level){
    
    selectedLevel = level;
    // when levelexplainlayer appears, set touch event of scrollview to false.
    cocos2d::ui::ScrollView *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
    scrollView->setTouchEnabled(false);
    onShowLevelFlag = false;
    showingLevel = true;
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
    Button* buttonPlay = Button::create("res/title/Continue.png", "res/title/Continue_selected.png");
    
    buttonPlay->setPosition(Vec2(levelBgPos.x - this->scrollframesize.width*0.025, levelBgPos.y - this->scrollframesize.width*0.16));
    buttonPlay->addTouchEventListener(CC_CALLBACK_2(MapviewScene::onLevelCloseEvent, this, (int)1));
    buttonPlay->setScale(this->scrollframesize.width*0.18/buttonPlay->getContentSize().width);
    
    levelExplainLayer->addChild(buttonPlay);
    
    
    ValueMap sdata = (this->arrLevels[level-1]).asValueMap();
    int targetnumber =  sdata["targetnumber"].asInt();
    int targettime =  sdata["leveltime"].asInt();
    
    auto levelNumber = Sprite::create(StringUtils::format("res/title/number%d.png", targetnumber));
    levelNumber->setPosition(levelBgPos.x - this->scrollframesize.width*0.21, levelBgPos.y - this->scrollframesize.width*0.02);
    levelNumber->setScale(this->scrollframesize.width*0.08/levelNumber->getContentSize().width);
    
    levelExplainLayer->addChild(levelNumber);
    
    auto levelTime = Sprite::create(StringUtils::format("res/title/timer/timer%d.png", targettime));
    levelTime->setPosition(levelBgPos.x + this->scrollframesize.width*0.16, levelBgPos.y - this->scrollframesize.width*0.02);
    levelTime->setScale(this->scrollframesize.width*0.08/levelTime->getContentSize().width);
    
    if (targettime == 120) {
        levelTime->setScale(this->scrollframesize.width*0.14/levelTime->getContentSize().width);
    }
    
    levelExplainLayer->addChild(levelTime);
    
    // level close
    
    Button* buttonClose = Button::create("res/title/close.png", "res/title/close.png");
    
    buttonClose->setPosition(Vec2(levelBgPos.x + this->scrollframesize.width*0.285, levelBgPos.y + this->scrollframesize.width*0.19));
    buttonClose->addTouchEventListener(CC_CALLBACK_2(MapviewScene::onLevelCloseEvent, this, (int)2));
    buttonClose->setScale(this->scrollframesize.width * 0.06f/buttonClose->getContentSize().width);
    
    levelExplainLayer->addChild(buttonClose);
    
    
    auto action_0 = MoveTo::create(0.4, Point(- this->scrollframesize.width*1.1 , 0));
    auto action_1 = MoveTo::create(0.1, Point(- this->scrollframesize.width*0.95 , 0));
    auto action_2 = Sequence::create(action_0, action_1, NULL);
//    auto action_3 = RepeatForever::create(action_2);
    levelExplainLayer->runAction(action_2);
}


void MapviewScene::touchEvent(Ref *pSender, Widget::TouchEventType type, int d)
{
//    CCLOG("HelloWorld::setCallFunc_2() = %d", (int)d);
//    if(this->onShowLevelFlag && d<=(completedLevel+1)) {
//        this->showLevelExplainacreen(d);
//    }
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            
            break;
            
        case Widget::TouchEventType::MOVED:
            
            break;
            
        case Widget::TouchEventType::ENDED:
        {
            if (!showingLevel) {
                if(onShowLevelFlag && d <= lockLevel + 1) {
                    
                    showLevelExplainacreen(d);
                } else if (d == 7 || d == 13 || d == 19 || d == 25 || d == 31) {
                    showZoneExplain(d);
                } else {
                    showLockLevelExplain(d);
                }
            }
            break;
        }
            
        case Widget::TouchEventType::CANCELED:
            
            break;
            
        default:
            break;

    
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
    
    showingLevel = false;
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
        Director::getInstance()->replaceScene(gameScene);
//        Director::getInstance()->pushScene(gameScene);
        
    } else if(state == 2){
//        auto *scrollView = (cocos2d::ui::ScrollView*)this->getChildByTag(TAG_MAP_SCROLL);
//        scrollView->setTouchEnabled(true);
//        this->onShowLevelFlag = true;
    }
    auto *levelLayer = (Layer*)this->getChildByTag(TAG_MAP_LEVELLAYER);
    this->removeChild(levelLayer);

//    CCLOG("HelloWorld::setCallFunc_2()%d", state);
}



void MapviewScene::scheduleCallback(float delta)
{
    auto *levelLayer = (Layer*)this->getChildByTag(TAG_MAP_LEVELLAYER);
    this->removeChild(levelLayer);
}
