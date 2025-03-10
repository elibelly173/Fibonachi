//
//  GameScene.cpp
//  fibonachi-cpp
//
//  Created by Future on 2/18/17.
//
//

#include "GameScene.h"
#include "MapviewScene.h"
#include "FractionLayer.h"
#include "FractionAnswerLayer.h"

using namespace ui;


Scene* GameScene::createScene(int level)
{
    // 'scene' is an autorelease object
    UserDefault::getInstance()->setIntegerForKey("Level",level);
    
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    if (level > 32)
        level = 32;
    
    level =UserDefault::getInstance()->getIntegerForKey("Level");
    screenSize = Director::getInstance()->getWinSize();
    
    completedLevel =UserDefault::getInstance()->getIntegerForKey("completedLevel");
    lockLevel = UserDefault::getInstance()->getIntegerForKey("lockLevel");

    getLevelInfo();
    
    initFlags();
    getLevelProblems();
    initScreen();
    initFiboAchi();
    initProAns();
    initanswerLayer();
    initTimerScore();
    initTicks();
    initKey();
    initButtons();

    
    playMusic();


    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
/**/
    this->schedule(schedule_selector(GameScene::UpdateTimer), 0.1f);
    this->scheduleUpdate();
    return true;
}

void GameScene::playMusic(){
    audio= CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("res/music/map.mp3", false);
}



void GameScene::initFlags() {
    
    if(level>19 && level<23){
        fractionFlag = 1;
    } else if(level==23){
        fractionFlag =2;
    } else if(level > 23 && level<=24){
        fractionFlag =3;
    } else if(level > 24 && level<30){
        fractionFlag =4;
    } else if(level == 30){
        fractionFlag = 1;
        deciamlFlag = true;
    } else if(level == 32) {
        fractionFlag = 0;
        deciamlFlag = true;
    } else {
        fractionFlag = 0;
    }
    
    if ((level >= 12) && (level != 17) && (level != 19) && (level != 20) && (level < 24)) {
        addKeyFlag = true;
    }
    
    switch(level){
        case 21:
            axisFlag = 1;
            break;
        case 22:
            axisFlag = 2;
            break;
        case 23: case 31:
            axisFlag = 3;
            break;
        default:
            axisFlag = 0;
            break;
    }
    
    tapenteranimFlag = UserDefault::getInstance()->getIntegerForKey("tapenteranimFlag");
    bool swipeflag = UserDefault::getInstance()->getIntegerForKey("swipeflag");
    if(tapenteranimFlag && !swipeflag && level < 4) {
        tapentertimeFlag = true;
    }

    level20animFlag = UserDefault::getInstance()->getIntegerForKey("level20animFlag");
    level21animFlag = UserDefault::getInstance()->getIntegerForKey("level21animFlag");
    
//    level20animFlag = true;
//    level21animFlag = false;
    
    
}

void GameScene::addTick(int order){
    if(order<targetnumber){
//        ValueMap sdata = (arrTicks[order]).asValueMap();
//        float x =  sdata["x"].asFloat();
//        float y =  sdata["y"].asFloat();
//        float w =  sdata["w"].asFloat();
//        float h =  sdata["h"].asFloat();
        auto tick1spr = Sprite::create(StringUtils::format("res/tree%d/tick%d.png",targetnumber, (order + 1)));
        tick1spr->setPosition(screenSize.width, screenSize.height);
        tick1spr->setAnchorPoint(Point(1.0f,1.0f));
        tick1spr->setScale(screenSize.width*0.174/tick1spr->getContentSize().width, screenSize.height*0.712/tick1spr->getContentSize().height);
        this->addChild(tick1spr);
        
    }
    
}


void GameScene::initTicks(){
    ValueMap data;
    std::string path = FileUtils::getInstance()->fullPathForFilename("res/plist/ticks.plist");
    data = FileUtils::getInstance()->getValueMapFromFile(path);
    arrTicks = data.at("ticks").asValueVector();
}




void GameScene::initScreen(){
    auto background = Sprite::create("gameboard.png");
    background->setPosition(screenSize.width/2, screenSize.height/2);
    this->addChild(background);
    background->setScale(screenSize.width/background->getContentSize().width, screenSize.height/background->getContentSize().height);
    
    
    auto cloudBg = Sprite::create("res/game/cloud.png");
    cloudBg->setPosition(screenSize.width*0.25, screenSize.height*0.71);
    this->addChild(cloudBg);
    cloudBg->setScale(screenSize.width*0.33/cloudBg->getContentSize().width, screenSize.height*0.35/cloudBg->getContentSize().height);
       
    auto scoreImg = Sprite::create("res/game/Score.png");
    scoreImg->setPosition(screenSize.width/2, screenSize.height);
    scoreImg->setAnchorPoint(Point(0.5f,1.0f));
    this->addChild(scoreImg);
    scoreImg->setScale(screenSize.width*0.2/scoreImg->getContentSize().width);
    
    auto treeImg = Sprite::create(StringUtils::format("res/tree%d/tree.png", targetnumber));
    treeImg->setPosition(screenSize.width, screenSize.height);
    treeImg->setAnchorPoint(Point(1.0f,1.0f));
    this->addChild(treeImg);
    treeImg->setScale(screenSize.width*0.345/treeImg->getContentSize().width, screenSize.height*0.868/treeImg->getContentSize().height);
}

void GameScene::initFiboAchi(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/achianim/achianim.plist");
    
    auto achispr = Sprite::createWithSpriteFrameName("achiAnim1.png");
    achispr->setTag(TAG_SPRITE_ACHI);
    achispr->setPosition(screenSize.width*0.30, screenSize.height*0.2);
    achispr->setAnchorPoint(Point(1.0f,0.0f));
    achispr->setScale(screenSize.width*0.22/achispr->getContentSize().width);
    this->addChild(achispr);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/fibo/fibo.plist");
    auto fibospr = Sprite::createWithSpriteFrameName("fibo0.png");
    fibospr->setTag(TAG_SPRITE_FIBO);
    fibospr->setPosition(screenSize.width*0.63, screenSize.height*0.19);
    fibospr->setAnchorPoint(Point(0.0f,0.0f));
    fibospr->setScale(screenSize.width*0.15/achispr->getContentSize().width);
    this->addChild(fibospr);


    
}

void GameScene::achianim(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/achianim/achianim.plist");
    
    auto spr = (Sprite*)this->getChildByTag(TAG_SPRITE_ACHI);
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.08);
    
    for (int i = 0; i<10; i++) {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("achiAnim%d.png", i+1));
        animation->addSpriteFrame(frame);
    }
    
    auto animate = Animate::create(animation);
    spr->runAction(animate);
    AnimEnd();
}

void GameScene::fiboanim(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/fibo/fibo.plist");
    
    auto spr = (Sprite*)this->getChildByTag(TAG_SPRITE_FIBO);
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.05);
    
    for (int i = 0; i<14; i++) {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("fibo%d.png", i));
        animation->addSpriteFrame(frame);
    }
    
    auto animate = Animate::create(animation);
    spr->runAction(animate);
}

void GameScene::getLevelProblems(){
    
    ValueMap data;
    if(level == 11){
        for(int ii= 1; ii< 11; ii++){
            ValueVector levelProblems;
            std::string path = FileUtils::getInstance()->fullPathForFilename(StringUtils::format("res/plist/level%d.plist", ii));
            data = FileUtils::getInstance()->getValueMapFromFile(path);
            levelProblems = data.at("anspro").asValueVector();
            auto problemSize = levelProblems.size();
            for(int jj = 0; jj< 5; jj++){
                int randomnumber = arc4random()%((problemSize - 1) - 0) - 0;
                auto sdata = levelProblems[randomnumber];
                arrLevelsProblems.push_back(sdata);
            }
        }
    } else if(level == 16){
        for(int ii= 1; ii< 16; ii++){
            if(ii == 1 || ii == 2 || ii == 3 || ii == 7 || ii == 8 || ii == 14 || ii == 15) {
                ValueVector levelProblems;
                std::string path = FileUtils::getInstance()->fullPathForFilename(StringUtils::format("res/plist/level%d.plist", ii));
                data = FileUtils::getInstance()->getValueMapFromFile(path);
                levelProblems = data.at("anspro").asValueVector();
                auto problemSize = levelProblems.size();
                for(int jj = 0; jj< 5; jj++){
                    int randomnumber = arc4random()%((problemSize - 1) - 0) - 0;
                    auto sdata = levelProblems[randomnumber];
                    arrLevelsProblems.push_back(sdata);
                }
            }
        }
    } else if(level == 30){
        std::string path = FileUtils::getInstance()->fullPathForFilename(StringUtils::format("res/plist/level%d.plist", this->level));
        data = FileUtils::getInstance()->getValueMapFromFile(path);
        arrLevelsProblems = data.at("anspro").asValueVector();
        
        for(int ii= 1; ii< 4; ii++){
//            if(ii == 1) {
                ValueVector levelProblems;
                std::string path = FileUtils::getInstance()->fullPathForFilename(StringUtils::format("res/plist/level30_%d.plist", ii));
                data = FileUtils::getInstance()->getValueMapFromFile(path);
                levelProblems = data.at("anspro").asValueVector();
                auto problemSize = levelProblems.size();
                for(int jj = 0; jj< 5; jj++){
                    int randomnumber = arc4random()%((problemSize - 1) - 0) - 0;
                    auto sdata = levelProblems[randomnumber];
                    arrLevelsProblems.push_back(sdata);
                }
//            }
        }

    }
    else {
        std::string path = FileUtils::getInstance()->fullPathForFilename(StringUtils::format("res/plist/level%d.plist", this->level));
        data = FileUtils::getInstance()->getValueMapFromFile(path);
        arrLevelsProblems = data.at("anspro").asValueVector();
    }
    
//    ValueMap data1;
//    std::string path1 = FileUtils::getInstance()->fullPathForFilename("res/plist/levels.plist");
//    data1 = FileUtils::getInstance()->getValueMapFromFile(path1);
//    auto arrLevels = data1.at("levels").asValueVector();
//    ValueMap sdata = (arrLevels[level-1]).asValueMap();
//    targettime =  sdata["targettime"].asInt();
    
}

void GameScene::initKey(){
    
    if(axisFlag == 0){
        for(int ii=0; ii<10; ii++){
            Button* keyButton = Button::create(StringUtils::format("res/key/key%d.png", (ii + 1)),
                                               StringUtils::format("res/key/key%d_selected.png", (ii + 1)));
            keyButton->setPosition(Vec2(screenSize.width*0.05+screenSize.width*ii/10, screenSize.height*0.04f));
            keyButton->setAnchorPoint(Point(0.5f,0.0f));
            keyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
            keyButton->setTag(TAG_GAME_KEY+ii);
            keyButton->setScale(screenSize.width * 0.07f/keyButton->getContentSize().width);
            
            this->addChild(keyButton);
        }
        
        if(addKeyFlag){
            Button* addKeyButton = Button::create("res/key/negative.png", "res/key/negative_selected.png");
            
            addKeyButton->setPosition(Vec2(screenSize.width*0.045, screenSize.height*0.08f + screenSize.width * 0.18f));
            addKeyButton->setAnchorPoint(Point(0.5f,0.0f));
            addKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
            addKeyButton->setTag(TAG_GAME_KEYADD);
            addKeyButton->setScale(screenSize.width * 0.07f/addKeyButton->getContentSize().width);
            this->addChild(addKeyButton);
        }
        
        if ((fractionFlag>0) && (level != 30)) {
            Button* fractionKeyButton = Button::create("res/key/divide.png", "res/key/divide_selected.png");
            fractionKeyButton->setPosition(Vec2(screenSize.width*0.045, screenSize.height*0.08 + screenSize.width * 0.18));
            fractionKeyButton->setAnchorPoint(Point(0.5f,0.0f));
            fractionKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
            fractionKeyButton->setTag(TAG_GAME_KEYFRACTION);
            fractionKeyButton->setScale(screenSize.width * 0.07/fractionKeyButton->getContentSize().width);
            this->addChild(fractionKeyButton);
        }
        
        if(deciamlFlag){
            Button* deciamlButton = Button::create("res/key/decimal.png", "res/key/decimal_selected.png");
            deciamlButton->setPosition(Vec2(screenSize.width*0.045, screenSize.height*0.08 + screenSize.width * 0.18));
            deciamlButton->setAnchorPoint(Point(0.5f,0.0f));
            deciamlButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
            deciamlButton->setTag(TAG_GAME_KEYDECIMAL);
            deciamlButton->setScale(screenSize.width * 0.07f/deciamlButton->getContentSize().width);
            this->addChild(deciamlButton);
        }
    } else if(axisFlag == 1 || axisFlag == 2){
/*
        Button* lineButton = Button::create(StringUtils::format("res/key/numberline%d.png", axisFlag), StringUtils::format("res/key/numberline%d.png", axisFlag));
        lineButton->setTag(TAG_GAME_KEYNUMBERLINE1);
        lineButton->setPosition(Vec2(screenSize.width*0.5, screenSize.height*0.03));
        lineButton->setAnchorPoint(Point(0.5f,0.0f));
    lineButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));       lineButton->setScale(screenSize.width*0.9/lineButton->getContentSize().width);
        this->addChild(lineButton);
*/
        
        auto numberline1Spr = Sprite::Sprite::create(StringUtils::format("res/key/numberline%d.png", axisFlag));
        numberline1Spr->setTag(TAG_GAME_KEYNUMBERLINE1);
        numberline1Spr->setPosition(screenSize.width*0.5, screenSize.height*0.03);
        numberline1Spr->setAnchorPoint(Point(0.5f,0.0f));
        numberline1Spr->setScale(screenSize.width*0.9/numberline1Spr->getContentSize().width);
        this->addChild(numberline1Spr);
        
    } else if(axisFlag == 3){
                
        Button* equalKeyButton = Button::create("res/key/equal.png", "res/key/equal_selected.png");
        equalKeyButton->setPosition(Vec2(screenSize.width*0.96, screenSize.height*0.08f + screenSize.width * 0.08f));
        equalKeyButton->setAnchorPoint(Point(0.5f,0.0f));
        equalKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        equalKeyButton->setTag(TAG_GAME_KEYEQUAL);
        equalKeyButton->setScale(screenSize.width * 0.06f/equalKeyButton->getContentSize().width);
        this->addChild(equalKeyButton);
        
        Button* bigKeyButton = Button::create("res/key/right.png", "res/key/right_selected.png");
        bigKeyButton->setPosition(Vec2(screenSize.width*0.96, screenSize.height*0.08f + screenSize.width * 0.18f));
        bigKeyButton->setAnchorPoint(Point(0.5f,0.0f));
        bigKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        bigKeyButton->setTag(TAG_GAME_KEYBIG);
        bigKeyButton->setScale(screenSize.width * 0.06f/bigKeyButton->getContentSize().width);
        this->addChild(bigKeyButton);
        
        Button* smallKeyButton = Button::create("res/key/left.png", "res/key/left_selected.png");
        smallKeyButton->setPosition(Vec2(screenSize.width*0.96, screenSize.height*0.08f + screenSize.width * 0.28f));
        smallKeyButton->setAnchorPoint(Point(0.5f,0.0f));
        smallKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        smallKeyButton->setTag(TAG_GAME_KEYSMALL);
        smallKeyButton->setScale(screenSize.width * 0.06f/smallKeyButton->getContentSize().width);
        this->addChild(smallKeyButton);
        
    }
}

void GameScene::initButtons(){

    Button* homeButton = Button::create("res/game/home.png", "res/game/home_selected.png");
    homeButton->setPosition(Vec2(screenSize.width*0.05, screenSize.height*0.93));
    homeButton->addTouchEventListener(CC_CALLBACK_2(GameScene::gotoHome, this));
    homeButton->setScale(screenSize.width * 0.075f/homeButton->getContentSize().width);
    this->addChild(homeButton);
    
    if (axisFlag == 0) {
        Button* enterButton = Button::create("res/game/Enter.png", "res/game/Enter_selected.png");
        enterButton->setPosition(Vec2(screenSize.width*0.84, screenSize.height*0.25));
        enterButton->addTouchEventListener(CC_CALLBACK_2(GameScene::gotoEnter, this));
        enterButton->setScale(screenSize.width * 0.08f/enterButton->getContentSize().width);
        this->addChild(enterButton);
        
        Button* deleteButton = Button::create("res/game/Delete.png", "res/game/Delete_selected.png");
        deleteButton->setPosition(Vec2(screenSize.width*0.06, screenSize.height*0.25));
        deleteButton->addTouchEventListener(CC_CALLBACK_2(GameScene::gotoDelete, this));
        deleteButton->setScale(screenSize.width * 0.08f/deleteButton->getContentSize().width);
        this->addChild(deleteButton);

    }

    Button* settingButton = Button::create("res/game/Settings.png", "res/game/Settings_selected.png");
    settingButton->setPosition(Vec2(screenSize.width*0.95, screenSize.height*0.93));
    settingButton->addTouchEventListener(CC_CALLBACK_2(GameScene::gotoHome, this));
    settingButton->setScale(screenSize.width * 0.05f/settingButton->getContentSize().width);
    this->addChild(settingButton);

}

void GameScene::initProAns(){
    if(fractionFlag>0){
        auto problemImg = Sprite::create("res/game/question1.png"); //here the background.png is a "red screen" png.
        problemImg->setPosition(screenSize.width*0.27, screenSize.height*0.215 + screenSize.width*0.08);
        problemImg->setAnchorPoint(Point(0.0f,0.0f));
        this->addChild(problemImg);
        problemImg->setScale(screenSize.width*0.27/problemImg->getContentSize().width);
        
        if(axisFlag !=0){
        } else {
            auto answerImg = Sprite::create("res/game/Answer Bubble_Large.png"); //here the background.png is a "red screen" png.
            answerImg->setPosition(screenSize.width*0.75, screenSize.height*0.36 + screenSize.width*0.08);
            answerImg->setOpacity(0);
            answerImg->setAnchorPoint(Point(1.0f,0.3f));
            answerImg->setTag(TAG_GAME_ANSWERIMG);
            
            answerImg->setScale(screenSize.width*0.15/answerImg->getContentSize().width);
            auto action_0 = ScaleTo::create(0.0f, 0.0f);
            auto callback = CallFunc::create( [this]() {
                auto spr = (Sprite*)this->getChildByTag(TAG_GAME_ANSWERIMG);
                spr->setOpacity(255);
            });
            auto sequence = Sequence::create(action_0, callback, NULL);
            answerImg->runAction(sequence);
//            answerImg->runAction(action_0);
            
            this->addChild(answerImg);
        }
    } else {
        auto problemImg = Sprite::create("res/game/problem.png"); //here the background.png is a "red screen" png.
        problemImg->setPosition(screenSize.width*0.27, (screenSize.height*0.21 + screenSize.width*0.08));
        problemImg->setAnchorPoint(Point(0.0f,0.0f));
        this->addChild(problemImg);
        problemImg->setScale(screenSize.width*0.27/problemImg->getContentSize().width);
        
        if (level != 31) {
            auto answerImg = Sprite::create("res/game/Answer Bubble_Small.png"); //here the background.png is a "red screen" png.
            answerImg->setPosition(screenSize.width*0.75, screenSize.height*0.37 + screenSize.width*0.08);
            answerImg->setOpacity(0);
            answerImg->setAnchorPoint(Point(1.0f,0.3f));
            answerImg->setTag(TAG_GAME_ANSWERIMG);
            
            answerImg->setScale(screenSize.width*0.15/answerImg->getContentSize().width);
            auto action_0 = ScaleTo::create(0.0f, 0.0f);
            auto callback = CallFunc::create( [this]() {
                auto spr = (Sprite*)this->getChildByTag(TAG_GAME_ANSWERIMG);
                spr->setOpacity(255);
            });
            auto sequence = Sequence::create(action_0, callback, NULL);
            answerImg->runAction(sequence);
//            answerImg->runAction(action_0);
            this->addChild(answerImg);
        }

    }
    
    this->makeproblem();
    this->makeproblem();
}

void GameScene::initTimerScore(){
//    auto timerLabel = Label::createWithSystemFont("0", "Yesterday Dream", screenSize.width*0.035);
//    timerLabel->setColor(Color3B::GREEN);
//    timerLabel->setPosition(screenSize.width*0.28, screenSize.height - screenSize.width*0.047);
//    timerLabel->setTag(TAG_GAME_TIMER);
//    this->addChild(timerLabel);
//    answerImg->getContentSize().width
    
    auto dialCircle = Sprite::create("res/timer/Dial Circle.png");
    dialCircle->setPosition(screenSize.width*0.2, screenSize.height - screenSize.width*0.038);
    dialCircle->setScale(screenSize.width*0.00035);
    this->addChild(dialCircle);
    
//    float Radius = screenSize.width*0.03;
//    float coef = 0.0174533;
//    for ( int i = 0 ; i < 360; i ++) {
//        float rads = (359 - i) * coef; // radians
//        Circle [i] .y = Radius * cosf (rads); //vertex x
//        Circle [i] .x = Radius * sinf (rads); //vertex y
//    }
//    Circle[0].y = 0;
//
//    DrawNode *draw = DrawNode::create();
//    draw-> drawPolygon (Circle, 360, Color4F::BLACK, 0 , Color4F::BLACK);
//    draw->setPosition(screenSize.width*0.2, screenSize.height - screenSize.width*0.038);
//    draw->setTag(TAG_GAME_CIRCLE);
//    this->addChild(draw);
    
    auto greenCircle = Sprite::create("res/timer/Blue.png");
    greenCircle->setPosition(screenSize.width*0.2, screenSize.height - screenSize.width*0.038);
    greenCircle->setScale(screenSize.width*0.00035);
    greenCircle->setTag(TAG_GAME_TIMER);
    this->addChild(greenCircle);
    
    auto dialLine = Sprite::create("res/timer/Dial Lines.png");
    dialLine->setPosition(screenSize.width*0.2, screenSize.height - screenSize.width*0.038);
    dialLine->setScale(screenSize.width*0.00035);
    this->addChild(dialLine);
    
    auto dial = Sprite::create("res/timer/Dial.png");
    dial->setPosition(screenSize.width*0.2, screenSize.height - screenSize.width*0.038);
    dial->setAnchorPoint(Point(screenSize.width*0.00038, screenSize.width*0.0001));
    dial->setScale(screenSize.width*0.00042);
    dial->setTag(TAG_GAME_CIRCLE);
    this->addChild(dial);
    
    auto scoreLabel = Label::createWithSystemFont("", "Yesterday Dream", screenSize.width*0.035);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setPosition(screenSize.width*0.5, screenSize.height - screenSize.width*0.06);
    scoreLabel->setTag(TAG_GAME_SCORE);
    this->addChild(scoreLabel);
    
    
    auto levelLabel = Label::createWithSystemFont(StringUtils::format("%d", level), "Yesterday Dream", screenSize.width*0.035);
    levelLabel->setColor(Color3B::BLACK);
    levelLabel->setPosition(screenSize.width*0.75, screenSize.height - screenSize.width*0.047);
    levelLabel->setTag(TAG_GAME_LEVEL);
    this->addChild(levelLabel);
}


void GameScene::update(float delta)
{
    problemTime+=delta;
    musicTime += delta;
    
//    if(startingTapFlag && !tapenteranimFlag && !levelCompleteFlag) {
//        waittingTaptimer += delta;
//    }
//
//    if(waittingTaptimer > 2 && !tapenteranimFlag) {
//        onTapAnimation();
//    }
//    if(onkeyswipeFlag && !levelCompleteFlag){
//        taptimer+=delta;
//    }
//
//    if(taptimer > 2 && tapentertimeFlag && onkeyswipeFlag){
//        taptimer = 0;
//        UserDefault::getInstance()->setIntegerForKey("swipeflag", true);
//        onSwipeAnimation();
//    }
    
    if(holdFlag){
        if(holdTime>0.4 ){
            holdTime = 0.0f;
            holdCount++;
            holdpreVal = holdnowVal;
            showDecimalAnswer(holdnowVal);
        } else {
            holdTime+= delta;
        }
    } else {
        holdTime = 0.0f;
    }
    
    if(musicTime>5.25 && !audioFlag){
        audioFlag = true;
        audio->stopBackgroundMusic();
        audio->setBackgroundMusicVolume(0.6);
        audio->playBackgroundMusic("res/music/body.mp3", true);
    }
    
    
}

void GameScene::UpdateTimer(float dt)
{
    if(firstEnterFlag && !levelCompleteFlag && !dimFlag){
        timer+=1;
        auto dial = (Sprite*)this->getChildByTag(TAG_GAME_CIRCLE);
        dial->setRotation(36 * timer / leveltime);
        auto timerLabel = (Sprite*)this->getChildByTag(TAG_GAME_TIMER);
        if(timer <= targettime1 * 10) {
//            draw-> drawPolygon (Circle, 360 - timer * 12 / targettime1, Color4F::BLACK, 0 , Color4F::BLACK);
        }
        else if(timer > targettime1 * 10 && timer < targettime * 10){
            timerLabel->setTexture("res/timer/Green.png");
//            draw-> drawPolygon (Circle, 240 - (timer - targettime1 * 10) * 12 / (leveltime - targettime1), Color4F::BLACK, 0 , Color4F::BLACK);
        } else if(timer > targettime * 10 && timer < leveltime * 10){
            timerLabel->setTexture("res/timer/Yellow.png");
//            draw-> drawPolygon (Circle, 240 - (timer - targettime1 * 10) * 12 / (leveltime - targettime1), Color4F::BLACK, 0 , Color4F::BLACK);
        } else if(timer >= leveltime * 10){
            timerLabel->setTexture("res/timer/Red.png");
//            draw-> drawPolygon (Circle, 120 - (timer - leveltime * 10) * 12 / (targettime2 - leveltime) > 2 ? 120 - (timer - leveltime * 10) * 12 / (targettime2 - leveltime) : 3, Color4F::BLACK, 0 , Color4F::BLACK);
        }
//        timerLabel->setString(StringUtils::format("%1.1f", timer/10.0f));
    }
    
    
    if(!level20animFlag && level==20){
        level20animFlag = true;
        UserDefault::getInstance()->setIntegerForKey("level20animFlag", true);
        onCancelFrAnim();
    }
    
    if(!level21animFlag && level==21){
        level21animFlag = true;
        UserDefault::getInstance()->setIntegerForKey("level21animFlag", true);
        onNlineAnim();
    }
    
    
}
void GameScene::onShowDimLayer(){
    dimFlag = true;
    
    CCLayerColor *dimLayer = CCLayerColor::create(ccc4(0,0,0,170));
    dimLayer->setTag(TAG_GAME_DIMLAYER);
    this->addChild(dimLayer);
}

void GameScene::onRemoveDimLayer(){
    dimFlag = false;
    auto dimLayer = (CCLayerColor*)this->getChildByTag(TAG_GAME_DIMLAYER);
    this->removeChild(dimLayer);
}


void GameScene::onTapAnimation(){
    tapenteranimFlag = true;
    UserDefault::getInstance()->setIntegerForKey("tapenteranimFlag", true);
    
    onShowDimLayer();
    onshowedTapAnimFlag = true;
    auto tapAnimTitle = Sprite::create("res/animation/tapimage.png");
    tapAnimTitle->setTag(TAG_GAME_TAPSPR);
    tapAnimTitle->setPosition(screenSize.width*0.65, screenSize.height*0.16 + screenSize.width*0.35);
    tapAnimTitle->setScale(screenSize.width*0.25/tapAnimTitle->getContentSize().width);
    this->addChild(tapAnimTitle);
    
    auto tapAnimhand = Sprite::create("res/animation/taphand.png");
    tapAnimhand->setTag(TAG_GAME_TAPANIM);
    tapAnimhand->setScale(screenSize.width*0.13/tapAnimhand->getContentSize().width);
    tapAnimhand->setAnchorPoint(Vec2(0.8, 0));
    this->addChild(tapAnimhand);
    
    if(fractionFlag>0 && !deciamlFlag){
        tapAnimhand->setPosition(screenSize.width*0.78, screenSize.height*0.16 + screenSize.width*0.12);
    } else if(fractionFlag>0 && deciamlFlag){
        tapAnimhand->setPosition(screenSize.width*0.78, screenSize.height*0.16 + screenSize.width*0.12);
    } else {
        tapAnimhand->setPosition(screenSize.width*0.78, screenSize.height*0.16 + screenSize.width*0.07);
    }
    
    auto action_0 = RotateTo::create(1.2f, -15.0f);
    auto action_1 = RotateTo::create(1.2f, 15.0f);
    auto action_2 = Sequence::create(action_0, action_1, NULL);
    auto action_3 = RepeatForever::create(action_2);
    tapAnimhand->runAction(action_3);
}

void GameScene::removeTapAnimation(){
    onRemoveDimLayer();
    onshowedTapAnimFlag = false;
    tapentertimeFlag = true;
    auto tapAnimTitle = (Sprite*)this->getChildByTag(TAG_GAME_TAPSPR);
    this->removeChild(tapAnimTitle);
    
    auto tapAnimhand =(Sprite*)this->getChildByTag(TAG_GAME_TAPANIM);
    this->removeChild(tapAnimhand);
}


void GameScene::onSwipeAnimation(){
    onShowDimLayer();
    onshowedSwipeAnimFlag = true;
    tapentertimeFlag = false;
    auto swipeAnimTitle = Sprite::create("res/animation/swipedelete.png");
    swipeAnimTitle->setPosition(screenSize.width*0.65, screenSize.height*0.16 + screenSize.width*0.35);
    swipeAnimTitle->setTag(TAG_GAME_SWIPESPR);
    swipeAnimTitle->setScale(screenSize.width*0.25/swipeAnimTitle->getContentSize().width);
    this->addChild(swipeAnimTitle);
    
    auto swipeAnimhand = Sprite::create("res/animation/hand.png");
    swipeAnimhand->setTag(TAG_GAME_SWIPEANIM);
    swipeAnimhand->setScale(screenSize.width*0.13/swipeAnimhand->getContentSize().width);
    swipeAnimhand->setAnchorPoint(Vec2(0.5, 1));
    this->addChild(swipeAnimhand);
    
    float pos = 0.0f;
    
    if(fractionFlag>0){
        swipeAnimhand->setPosition(screenSize.width*0.66, screenSize.height*0.16 + screenSize.width*0.195);
        pos =screenSize.height*0.16 + screenSize.width*0.195;
    } else {
        swipeAnimhand->setPosition(screenSize.width*0.66, screenSize.height*0.16 + screenSize.width*0.145);
        pos =screenSize.height*0.16 + screenSize.width*0.145;
    }
    
    auto action_0 = MoveTo::create(1.2, Point(screenSize.width*0.77, pos));
    auto action_1 = MoveTo::create(1.2, Point(screenSize.width*0.66, pos));
    auto action_2 = Sequence::create(action_0, action_1, NULL);
    auto action_3 = RepeatForever::create(action_2);
    swipeAnimhand->runAction(action_3);
}


void GameScene::removeSwipeAnimation(){
    onRemoveDimLayer();
    onshowedSwipeAnimFlag = false;
    auto swipeAnimTitle = (Sprite*)this->getChildByTag(TAG_GAME_SWIPESPR);
    this->removeChild(swipeAnimTitle);
    
    auto swipeAnimhand =(Sprite*)this->getChildByTag(TAG_GAME_SWIPEANIM);
    this->removeChild(swipeAnimhand);
}




void GameScene::onCancelFrAnim(){
    onShowDimLayer();
    onshowedCancelFrAnimFlag = true;
    auto canFrAnimTitle = Sprite::create("res/animation/cancelfraction.png");
    canFrAnimTitle->setPosition(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.3);
    canFrAnimTitle->setTag(TAG_GAME_CANCELFRSPR);
    canFrAnimTitle->setScale(screenSize.width*0.35/canFrAnimTitle->getContentSize().width);
    this->addChild(canFrAnimTitle);
    
    auto canFrAnimhand1 = Sprite::create("res/animation/left_hand.png");
    canFrAnimhand1->setTag(TAG_GAME_CANCELFRANIM1);
    canFrAnimhand1->setScale(screenSize.width*0.11/canFrAnimhand1->getContentSize().width);
    canFrAnimhand1->setAnchorPoint(Vec2(1, 1));
    this->addChild(canFrAnimhand1);
    
    float pos1 = 0.0f;
    
    canFrAnimhand1->setPosition(screenSize.width*0.3, screenSize.height*0.16 + screenSize.width*0.19);
    pos1 =screenSize.height*0.16 + screenSize.width*0.19;
    
    auto action_4 = MoveTo::create(1.2, Point(screenSize.width*0.4, pos1));
    auto action_5 = MoveTo::create(1.2, Point(screenSize.width*0.3, pos1));
    auto action_6 = Sequence::create(action_4, action_5, NULL);
    auto action_7 = RepeatForever::create(action_6);
    canFrAnimhand1->runAction(action_7);
}

void GameScene::removeCancelFrAnim(){
    onRemoveDimLayer();
    onshowedCancelFrAnimFlag = false;
    auto canFrAnimTitle = (Sprite*)this->getChildByTag(TAG_GAME_CANCELFRSPR);
    this->removeChild(canFrAnimTitle);
    
    auto canFrAnimhand =(Sprite*)this->getChildByTag(TAG_GAME_CANCELFRANIM1);
    this->removeChild(canFrAnimhand);
    onTapFrAnim();
}



void GameScene::onTapFrAnim(){
    onShowDimLayer();
    onshowedTapFrAnimFlag = true;
    auto tapFrAnimTitle = Sprite::create("res/animation/Fraction.png");
    tapFrAnimTitle->setPosition(screenSize.width*0.65, screenSize.height*0.16 + screenSize.width*0.35);
    tapFrAnimTitle->setTag(TAG_GAME_TAPFRSPR);
    tapFrAnimTitle->setScale(screenSize.width*0.35/tapFrAnimTitle->getContentSize().width);
    this->addChild(tapFrAnimTitle);
    
    auto tapFrAnimhand = Sprite::create("res/animation/left_hand.png");
    tapFrAnimhand->setTag(TAG_GAME_TAPFRANIM);
    tapFrAnimhand->setScale(screenSize.width*0.11/tapFrAnimhand->getContentSize().width);
    tapFrAnimhand->setAnchorPoint(Vec2(1, 1));
    this->addChild(tapFrAnimhand);
    
    float pos = 0.0f;
    
    tapFrAnimhand->setPosition(screenSize.width*0.85, screenSize.height*0.08 + screenSize.width * 0.16);
    pos =screenSize.height*0.08 + screenSize.width * 0.16;
    
    auto action_0 = MoveTo::create(1.2, Point(screenSize.width*0.95, pos));
    auto action_1 = MoveTo::create(1.2, Point(screenSize.width*0.85, pos));
    auto action_2 = Sequence::create(action_0, action_1, NULL);
    auto action_3 = RepeatForever::create(action_2);
    tapFrAnimhand->runAction(action_3);
    
}

void GameScene::removeTapFrAnim(){
    onRemoveDimLayer();
    onshowedTapFrAnimFlag = false;
    auto tapFrAnimTitle = (Sprite*)this->getChildByTag(TAG_GAME_TAPFRSPR);
    this->removeChild(tapFrAnimTitle);
    
    auto tapFrAnimhand =(Sprite*)this->getChildByTag(TAG_GAME_TAPFRANIM);
    this->removeChild(tapFrAnimhand);
}


void GameScene::onOneByOneAnimation(){
    onShowDimLayer();
    
//    if(fractionFlag>0 && !deciamlFlag){
//        std::stringstream test(StringUtils::format("%s", answerArray[rightCount].c_str()));
//        std::string segment;
//        std::vector<std::string> seglist;
//
//        while(std::getline(test, segment, '/'))
//        {
//            seglist.push_back(segment);
//        }
//        answer = 1;
//        showFractionAnswer(atoi(seglist[0].c_str()));
//        onClickDividerKey();
//        showFractionAnswer(atoi(seglist[1].c_str()));
//
//    } else if(deciamlFlag){
//        answer = 1;
//        showDecimalAnswer1(answerArray[rightCount]);
//    } else {
//        auto inseadAns = atoi(answerArray[rightCount].c_str());
//        answer = atoi(answerArray[rightCount].c_str());
//        showAnswer(inseadAns);
//    }
    onShowedOneAnimFlag = true;
    auto oneAnimTitle = Sprite::create("res/animation/answer-this-one.png");
    oneAnimTitle->setTag(TAG_GAME_ONESPR);
    
    oneAnimTitle->setScale(screenSize.width*0.25/oneAnimTitle->getContentSize().width);
    oneAnimTitle->setAnchorPoint(Vec2(0.5, 1));
    this->addChild(oneAnimTitle);
    
/*
    Button* oneAnimhand = Button::create("res/animation/taphand.png", "res/animation/taphand.png");

    oneAnimhand->setTag(TAG_GAME_ONEANIM); oneAnimhand->addTouchEventListener(CC_CALLBACK_2(GameScene::gotoAnimhand, this));
    oneAnimhand->setScale(screenSize.width * 0.1f/oneAnimhand->getContentSize().width);
    this->addChild(oneAnimhand);
*/
    
    auto oneAnimhand = Sprite::create("res/animation/taphand.png");
    oneAnimhand->setTag(TAG_GAME_ONEANIM);
    oneAnimhand->setScale(screenSize.width*0.13/oneAnimhand->getContentSize().width);
    oneAnimhand->setAnchorPoint(Vec2(0, 0.8));
    this->addChild(oneAnimhand);

    if(fractionFlag>0){
        oneAnimTitle->setPosition(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.3);
        oneAnimhand->setPosition(Vec2(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.16));
    }
    else {
        oneAnimTitle->setPosition(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.27);
        oneAnimhand->setPosition(Vec2(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.12));
    }

    
}

void GameScene::removeOneByOneAnimation(){
    onRemoveDimLayer();
    onShowedOneAnimFlag = false;
    
    auto oneAnimTitle = (Sprite*)this->getChildByTag(TAG_GAME_ONESPR);
    this->removeChild(oneAnimTitle);
    
    auto oneAnimhand =(Sprite*)this->getChildByTag(TAG_GAME_ONEANIM);
    this->removeChild(oneAnimhand);
}


void GameScene::onNlineAnim(){
    onShowDimLayer();
    onshowedNlineAnimFlag = true;
    auto nlineAnimTitle = Sprite::create("res/animation/Numberline.png");
    nlineAnimTitle->setTag(TAG_GAME_NLINESPR);
    nlineAnimTitle->setPosition(screenSize.width*0.5, screenSize.height*0.03 + screenSize.width*0.08);
    nlineAnimTitle->setScale(screenSize.width*0.35/nlineAnimTitle->getContentSize().width);
    nlineAnimTitle->setAnchorPoint(Vec2(0.5, 0));
    this->addChild(nlineAnimTitle);
    
    auto nlineAnimhand = Sprite::create("res/animation/nline_hand.png");
    nlineAnimhand->setTag(TAG_GAME_NLINEANIM);
    nlineAnimhand->setScale(screenSize.width*0.13/nlineAnimhand->getContentSize().width);
    nlineAnimhand->setAnchorPoint(Vec2(0.2, 0));
    
    this->addChild(nlineAnimhand);
    nlineAnimhand->setPosition(screenSize.width*0.2, screenSize.height*0.03 + screenSize.width*0.08);
    
    auto numberline2Spr = (Sprite*) this->getChildByTag(TAG_GAME_KEYNUMBERLINE1);
    
    this->removeChild(numberline2Spr);
    
    
    auto numberline1Spr = Sprite::Sprite::create(StringUtils::format("res/key/numberline%d.png", axisFlag));
    numberline1Spr->setTag(TAG_GAME_KEYNUMBERLINE1);
    numberline1Spr->setPosition(screenSize.width*0.5, screenSize.height*0.03);
    numberline1Spr->setAnchorPoint(Point(0.5f,0.0f));
    numberline1Spr->setScale(screenSize.width*0.9/numberline1Spr->getContentSize().width);
    this->addChild(numberline1Spr);
    
    
    auto action_0 = RotateTo::create(1.2f, 15.0f);
    auto action_1 = RotateTo::create(1.2f, -15.0f);
    auto action_2 = Sequence::create(action_0, action_1, NULL);
    auto action_3 = RepeatForever::create(action_2);
    nlineAnimhand->runAction(action_3);
}

void GameScene::removeNlineAnim(){
    onRemoveDimLayer();
    onshowedNlineAnimFlag = false;
    
    auto nlineAnimTitle = (Sprite*)this->getChildByTag(TAG_GAME_NLINESPR);
    this->removeChild(nlineAnimTitle);
    
    auto nlineAnimhand =(Sprite*)this->getChildByTag(TAG_GAME_NLINEANIM);
    this->removeChild(nlineAnimhand);
}



void GameScene::initanswerLayer(){
    if(fractionFlag>0 && !deciamlFlag){
        auto answerLayer = new FractionAnswerLayer(0);//FractionLayer::create();
        answerLayer->setPosition(screenSize.width*0.75, screenSize.height*0.2 + screenSize.width*0.08);
        answerLayer->setTag(TAG_GAME_ANSWERLABEL);
        answerLayer->setOpacity(0);
        this->addChild(answerLayer);
    } else if(fractionFlag>0 && deciamlFlag){
        auto answerlabel = Label::createWithSystemFont("", "Yesterday Dream", screenSize.width*0.04);
        answerlabel->setColor(Color3B::BLACK);
        answerlabel->setPosition(screenSize.width*0.66, screenSize.height*0.2 + screenSize.width*0.17);
        answerlabel->setTag(TAG_GAME_ANSWERLABEL);
        answerlabel->setOpacity(0);
        this->addChild(answerlabel);
        
        auto answerBar = Label::createWithSystemFont("_", "Yesterday Dream", screenSize.width*0.05);
        answerBar->setColor(Color3B::WHITE);
        answerBar->setPosition(screenSize.width*0.67, screenSize.height*0.21 + screenSize.width*0.21);
        answerBar->setTag(TAG_GAME_ANSWERBAR);
        this->addChild(answerBar);
    } else {
        auto answerlabel = Label::createWithSystemFont("", "Yesterday Dream", screenSize.width*0.04);
        answerlabel->setColor(Color3B::BLACK);
        answerlabel->setPosition(screenSize.width*0.66, screenSize.height*0.3 + screenSize.width*0.13);
        answerlabel->setTag(TAG_GAME_ANSWERLABEL);
        answerlabel->setOpacity(0);
        this->addChild(answerlabel);
    }
}



void GameScene::Fraction26(int mol1, int den1, int mol2, int den2, int order, float offsetPos, std::string op){
    
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+order);
    
    if(den1 != 1){
        auto moleculeLabel = Label::createWithSystemFont(StringUtils::format("%d", mol1), "Yesterday Dream", screenSize.width*0.04);
        moleculeLabel->setColor(Color3B::BLACK);
        moleculeLabel->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.107);
        moleculeLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4);
        problemLayer->addChild(moleculeLabel);
        
        auto denLabel = Label::createWithSystemFont(StringUtils::format("%d", den1), "Yesterday Dream", screenSize.width*0.04);
        denLabel->setColor(Color3B::BLACK);
        denLabel->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.068);
        denLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +1);
        problemLayer->addChild(denLabel);
        
        auto lineSpr = Sprite::create("res/game/line.png");
        lineSpr->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.095);
        lineSpr->setScale(screenSize.width*0.045/lineSpr->getContentSize().width, screenSize.width*0.006/lineSpr->getContentSize().height);
        
        problemLayer->addChild(lineSpr);
    } else {
        auto moleculeLabel = Label::createWithSystemFont(StringUtils::format("%d", mol1), "Yesterday Dream", screenSize.width*0.04);
        moleculeLabel->setColor(Color3B::BLACK);
        moleculeLabel->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.085);
        moleculeLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4);
        problemLayer->addChild(moleculeLabel);
        
        auto denLabel = Label::createWithSystemFont(StringUtils::format("%d", den1), "Yesterday Dream", 0);
        denLabel->setColor(Color3B::BLACK);
        denLabel->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.068);
        denLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +1);
        problemLayer->addChild(denLabel);
    }
    
    auto moleculeLabel2 = Label::createWithSystemFont(StringUtils::format("%d", mol2), "Yesterday Dream", screenSize.width*0.04);
    moleculeLabel2->setColor(Color3B::BLACK);
    moleculeLabel2->setPosition(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.107);
    moleculeLabel2->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +2);
    problemLayer->addChild(moleculeLabel2);
    
    auto denLabel2 = Label::createWithSystemFont(StringUtils::format("%d", den2), "Yesterday Dream", screenSize.width*0.04);
    denLabel2->setColor(Color3B::BLACK);
    denLabel2->setPosition(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.068);
    denLabel2->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 + 3);
    problemLayer->addChild(denLabel2);
    
    auto lineSpr2 = Sprite::create("res/game/line.png");
    lineSpr2->setPosition(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.095);
    lineSpr2->setScale(screenSize.width*0.045/lineSpr2->getContentSize().width, screenSize.width*0.006/lineSpr2->getContentSize().height);
    problemLayer->addChild(lineSpr2);
    
    if(std::strcmp(op.c_str(), "x") == 0){
        auto oplabel = Label::createWithSystemFont("x", "Yesterday Dream", screenSize.width*0.04);
        oplabel->setPosition(-screenSize.width*0.09, screenSize.width*0.085);
        oplabel->setColor(Color3B::BLACK);
        problemLayer->addChild(oplabel);
    } else {
        Button* dividerSprbutton = Button::create("res/game/dividersprite.png", "res/game/dividersprite.png");
        dividerSprbutton->setPosition(Vec2(-screenSize.width*0.09, screenSize.width*0.085));
        dividerSprbutton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        dividerSprbutton->setTag(TAG_GAME_KEYDIVIDER + order);
        dividerSprbutton->setScale(screenSize.width*0.02/dividerSprbutton->getContentSize().width);
        problemLayer->addChild(dividerSprbutton);
        fractionSwipeFlagArray[order] = true;
    }
}


void GameScene::Fraction20(int mol1, int den1, int order){
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+order);
    auto moleculeLabel = Label::createWithSystemFont(StringUtils::format("%d", mol1), "Yesterday Dream", 0);
    moleculeLabel->setColor(Color3B::BLACK);
    moleculeLabel->setPosition(0, 0);
    moleculeLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4);
    problemLayer->addChild(moleculeLabel);
    
    auto denLabel = Label::createWithSystemFont(StringUtils::format("%d", den1), "Yesterday Dream", 0);
    denLabel->setColor(Color3B::BLACK);
    denLabel->setPosition(0, 0);
    denLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +1);
    problemLayer->addChild(denLabel);
    
    auto moleculeLabel2 = Label::createWithSystemFont(StringUtils::format("%d", mol1), "Yesterday Dream", screenSize.width*0.04);
    moleculeLabel2->setColor(Color3B::BLACK);
    moleculeLabel2->setPosition(-screenSize.width*0.09, screenSize.width*0.107);
    moleculeLabel2->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +2);
    problemLayer->addChild(moleculeLabel2);
    
    auto denLabel2 = Label::createWithSystemFont(StringUtils::format("%d", den1), "Yesterday Dream", screenSize.width*0.04);
    denLabel2->setColor(Color3B::BLACK);
    denLabel2->setPosition(-screenSize.width*0.09, screenSize.width*0.068);
    denLabel2->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 + 3);
    problemLayer->addChild(denLabel2);
    
    auto lineSpr2 = Sprite::create("res/game/line.png");
    lineSpr2->setPosition(-screenSize.width*0.09, screenSize.width*0.095);
    lineSpr2->setScale(screenSize.width*0.045/lineSpr2->getContentSize().width, screenSize.width*0.006/lineSpr2->getContentSize().height);
    problemLayer->addChild(lineSpr2);
}

void GameScene::makeproblem(){
//    int YOUR_RESULT=rand()%(max-min)+min;
    int randomnumber = arc4random()%((arrLevelsProblems.size() - 1) - 0) - 0;
//    int randomnumber = rand() % (arrLevelsProblems.size() - 1);
//    int randomnumber = std::srand() % (arrLevelsProblems.size() - 1);
    ValueMap sdata = (arrLevelsProblems[randomnumber]).asValueMap();
    auto answer1 = sdata["answer"].asString();
    auto problemlayer = Layer::create();
    auto fadeLayer = Layer::create();
    this->addChild(problemlayer);
    this->addChild(fadeLayer);
    auto cloudBg = Sprite::create("res/game/cloud.png");
    cloudBg->setPosition(screenSize.width*0.25, screenSize.height*0.71);
    cloudBg->setOpacity(100);
    fadeLayer->addChild(cloudBg);
    cloudBg->setScale(screenSize.width*0.33/cloudBg->getContentSize().width, screenSize.height*0.35/cloudBg->getContentSize().height);
    problemlayer->setTag(TAG_GAME_PROBLEM+problemCount);
    if(problemCount == 0 && fractionFlag==0){
        problemlayer->setPosition(screenSize.width*0.52, screenSize.height*0.2 + screenSize.width*0.04);
    } else if(problemCount == 0 && fractionFlag>0){
        problemlayer->setPosition(screenSize.width*0.52, screenSize.height*0.2 + screenSize.width*0.08);
    }else {
        problemlayer->setPosition(screenSize.width*0.34, screenSize.height*0.74-screenSize.width*0.085);
    }
    answerArray[problemCount] = answer1;
    
    switch(fractionFlag){
        case 0:
        {
            auto x1 =  sdata["x1"].asString();
            
            auto problemlabel = Label::createWithSystemFont(x1, "Yesterday Dream", screenSize.width*0.04);
            problemlabel->setPosition(-screenSize.width*0.09, screenSize.width*0.085);
            problemlabel->setColor(Color3B::BLACK);
            problemlayer->addChild(problemlabel);
            break;
        }
        case 1:
        {
            if(level == 20){
                auto x1 =  sdata["x1"].asInt();
                auto y1 =  sdata["y1"].asInt();
                Fraction20(x1, y1, problemCount);
            }
            else if(level == 22){
                auto x1 =  sdata["x1"].asInt();
                auto y1 =  sdata["y1"].asInt();
                auto op =  sdata["op"].asString();
                bool OpFlag = false;
                if (std::strcmp(op.c_str(), "-") == 0) {
                    OpFlag = true;
                }
                auto question1Layer = new FractionLayer(x1, y1, 0.0f, OpFlag);
                problemlayer->addChild(question1Layer);
            } else {
                auto x1 =  sdata["x1"].asInt();
                auto y1 =  sdata["y1"].asInt();
                auto question1Layer = new FractionLayer(x1, y1, 0.0f, false);
                problemlayer->addChild(question1Layer);
            }
            break;
        }
        case 2:
        {
            auto x1 =  sdata["x1"].asInt();
            auto y1 =  sdata["y1"].asInt();
            auto question1Layer = new FractionLayer(x1, y1, -0.06f, false);
            problemlayer->addChild(question1Layer);
            
            
            auto oplabel = Label::createWithSystemFont("___", "Yesterday Dream", screenSize.width*0.04);
            oplabel->setPosition(-screenSize.width*0.09, screenSize.width*0.075);
            oplabel->setColor(Color3B::BLACK);
            problemlayer->addChild(oplabel);
            auto question2Layer = new FractionLayer(1, 2, 0.06f, false);
            problemlayer->addChild(question2Layer);
            break;
        }
        case 3:
        {
            auto x1 =  sdata["x1"].asInt();
            auto y1 =  sdata["y1"].asInt();
            auto x2 =  sdata["x2"].asInt();
            auto y2 =  sdata["y2"].asInt();
            auto question1Layer = new FractionLayer(x1, y1, -0.04f, false);
            problemlayer->addChild(question1Layer);
            
            auto oplabel = Label::createWithSystemFont("x", "Yesterday Dream", screenSize.width*0.04);
            oplabel->setPosition(-screenSize.width*0.09, screenSize.width*0.085);
            oplabel->setColor(Color3B::BLACK);
            problemlayer->addChild(oplabel);
            
            auto question2Layer = new FractionLayer(x2, y2, 0.04f, false);
            problemlayer->addChild(question2Layer);
            break;
        }
        case 4:
        {
            auto x1 =  sdata["x1"].asInt();
            auto y1 =  sdata["y1"].asInt();
            auto x2 =  sdata["x2"].asInt();
            auto y2 =  sdata["y2"].asInt();
            auto op =  sdata["op"].asString();
            
            Fraction26(x1, y1, x2, y2, problemCount, 0.0f, op);
            break;
        }
    }
    problemlayer->setCascadeOpacityEnabled(true);
    problemCount++;
}
void GameScene::enterAnswer(){
    
    if(fractionFlag>0 || deciamlFlag){
        
        if(holdCount>3) {
            auto answerbar = (Label*)this->getChildByTag(TAG_GAME_ANSWERBAR);
            answerbar->setColor(Color3B::WHITE);
            holdCount = 0;
        }
        
        if(std::strcmp(answerString.c_str(), answerArray[rightCount].c_str()) == 0){
            rightAnswer();
        } else {
            wrongAnswer();
        }
    } else {
        if(answer == atoi(answerArray[rightCount].c_str())){
            rightAnswer();
        } else {
            wrongAnswer();
        }
    }
    
}

void GameScene::rightAnswer(){
    
    if(problemTime <2 && level != 24){
        addTick(ticksCount);
        addTick(ticksCount+1);
        ticksCount+=2;
    } else {
        addTick(ticksCount);
        ticksCount +=1;
    }
    wrongCountofOne = 6;
    problemTime = 0.0f;
    removeProblem(rightCount);
    rightCount++;
    achianim();
    animationProblem(rightCount);
    updateScore();
    
    answer = 0;
    answerString = "";
    for(int i =0; i<4; i++){
        fractionBoxArray[i] = false;
    }
    if(ticksCount >targetnumber-1 && level != 24){
        onShowReportLayer();
    } else if(ticksCount >4 && level == 24){
        onShowReportLayer();
    } else {
        makeproblem();
    }
}


void GameScene::wrongAnswer(){
    wrongCount++;
    if(axisFlag == 0){
        wrongCountofOne++;
    }
    
    fiboanim();
    answer = 0;
    answerString = "";
    Device::vibrate(0.6f);
    if(wrongCountofOne == 3 && level == 1)
    {
        onOneByOneAnimation();
//        wrongCountofOne = 0;
    }
}




void GameScene::fractionSwipeFunc(){
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+rightCount);
    auto *topLabel = (Label*)problemLayer->getChildByTag(TAG_GAME_PROBLEM_ELEMENT + rightCount*4 + 2);
    auto *bottpmLabel = (Label*)problemLayer->getChildByTag(TAG_GAME_PROBLEM_ELEMENT + rightCount*4 + 3);
    
    auto action_0 = MoveTo::create(0.1, Point(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.068));
    topLabel->runAction(action_0);
    auto action_1 = MoveTo::create(0.1, Point(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.107));
    bottpmLabel->runAction(action_1);
    fractionSwipeFlagArray[rightCount] = false;
    
}


void GameScene::answerSwipeFunc(){
    if(fractionFlag==0 || deciamlFlag){
        auto answerLabel = (Label*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
        answerLabel->setString("");
        clickedDividerKeyFlag = false;
        is_Negative = 1;
    } else {
        auto answerLayer = (FractionAnswerLayer*) this->getChildByTag(TAG_GAME_ANSWERLABEL);
        answerLayer->reset();
    }
    clickedDividerKeyFlag = false;
    
    if (initialAnswerTouchPos[0] - currentAnswerTouchPos[0] > screenSize.width * 0.04)
    {
        answer=0;
        answerString = "";
        if(onshowedSwipeAnimFlag){
            removeSwipeAnimation();
        }
    }
    else if (initialAnswerTouchPos[0] - currentAnswerTouchPos[0] < - screenSize.width * 0.04)
    {
        answer=0;
        answerString = "";
        if(onshowedSwipeAnimFlag){
            removeSwipeAnimation();
        }
    }else {
        taptimer = 0;
        if(answer==0 && fractionFlag!=0){
            selectedAnswerBox =0;
        } else {            
            enterAnswer();
        }
    }
    isAnswerTouchDown = false;
}



void GameScene::updateScore(){
//    score+=1000;
    float subtract = float((timer - prevTime) / 10.0f);
    
    if(subtract <= float(blueNumber / 3.0f))
    {
        score += 500;
    } else if (subtract > float(blueNumber / 3.0f) && subtract < float(3.536f * blueNumber))
    {
        score += 542 - (125 * subtract) / blueNumber;
    } else {
        score += 100;
    }
    
    prevTime = timer;
    
    auto scoreLabel = (Label*)this->getChildByTag(TAG_GAME_SCORE);
    scoreLabel->setString(StringUtils::format("%d", score));
}

void GameScene::onShowReportLayer(){
    levelCompleteFlag = true;
    
    levelSpeed = rightCount * 180/timer;
    if(levelSpeed>100) levelSpeed = 100;
    
    levelAccuracy = (rightCount - wrongCount) *100/ rightCount;
    if(levelAccuracy > 100)
    {
        levelAccuracy = 100;
    } else if(levelAccuracy < 0)
    {
        levelAccuracy = 0;
    }
    
    int speedStarCount =0;
//    int accuracyStarCount = 0;
//    if(levelSpeed ==100) speedStarCount = 4;
//    else if(levelSpeed>75 && levelSpeed<=99) speedStarCount = 3;
//    else if(levelSpeed >50 && levelSpeed <=75) speedStarCount = 2;
//    else speedStarCount = 1;
    if(timer <= targettime1 * 10) speedStarCount = 4;
    else if(timer>targettime1 * 10 && timer<=targettime * 10) speedStarCount = 3;
    else if(timer >targettime * 10 && timer <=leveltime * 10) speedStarCount = 2;
    else if(timer >leveltime * 10 && timer <=targettime2 * 10) speedStarCount = 1;
    else speedStarCount = 1;
    
    speedStarCount -= wrongCount;
    if (speedStarCount < 1) speedStarCount = 1;
    
//    StringUtils::format("res/title/level/level%d.png", newlevel)
    
//    UserDefault::getInstance()->setIntegerForKey("completedLevel",level);
//    int insteadlevel = UserDefault::getInstance()->getIntegerForKey("completedLevel");
    const char *levelstarString = StringUtils::format("level%dstar", level).c_str();
    int starCount = UserDefault::getInstance()->getIntegerForKey(levelstarString, 1);
    if(speedStarCount > starCount) {
        UserDefault::getInstance()->setIntegerForKey(levelstarString,speedStarCount);
    }
    
//    if(levelAccuracy == 100) accuracyStarCount = 4;
//    else if(levelAccuracy>75 && levelAccuracy<=99) accuracyStarCount = 3;
//    else if(levelAccuracy >50 && levelAccuracy <=75) accuracyStarCount = 2;
//    else accuracyStarCount = 1;
    
    
    auto vinyetBg = Sprite::create("res/title/Vinyet.png"); //here the background.png is a "red screen" png.
    
    vinyetBg->setPosition(screenSize.width/2, screenSize.height/2);
    
    vinyetBg->setScale(screenSize.width/vinyetBg->getContentSize().width, screenSize.height/vinyetBg->getContentSize().height);
    
    vinyetBg->setTag(TAG_GAME_VINEYET);
    this->addChild(vinyetBg);
    
    
    // Layer
    auto reportLayer = Layer::create();
    this->addChild(reportLayer);
    reportLayer->setTag(TAG_GAME_REPORTLAYER);
    reportLayer->setPosition(0, -screenSize.height);
    
    auto reportBg = Sprite::create("res/report/reportBg.png");
    reportBg->setPosition(screenSize.width*0.5 , screenSize.height/2);
    reportBg->setScale(screenSize.width*1.0/reportBg->getContentSize().width);
    reportLayer->addChild(reportBg);
    // Level Number
    auto levels = Sprite::create(StringUtils::format("res/report/Level/Level %d.png", level));
    levels->setPosition(screenSize.width*0.29, screenSize.height*0.5);
    levels->setScale(screenSize.width*0.22/levels->getContentSize().width);
    
    reportLayer->addChild(levels);
    
    // Time, Errors and personal best LabelTTF::create("Text", "Lato-Light", 60);
    const char *levelBestString = StringUtils::format("level%dbest", level).c_str();
    int bestCount = UserDefault::getInstance()->getIntegerForKey(levelBestString, 36000);
    if(timer < bestCount) {
        UserDefault::getInstance()->setIntegerForKey(levelBestString, timer);
        bestCount = timer;
    }
    
    auto bestLabel = bestCount < 600 ? Label::createWithSystemFont(StringUtils::format("%d.%d''", bestCount / 10, bestCount % 10), "Berlin Sans FB Demi", screenSize.width*0.028) : Label::createWithSystemFont(StringUtils::format("%d' %d.%d''", bestCount / 600, (bestCount % 600) / 10, (timer % 600) % 10), "Berlin Sans FB Demi", screenSize.width*0.028);
    bestLabel->setPosition(screenSize.width*0.4, screenSize.height*0.231);
    bestLabel->setColor(Color3B(45, 94, 112));
    bestLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    reportLayer->addChild(bestLabel);
    
    timer = timer > 36000 ? 36000 : timer;
    auto timeLabel = timer < 600 ? Label::createWithSystemFont(StringUtils::format("%d.%d''", timer / 10, timer % 10), "Berlin Sans FB Demi", screenSize.width*0.038) : Label::createWithSystemFont(StringUtils::format("%d' %d.%d''", timer / 600, (timer % 600) / 10, (timer % 600) % 10), "Berlin Sans FB Demi", screenSize.width*0.038);
    timeLabel->setPosition(screenSize.width*0.33, screenSize.height*0.372);
    timeLabel->setColor(Color3B(45, 94, 112));
    timeLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    reportLayer->addChild(timeLabel);
    
    auto errorLabel = Label::createWithSystemFont(StringUtils::format("%d", wrongCount), "Berlin Sans FB Demi", screenSize.width*0.038);
    errorLabel->setPosition(screenSize.width*0.37, screenSize.height*0.292);
    errorLabel->setColor(Color3B(45, 94, 112));
    errorLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    reportLayer->addChild(errorLabel);
    
    
    //4 stars time
    int fourStar = targettime1 % 10;
    auto fourStarOne = Sprite::create(StringUtils::format("res/report/Numbers/%d.png", fourStar));
    fourStarOne->setPosition(screenSize.width*0.683, screenSize.height*0.382);
    fourStarOne->setScale(screenSize.width*0.185/levels->getContentSize().width);
    fourStarOne->setAnchorPoint(Vec2(1.0f, 0.0f));
    
    reportLayer->addChild(fourStarOne);
    
    if (targettime1 > 10) {
        int fourStarTwo = targettime1 / 10;
        
        auto fourStarTen = Sprite::create(StringUtils::format("res/report/Numbers/%d.png", fourStarTwo));
        fourStarTen->setPosition(screenSize.width*0.669, screenSize.height*0.382);
        fourStarTen->setScale(screenSize.width*0.185/levels->getContentSize().width);
        fourStarTen->setAnchorPoint(Vec2(1.0f, 0.0f));
        
        reportLayer->addChild(fourStarTen);
    }
    
    //3 stars time
    int threeStar = targettime % 10;
    auto threeStarOne = Sprite::create(StringUtils::format("res/report/Numbers/%d.png", threeStar));
    threeStarOne->setPosition(screenSize.width*0.683, screenSize.height*0.339);
    threeStarOne->setScale(screenSize.width*0.185/levels->getContentSize().width);
    threeStarOne->setAnchorPoint(Vec2(1.0f, 0.0f));
    
    reportLayer->addChild(threeStarOne);
    
    if (targettime > 10) {
        int threeStarTwo = targettime / 10;
        
        auto threeStarTen = Sprite::create(StringUtils::format("res/report/Numbers/%d.png", threeStarTwo));
        threeStarTen->setPosition(screenSize.width*0.669, screenSize.height*0.339);
        threeStarTen->setScale(screenSize.width*0.185/levels->getContentSize().width);
        threeStarTen->setAnchorPoint(Vec2(1.0f, 0.0f));
        
        reportLayer->addChild(threeStarTen);
    }
    
    //2 stars time
    int twoStar = leveltime % 10;
    auto twoStarOne = Sprite::create(StringUtils::format("res/report/Numbers/%d.png", twoStar));
    twoStarOne->setPosition(screenSize.width*0.683, screenSize.height*0.29);
    twoStarOne->setScale(screenSize.width*0.185/levels->getContentSize().width);
    twoStarOne->setAnchorPoint(Vec2(1.0f, 0.0f));
    
    reportLayer->addChild(twoStarOne);
    int twoStarThree = 0;
    
    if (targettime > 10) {
        int twoStarTwo = leveltime / 10;
        
        if (twoStarTwo > 10) {
            twoStarThree = twoStarTwo / 10;
            twoStarTwo %= 10;
        }
        
        auto twoStarTen = Sprite::create(StringUtils::format("res/report/Numbers/%d.png", twoStarTwo));
        twoStarTen->setPosition(screenSize.width*0.669, screenSize.height*0.29);
        twoStarTen->setScale(screenSize.width*0.185/levels->getContentSize().width);
        twoStarTen->setAnchorPoint(Vec2(1.0f, 0.0f));
        
        reportLayer->addChild(twoStarTen);
    }
    
    if (twoStarThree > 0) {
        auto twoStarTen = Sprite::create(StringUtils::format("res/report/Numbers/%d.png", twoStarThree));
        twoStarTen->setPosition(screenSize.width*0.655, screenSize.height*0.29);
        twoStarTen->setScale(screenSize.width*0.185/levels->getContentSize().width);
        twoStarTen->setAnchorPoint(Vec2(1.0f, 0.0f));
        
        reportLayer->addChild(twoStarTen);
    }
    
    auto action_0 = MoveTo::create(0.4, Point(0 , screenSize.height*0.3));
    auto action_1 = MoveTo::create(0.1, Point(0 , -screenSize.height*0.2));
    auto action_3 = MoveTo::create(0.1, Point(0 , screenSize.height*0.1));
    auto action_4 = MoveTo::create(0.1, Point(0 , 0));
    auto action_2 = Sequence::create(action_0, action_1, action_3, action_4, NULL);
    //    auto action_3 = RepeatForever::create(action_2);
    reportLayer->runAction(action_2);
    
    //Report title
//    if(speedStarCount > 2 && levelAccuracy == 100){
    if(level > completedLevel){
        UserDefault::getInstance()->setIntegerForKey("completedLevel",level);
    }
    bool nextAvailable = true;
    if(level > lockLevel && speedStarCount >= 2){
        if (level == 6 || level == 12 || level == 18 || level == 24 || level == 30) {
            bool zonesFlag = true;
            for (int i = level - 5; i <= level; i ++) {
                const char *levelstarString = StringUtils::format("level%dstar", i).c_str();
                int starCount = UserDefault::getInstance()->getIntegerForKey(levelstarString, 1);
                if(3 > starCount) {
                    zonesFlag = false;
                    nextAvailable = false;
                    break;
                }
            }
            if (zonesFlag == true) {
                UserDefault::getInstance()->setIntegerForKey("lockLevel",level);
                const char *zonesString = StringUtils::format("zones%d", level / 6 - 1).c_str();
                UserDefault::getInstance()->setIntegerForKey(zonesString, 1);
            }
        } else {
            UserDefault::getInstance()->setIntegerForKey("lockLevel",level);
        }
            
    } else if(speedStarCount > 2) {
        int upperZone = (level / 6) + 6;
        bool zonesFlag = true;
        for (int i = upperZone - 5; i <= upperZone; i ++) {
            const char *levelstarString = StringUtils::format("level%dstar", i).c_str();
            int starCount = UserDefault::getInstance()->getIntegerForKey(levelstarString, 1);
            if(3 > starCount) {
                zonesFlag = false;
                break;
            }
        }
        if (zonesFlag == true) {
            const char *zonesString = StringUtils::format("zones%d", upperZone / 6 - 1).c_str();
            UserDefault::getInstance()->setIntegerForKey(zonesString, 1);
            UserDefault::getInstance()->setIntegerForKey("lockLevel",upperZone);
        }
    }
    
    if(speedStarCount >= 2){
        Sprite* reportTitle;
        if (speedStarCount == 4)
            reportTitle = Sprite::create("res/report/Amazing.png");
        else if (speedStarCount == 3)
            reportTitle = Sprite::create("res/report/Great Job.png");
        else if (speedStarCount == 2)
            reportTitle = Sprite::create("res/report/You Passed.png");
        if (speedStarCount > 2) {
            reportTitle->setPosition(screenSize.width*0.52, screenSize.width*0.2+screenSize.height*0.44);
            reportTitle->setScale(screenSize.width*0.049/reportTitle->getContentSize().width);
            reportTitle->setOpacity(0);
            
//            auto action_0 = MoveTo::create(0.3, Point(screenSize.width*0.52, screenSize.width*0.2+screenSize.height*0.44));
            auto action_1 = ScaleTo::create(0.3, screenSize.width*0.49/reportTitle->getContentSize().width);
            auto action_3 = FadeTo::create(0.1, 255);
            auto delay = DelayTime::create(2.3f);
//            auto spawn_1 = Spawn::createWithTwoActions(action_0, action_1);
//            auto spawn_2 = Spawn::createWithTwoActions(spawn_1, action_3);
            auto move_ease_in = EaseElasticOut::create(action_1->clone());
            auto action_2 = Sequence::create(delay, action_3, move_ease_in, NULL);
        //    auto action_3 = RepeatForever::create(action_2);
            reportTitle->runAction(action_2);
        } else {
            reportTitle->setPosition(screenSize.width*0.52, screenSize.width*0.2+screenSize.height*0.44);
            reportTitle->setScale(screenSize.width*0.049/reportTitle->getContentSize().width);
            reportTitle->setOpacity(0);
            
            auto action_1 = ScaleTo::create(0.3, screenSize.width*0.49/reportTitle->getContentSize().width);
            auto action_3 = FadeTo::create(0.1, 255);
            auto delay = DelayTime::create(2.0f);
//            auto spawn_1 = Spawn::createWithTwoActions(action_0, action_1);
//            auto spawn_2 = Spawn::createWithTwoActions(spawn_1, action_3);
            auto move_ease_in = EaseElasticOut::create(action_1->clone());
            auto action_2 = Sequence::create(delay, action_3, move_ease_in, NULL);
        //    auto action_3 = RepeatForever::create(action_2);
            reportTitle->runAction(action_2);
        }
        
        reportLayer->addChild(reportTitle);
        Button* reportContinueButton;
        if (nextAvailable) {
            reportContinueButton = Button::create("res/report/report_continue.png", "res/report/report_continue_selected.png");
            reportContinueButton->setTag(TAG_GAME_REPORTCONTINUE);
        } else {
            reportContinueButton = Button::create("res/report/continue_failure.png", "res/report/continue_failure.png");
            reportContinueButton->setTag(TAG_GAME_REPORTFAILURE);
        }
//        Button* reportContinueButton = Button::create("res/report/report_continue.png", "res/report/report_continue_selected.png");
        reportContinueButton->setPosition(Vec2(screenSize.width*0.52, screenSize.height*0.5 - screenSize.width * 0.215f));
        reportContinueButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
//        reportContinueButton->setTag(TAG_GAME_REPORTCONTINUE);
        reportContinueButton->setScale(this->screenSize.width * 0.12f/reportContinueButton->getContentSize().width);
        reportLayer->addChild(reportContinueButton);
        
    } else {
        auto reportTitle = Sprite::create("res/report/Keep Trying.png");
        reportTitle->setPosition(screenSize.width*0.52, screenSize.width*0.2+screenSize.height*0.44);
        reportTitle->setScale(screenSize.width*0.049/reportTitle->getContentSize().width);
        reportTitle->setOpacity(0);
        
        auto action_1 = ScaleTo::create(0.3, screenSize.width*0.49/reportTitle->getContentSize().width);
        auto action_3 = FadeTo::create(0.1, 255);
        auto delay = DelayTime::create(1.3f);
//            auto spawn_1 = Spawn::createWithTwoActions(action_0, action_1);
//            auto spawn_2 = Spawn::createWithTwoActions(spawn_1, action_3);
        auto move_ease_in = EaseElasticOut::create(action_1->clone());
        auto action_2 = Sequence::create(delay, action_3, move_ease_in, NULL);
    //    auto action_3 = RepeatForever::create(action_2);
        reportTitle->runAction(action_2);
        
        reportLayer->addChild(reportTitle);
        Button* reportContinueButton;
        if (level<lockLevel) {
            reportContinueButton = Button::create("res/report/report_continue.png", "res/report/report_continue_selected.png");
            reportContinueButton->setTag(TAG_GAME_REPORTCONTINUE);
        } else {
            reportContinueButton = Button::create("res/report/continue_failure.png", "res/report/continue_failure.png");
            reportContinueButton->setTag(TAG_GAME_REPORTFAILURE);
        }
        reportContinueButton->setPosition(Vec2(screenSize.width*0.52, screenSize.height*0.5 - screenSize.width * 0.215f));
        reportContinueButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
//        reportContinueButton->setTag(TAG_GAME_REPORTFAILURE);
        reportContinueButton->setScale(this->screenSize.width * 0.12f/reportContinueButton->getContentSize().width);
        reportLayer->addChild(reportContinueButton);
    }
    
//    Top star
//    for(int ii=0; ii<speedStarCount; ii++){
//        auto starSpr = Sprite::create("res/report/star.png");
//        starSpr->setPosition(screenSize.width*0.54+screenSize.width*0.067*ii , screenSize.height/2+screenSize.width*0.035);
//        starSpr->setScale(screenSize.width*0.064/starSpr->getContentSize().width);
//        reportLayer->addChild(starSpr);
//    }
    // Bottom star
//    for(int ii=0; ii<accuracyStarCount; ii++){
//        auto starSpr = Sprite::create("res/report/star.png");
//        starSpr->setPosition(screenSize.width*0.54+screenSize.width*0.067*ii , screenSize.height/2-screenSize.width*0.048);
//        starSpr->setScale(screenSize.width*0.064/starSpr->getContentSize().width);
//        reportLayer->addChild(starSpr);
//    }
    
    // report buttons
    Button* reportBackButton = Button::create("res/report/report_back.png", "res/report/report_back_selected.png");
    reportBackButton->setPosition(Vec2(screenSize.width*0.3, screenSize.height*0.5 - screenSize.width * 0.215f));
    reportBackButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
    reportBackButton->setTag(TAG_GAME_REPORTBACK);
    reportBackButton->setScale(this->screenSize.width * 0.12f/reportBackButton->getContentSize().width);
    reportLayer->addChild(reportBackButton);
    
    Button* reportExitButton = Button::create("res/report/report_exit.png", "res/report/report_exit_selected.png");
    reportExitButton->setPosition(Vec2(screenSize.width*0.74, screenSize.height*0.5 - screenSize.width * 0.215f));
    reportExitButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
    reportExitButton->setTag(TAG_GAME_REPORTEXIT);
    reportExitButton->setScale(this->screenSize.width * 0.12f/reportExitButton->getContentSize().width);
    reportLayer->addChild(reportExitButton);
    
    for (int i = 0; i < speedStarCount; i ++) {
        auto starSpr = Sprite::create(StringUtils::format("res/report/star_0%d.png", i + 1));
        starSpr->setPosition(screenSize.width*0.5 , screenSize.height/2);
        starSpr->setOpacity(0);
        starSpr->setScale(screenSize.width*0.1/starSpr->getContentSize().width);
        
        auto action_1 = ScaleTo::create(0.3, screenSize.width * 1.0/starSpr->getContentSize().width);
        auto action_3 = FadeTo::create(0.1, 255);
        auto delay = DelayTime::create(0.7 + 0.3 * i);
        
        auto move_ease_in = EaseElasticOut::create(action_1->clone());
        auto spawn_1 = Spawn::createWithTwoActions(move_ease_in, action_3);
        auto action_2 = Sequence::create(delay, spawn_1, NULL);
        
        starSpr->runAction(action_2);
        reportLayer->addChild(starSpr);
    }

    
}

void GameScene::onRemoveReportLayer(int status){
    levelCompleteFlag = false;
    auto *reportBg = (Sprite*)this->getChildByTag(TAG_GAME_VINEYET);
    this->removeChild(reportBg);
    
    auto *reportLayer = (Layer*)this->getChildByTag(TAG_GAME_REPORTLAYER);
    
    auto action_0 = MoveTo::create(0.1, Point(0 , -screenSize.height*0.1));
    auto action_1 = MoveTo::create(0.4, Point(0 , screenSize.height));    
    
    auto action_2 = CallFuncN::create( CC_CALLBACK_1(GameScene::reportCallback, this, (int)status));
    auto action_3 = Sequence::create(action_0, action_1, action_2, NULL);
    //    auto action_3 = RepeatForever::create(action_2);
    reportLayer->runAction(action_3);
    
}

void GameScene::getLevelInfo(){
    ValueMap data;
    std::string path = FileUtils::getInstance()->fullPathForFilename("res/plist/levels.plist");
    data = FileUtils::getInstance()->getValueMapFromFile(path);
    arrLevels = data.at("levels").asValueVector();
    ValueMap sdata = (arrLevels[level-1]).asValueMap();
//    targetnumber =  sdata["targetnumber"].asInt();
    targetnumber = 5;
    targettime =  sdata["time2"].asInt();
    targettime1 =  sdata["time1"].asInt();
    targettime2 =  sdata["time3"].asInt();
    leveltime = sdata["leveltime"].asInt();
    blueNumber = sdata["bluetime"].asFloat();
}

void GameScene::nextLevel(){
    auto *reportLayer = (Layer*)this->getChildByTag(TAG_GAME_REPORTLAYER);
    
    auto action_0 = MoveTo::create(0.1, Point(0 , -screenSize.height*0.1));
    auto action_1 = MoveTo::create(0.4, Point(0 , screenSize.height));
    
    
    auto action_2 = CallFuncN::create( CC_CALLBACK_1(GameScene::onIntroduceLevel, this));
    auto action_3 = Sequence::create(action_0, action_1, action_2, NULL);
    //    auto action_3 = RepeatForever::create(action_2);
    reportLayer->runAction(action_3);
    
}

void GameScene::onRemoveIntroduceLevel(bool activeFlag){
    levelCompleteFlag = false;
    auto *reportBg = (Sprite*)this->getChildByTag(TAG_GAME_VINEYET);
    this->removeChild(reportBg);
    
    auto *reportLayer = (Layer*)this->getChildByTag(TAG_GAME_NEXTLAYER);
    
    auto action_0 = MoveTo::create(0.1, Point(- screenSize.width*0.8 , 0));
    auto action_1 = MoveTo::create(0.8, Point(- screenSize.width*2 , 0));
    auto action_2 = CallFuncN::create( CC_CALLBACK_1(GameScene::reportCallback, this, 2));
    
    if(!activeFlag){
        action_2 = CallFuncN::create( CC_CALLBACK_1(GameScene::reportCallback, this, 3));
    }
    
    auto action_3 = Sequence::create(action_0, action_1, action_2, NULL);
    //    auto action_3 = RepeatForever::create(action_2);
    reportLayer->runAction(action_3);
    
}

void GameScene::onIntroduceLevel(Ref *sender){
    nextLevelFlag = true;
    // Layer
    auto levelExplainLayer = Layer::create();
    this->addChild(levelExplainLayer);
    levelExplainLayer->setTag(TAG_GAME_NEXTLAYER);
    
    auto levelBg = Sprite::create("res/title/level_ground.png");
    
    levelBg->setPosition(screenSize.width*3/2 , screenSize.height/2);
    levelBg->setScale(screenSize.width*0.7/levelBg->getContentSize().width);
    levelExplainLayer->addChild(levelBg);
    
    //    CCLOG("level %d", level);
    auto newlevel = level+1;
    //level title
    auto levelTitle = Sprite::create(StringUtils::format("res/title/level/level%d.png", newlevel));
    auto levelBgPos = levelBg->getPosition();
    levelTitle->setPosition(levelBgPos.x - screenSize.width*0.03, levelBgPos.y + screenSize.width*0.2);
    levelTitle->setScale(screenSize.width*0.27/levelTitle->getContentSize().width);
    
    levelExplainLayer->addChild(levelTitle);
    
    
    //level content
    auto levelContent = Sprite::create(StringUtils::format("res/title/contents/content%d.png", newlevel));
    levelContent->setPosition(levelBgPos.x - screenSize.width*0.03, levelBgPos.y + screenSize.width*0.135);
    levelContent->setScale(screenSize.width*0.5/levelContent->getContentSize().width);
    
    levelExplainLayer->addChild(levelContent);
    
    
    // level continue
    Button* buttonPlay = Button::create("res/title/Continue.png", "res/title/Continue_selected.png");
    buttonPlay->setTag(TAG_GAME_NEXTLEVEL);
    buttonPlay->setPosition(Vec2(levelBgPos.x - screenSize.width*0.025, levelBgPos.y - screenSize.width*0.16));
    buttonPlay->setScale(screenSize.width*0.18/buttonPlay->getContentSize().width);
    buttonPlay->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
    levelExplainLayer->addChild(buttonPlay);
    
    
    ValueMap sdata = (this->arrLevels[newlevel-1]).asValueMap();
    targetnumber =  sdata["targetnumber"].asInt();
    targettime =  sdata["time2"].asInt();
    targettime1 =  sdata["time1"].asInt();
    targettime2 =  sdata["time3"].asInt();
    leveltime = sdata["leveltime"].asInt();
    
    auto levelNumber = Sprite::create(StringUtils::format("res/title/number%d.png", targetnumber));
    levelNumber->setPosition(levelBgPos.x - screenSize.width*0.21, levelBgPos.y - screenSize.width*0.02);
    levelNumber->setScale(screenSize.width*0.08/levelNumber->getContentSize().width);
    
    levelExplainLayer->addChild(levelNumber);
    
    auto levelTime = Sprite::create(StringUtils::format("res/title/timer/timer%d.png", leveltime));
    levelTime->setPosition(levelBgPos.x + screenSize.width*0.16, levelBgPos.y - screenSize.width*0.02);
    levelTime->setScale(screenSize.width*0.08/levelTime->getContentSize().width);
    
    levelExplainLayer->addChild(levelTime);
    
    
    Button* buttonClose = Button::create("res/title/close.png", "res/title/close.png");
    buttonClose->setTag(TAG_GAME_CLOSE);
    buttonClose->setPosition(Vec2(levelBgPos.x + screenSize.width*0.285, levelBgPos.y + screenSize.width*0.19));
    buttonClose->setScale(screenSize.width * 0.06f/buttonClose->getContentSize().width);
    buttonClose->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
    
    levelExplainLayer->addChild(buttonClose);
    
    auto action_0 = MoveTo::create(0.4, Point(- screenSize.width*1.1 , 0));
    auto action_1 = MoveTo::create(0.1, Point(- screenSize.width*0.95 , 0));
    auto action_2 = Sequence::create(action_0, action_1, NULL);
    levelExplainLayer->runAction(action_2);
    
}



void GameScene::reportCallback(Ref *sender, int status){
    audio->stopBackgroundMusic();
    if(status == 1){
        auto gameScene = GameScene::createScene(level);
        Director::getInstance()->replaceScene(gameScene);
    } else if(status == 2){
        auto gameScene = GameScene::createScene(level+1);
        Director::getInstance()->replaceScene(gameScene);
    } else if(status == 3){
        auto mapScene = MapviewScene::createScene();
        Director::getInstance()->replaceScene(mapScene);
    }
    
}



void GameScene::removeProblem(int order){
    
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+order);
    this->removeChild(problemLayer);
    
}

void GameScene::animationProblem(int order){
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+order);
    auto destinationPos = Point(0,0);
    if(fractionFlag>0) {
        destinationPos = Point(screenSize.width*0.52, screenSize.height*0.2 + screenSize.width*0.08);
    } else {
        destinationPos = Point(screenSize.width*0.52, screenSize.height*0.2 + screenSize.width*0.04);
    }
    
    auto action_1 = FadeTo::create(0.05f, 0);
    auto action_2 = FadeTo::create(0.4f, 255);
    auto action_0 = MoveTo::create(0.05f, destinationPos);
    auto action_3 = Sequence::create(action_1, action_0, action_2, NULL);
    if (problemLayer != NULL) problemLayer->runAction(action_3);
}

void GameScene::gotoHome(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
//        Director::getInstance()->popScene();
        auto mapScene = MapviewScene::createScene();
        Director::getInstance()->replaceScene(mapScene);
        
    }
    
}

void GameScene::gotoEnter(Ref *pSender, Widget::TouchEventType type)
{

    if (type == Widget::TouchEventType::ENDED) {
        if(!dimFlag)
        {
            
            if(fractionFlag==0 || deciamlFlag){
                auto answerLabel = (Label*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
                answerLabel->setString("");
                is_Negative = 1;
            } else {
                clickedDividerKeyFlag = false;
                auto answerLayer = (FractionAnswerLayer*) this->getChildByTag(TAG_GAME_ANSWERLABEL);
                answerLayer->reset();
            }
            
            if(axisFlag == 0) {
                holdCount = 0;
                holdTime = 0.0f;
                enterAnswer();
            }
            else if((axisFlag == 1) || (axisFlag == 2)) {
                auto numberline1Spr = (Button*)this->getChildByTag(TAG_GAME_KEYNUMBERLINE1);
                Rect numberline1SprRect = numberline1Spr->getBoundingBox();
                
            }

            

        }
    }
}

void GameScene::gotoAnimhand(Ref *pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        if(dimFlag)
        {
            if(onshowedTapAnimFlag){
                removeTapAnimation();
            }
            
            if(onshowedSwipeAnimFlag){
                removeSwipeAnimation();
            }
            
            if(onShowedOneAnimFlag){
                removeOneByOneAnimation();
            }
            
            if(onshowedCancelFrAnimFlag){
                removeCancelFrAnim();
                
            }
            if(onshowedTapFrAnimFlag){
                removeTapFrAnim();
            }
            if(onshowedNlineAnimFlag){
                removeNlineAnim();
            }
        }
    }

    

}

void GameScene::gotoDelete(Ref *pSender, Widget::TouchEventType type)
{

    if (type == Widget::TouchEventType::ENDED) {
        if(!dimFlag)
        {
            if (fractionFlag == 0) {
                answer=0;
                answerString = "";
                
                auto answerLabel = (Label*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
                answerLabel->setString("");
            } else if(level == 30) {
                answer=0;
                answerString = "";
                
                auto answerLabel = (Label*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
                answerLabel->setString("");
            }
            else {
                clickedDividerKeyFlag = false;
                auto answerLayer = (FractionAnswerLayer*) this->getChildByTag(TAG_GAME_ANSWERLABEL);
                answerLayer->reset();
                auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+rightCount);
                for(int i=0; i<4; i++){
                    auto molLabel1 = (Label*)problemLayer->getChildByTag(TAG_GAME_MOLANS1 + i);
                    problemLayer->removeChild(molLabel1);
                    
                    auto ansLabel = (Label*)problemLayer->getChildByTag(TAG_GAME_MOLANS1LABEL + i);
                    problemLayer->removeChild(ansLabel);
                    
                    auto ansLine = (Label*)problemLayer->getChildByTag(TAG_GAME_MOLANS1LINE + i);
                    problemLayer->removeChild(ansLine);
                    
                    fractionBoxArray[i] = false;
                }
                selectedAnswerBox = 0;
            }
        }
    }
    

}

void GameScene::onTapFractionItem(Touch *touch){
    if(onshowedCancelFrAnimFlag){
        removeCancelFrAnim();
    }
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+rightCount);
    
    Point layerLocation = problemLayer->getPosition();
    Point location = Point(touch->getLocation().x - layerLocation.x, touch->getLocation().y - layerLocation.y);
    
    for(int i=0; i<4; i++){
        if(!fractionBoxArray[i]){
            auto molLabel1 = (Label*)problemLayer->getChildByTag(TAG_GAME_PROBLEM_ELEMENT + rightCount*4 + i);
            Rect molLabel1Rect = molLabel1->getBoundingBox();
            
            if(molLabel1Rect.containsPoint(location)){
                auto point = molLabel1->getPosition();
                auto lineSpr = Sprite::create("res/game/line.png");
                lineSpr->setPosition(point);
                lineSpr->setScale(screenSize.width*0.045/lineSpr->getContentSize().width, screenSize.width*0.006/lineSpr->getContentSize().height);
                lineSpr->setTag(TAG_GAME_MOLANS1LINE + i);
                
                problemLayer->addChild(lineSpr);
                
                auto answerBoxSpr = Sprite::create("res/game/answerboxlayer.png");
                auto ansLabel = Label::createWithSystemFont("", "Yesterday Dream", screenSize.width*0.03);
                
                float xx, yy;
                if(point.x < -screenSize.width*0.11){
                    xx = - screenSize.width*0.02;
                } else {
                    xx = screenSize.width*0.02;
                }
                
//                if(point.y < screenSize.width*0.085){
                if(point.y < screenSize.width*0.07){
                    yy = -screenSize.width*0.02;
                } else {
                    yy = screenSize.width*0.02;
                }
                answerBoxSpr->setPosition(point.x + xx , point.y + yy);
                ansLabel->setPosition(point.x + xx , point.y + yy - 3);
                
                answerBoxSpr->setScale(screenSize.width*0.035/answerBoxSpr->getContentSize().width);
                answerBoxSpr->setTag(TAG_GAME_MOLANS1+i);
                problemLayer->addChild(answerBoxSpr);
                
                
                ansLabel->setColor(Color3B::WHITE);
                //                    ansLabel->setPosition(point.x - screenSize.width*0.03, point.y + screenSize.width*0.03);
                //    moleculeLabel->setPosition(0, 0);
                ansLabel->setTag(TAG_GAME_MOLANS1LABEL+i);
                problemLayer->addChild(ansLabel);
                selectedAnswerBox = i+1;
                fractionBoxArray[i] = true;
                
            }
            
        } else {
            auto answerBoxSpr = (Sprite *)problemLayer->getChildByTag(TAG_GAME_MOLANS1 + i);
            Rect boxSprRect = answerBoxSpr->getBoundingBox();
            if(boxSprRect.containsPoint(location)){
                selectedAnswerBox = i+1;
                auto ansLabel = (Label*)problemLayer->getChildByTag(TAG_GAME_MOLANS1LABEL+i);
                ansLabel->setString("");
            }
        }
        
    }
}


void GameScene::convertDividertoMultiSign(){
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+rightCount);
    
    auto *dividersign = (Button*)problemLayer->getChildByTag(TAG_GAME_KEYDIVIDER + rightCount);
    problemLayer->removeChild(dividersign);
    
    auto *den2 = (Label*)problemLayer->getChildByTag(TAG_GAME_PROBLEM_ELEMENT + rightCount*4 + 3);
    den2->setPosition(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.107);
    auto *mol2 = (Label*)problemLayer->getChildByTag(TAG_GAME_PROBLEM_ELEMENT + rightCount*4 + 2);
    mol2->setPosition(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.068);
    
    auto oplabel = Label::createWithSystemFont("x", "Yesterday Dream", screenSize.width*0.04);
    oplabel->setPosition(-screenSize.width*0.09, screenSize.width*0.085);
    oplabel->setColor(Color3B::BLACK);
    problemLayer->addChild(oplabel);
}


void GameScene::onKeyTouchEvent(Ref *pSender, Widget::TouchEventType type)
{
    
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
        {
            if(!firstEnterFlag){
                firstEnterFlag = true;
            }
            int keyTagValue = ((cocos2d::ui::Button*) pSender)->getTag();
            if(keyTagValue == (TAG_GAME_KEYDIVIDER + rightCount)){
                convertDividertoMultiSign();
            } else {
                switch (keyTagValue){
                    case TAG_GAME_KEYADD:
                        answer *= -1;
                        is_Negative *=-1;
                        
                        showAnswer(answer);
                        AnimStart();
                        break;
                    case TAG_GAME_KEYSMALL:
                        CompareNumber(-1);
                        break;
                    case TAG_GAME_KEYEQUAL:
                        CompareNumber(0);
                        break;
                    case TAG_GAME_KEYBIG:
                        CompareNumber(1);
                        break;
                    case TAG_GAME_KEYFRACTION:
                        onClickDividerKey();
                        break;
                    case TAG_GAME_KEYDECIMAL:
                        onClickDeciamlKey();
                        AnimStart();
                        break;
                    case TAG_GAME_REPORTBACK:
                        onRemoveReportLayer(1);
                        break;
                    case TAG_GAME_REPORTCONTINUE:
                        nextLevel();
//                        onRemoveReportLayer(2);
                        break;
                    case TAG_GAME_REPORTEXIT:
                        onRemoveReportLayer(3);
                        break;
                    case TAG_GAME_NEXTLEVEL:
                        onRemoveIntroduceLevel(true);
                        break;
                    case TAG_GAME_CLOSE:
                        onRemoveIntroduceLevel(false);
                        break;
                    case TAG_GAME_KEY: case 202:case 203: case 204: case 205: case 206: case 207: case 208: case 209: case 210:
                        AnimStart();
                    default:
                    {
                        
                        if(!tapenteranimFlag && level<4){
                            if(!startingTapFlag){
                                startingTapFlag = true;
                            } else {
                                waittingTaptimer = 0.0f;
                            }
//                            tapenteranimFlag = true;
//                            UserDefault::getInstance()->setIntegerForKey("tapenteranimFlag", true);
//                            onTapAnimation();
                        }
                        
                        if(tapentertimeFlag){
                            onkeyswipeFlag = true;
                        }
                        
                        
                        if(selectedAnswerBox > 0){
                            showAnswerBox(keyTagValue);
                            
                        } else {
                            answer = answer*10 + (keyTagValue%10)*is_Negative;
                            if(fractionFlag>0 && !deciamlFlag){
                                
                                showFractionAnswer(keyTagValue%10);
                            } else if(fractionFlag>0 && deciamlFlag){
                                holdFlag = true;
                                holdnowVal = keyTagValue;
                                showDecimalAnswer(keyTagValue);
                            }else {
                                if(deciamlFlag){
                                    
                                    showDecimalAnswer(keyTagValue);
                                } else {
                                    //                                    answer = answer*10 + (keyTagValue%10)*is_Negative;
                                    showAnswer(answer);
                                }
                                
                            }
                        }
                        
                        
                        
                        
                        break;
                    }
                }
                
                
            }
            
            
        }
           
            break;
            
        case Widget::TouchEventType::MOVED:
            
            break;
            
        case Widget::TouchEventType::ENDED:{
            holdFlag = false;
            holdTime = 0.0f;
            if(holdpreVal == holdnowVal){
                holdCount++;
            } else {
                holdCount = 1;
                holdpreVal = holdnowVal;
            }
            
        }
   
            break;
            
        case Widget::TouchEventType::CANCELED:
            
            break;
            
        default:
            break;
    }
    
//    int keyTagValue = ((cocos2d::ui::Button*) pSender)->getTag();
//    
//    if(keyTagValue<211 && keyTagValue>0 && clickedkeycount%2 == 0){
//        answer = answer*10 + keyTagValue%10;
//        CCLOG("clickedkeycount = %d", clickedkeycount);
//        CCLOG("keyTagValue = %d", keyTagValue);
//            showAnswer(answer);
//    }
//    clickedkeycount++;
    
}

void GameScene::showAnswerBox(int ans){
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+rightCount);
    auto boxLabel = (Label*)problemLayer->getChildByTag(TAG_GAME_MOLANS1LABEL + selectedAnswerBox -1);
    boxLabel->setString(StringUtils::format("%d", ans%10));
    selectedAnswerBox = 0;
}

void GameScene::CompareNumber(int ans){
    if(ans == atoi(answerArray[rightCount].c_str())){
        rightAnswer();
    } else {
        wrongAnswer();
    }
}

void GameScene::onClickDeciamlKey(){
    if(answerString == ""){
        answerString ="0";
    }
    
    std::string keydeciamlvalue = StringUtils::format("%s", ".");
    answerString = StringUtils::format("%s%s", answerString.c_str(), keydeciamlvalue.c_str());
    auto answerLabel = (Label*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
    answerLabel->setString(answerString);
    
}

void GameScene::onClickDividerKey(){
    if(onshowedTapFrAnimFlag){
        removeTapFrAnim();
    }
    if(answerString != "" && !clickedDividerKeyFlag){
        std::string keydividevalue = StringUtils::format("%s", "/");
        answerString = StringUtils::format("%s%s", answerString.c_str(), keydividevalue.c_str());
        clickedDividerKeyFlag = true;
        auto answerLayer = (FractionAnswerLayer*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
        answerLayer->onClickDividerKey();
    }
    
}



void GameScene::showFractionAnswer(int keyValue){
    
    answerString = StringUtils::format("%s%d", answerString.c_str(), keyValue);
    auto answerLayer = (FractionAnswerLayer*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
    answerLayer->onClickNormalKey(keyValue);
}

void GameScene::showDecimalAnswer(int keyValue){
    auto answerLabel = (Label*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
    
    
   if(level == 30 && holdCount > 3) {
        answerString = StringUtils::format("%s%d%s", "0.", (keyValue%10)," ");
        answerLabel->setString(answerString);
        
        auto answerbar = (Label*)this->getChildByTag(TAG_GAME_ANSWERBAR);
        answerbar->setColor(Color3B::BLACK);
    } else {
        answerString = StringUtils::format("%s%d", answerString.c_str(), (keyValue%10));
        answerLabel->setString(answerString);
        
    }
    
    switch (answerString.length()) {
        case 5:
            answerLabel->setSystemFontSize(screenSize.width*0.035);
            break;
        case 6:
            answerLabel->setSystemFontSize(screenSize.width*0.03);
            break;
        case 7: case 8: case 9: case 10:
            answerLabel->setSystemFontSize(screenSize.width*0.027);
            break;
            
        default:
            answerLabel->setSystemFontSize(screenSize.width*0.04);
            break;
    }
    
//    if(answerString.length() > 4 && answerString.length() <7) {
//        answerLabel->setSystemFontSize(screenSize.width*0.03);
//    } else {
//        answerLabel->setSystemFontSize(screenSize.width*0.04);
//    }
}

void GameScene::showDecimalAnswer1(std::string insteadAns){
    
    answerString = StringUtils::format("%s", insteadAns.c_str());
    auto answerLabel = (Label*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
    CCLOG("string");
    answerLabel->setString(answerString);
    
    switch (answerString.length()) {
        case 5:
            answerLabel->setSystemFontSize(screenSize.width*0.035);
            break;
        case 6:
            answerLabel->setSystemFontSize(screenSize.width*0.03);
            break;
        case 7: case 8: case 9: case 10:
            answerLabel->setSystemFontSize(screenSize.width*0.027);
            break;
            
        default:
            answerLabel->setSystemFontSize(screenSize.width*0.04);
            break;
    }

}

void GameScene::showAnswer(int ans){

    CCLOG("showanswer");
    auto answerLabel = (Label*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
    if(answer == 0 && is_Negative == -1){
        answerLabel->setString("-");
    } else{
        answerLabel->setString(StringUtils::format("%d", answer));
    }
    
    if((ans>9999 && ans< 100000 ) || (ans<-999 && ans> -10000)){
        answerLabel->setSystemFontSize(screenSize.width*0.035);
    } else if((ans>99999 && ans< 1000000 ) || (ans<-9999 && ans> -100000)){
        answerLabel->setSystemFontSize(screenSize.width*0.03);
    } else if((ans>999999 && ans< 10000000 ) || (ans<-99999 && ans> -1000000)){
        answerLabel->setSystemFontSize(screenSize.width*0.025);
    } else {
        answerLabel->setSystemFontSize(screenSize.width*0.04);
    }
    
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{

    if(!dimFlag){
/*        Point location = touch->getLocation();
        if(axisFlag ==0){
            CCLOG("locationx=%f", location.x);
            CCLOG("locationy=%f", location.y);
            Rect *answerSprRect = new Rect(screenSize.width*0.5, screenSize.height*0.16 + screenSize.width*0.04, screenSize.width*0.36 , screenSize.width*0.28);
            
            if(answerSprRect->containsPoint(location)){
                initialAnswerTouchPos[0] = location.x;
                initialAnswerTouchPos[1] = location.y;
                currentAnswerTouchPos[0] = location.x;
                currentAnswerTouchPos[1] = location.y;
                
                isAnswerTouchDown = true;
                
            }
            
        }
        */
        if(fractionSwipeFlagArray[rightCount] == true){
            
            auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+rightCount);
            Point layerLocation = problemLayer->getPosition();
            Point convertedLocation = Point(touch->getLocation().x - layerLocation.x, touch->getLocation().y - layerLocation.y);
            
            if(convertedLocation.x<(-screenSize.width*0.02) && convertedLocation.x>=(-screenSize.width*0.08) && convertedLocation.y<screenSize.width*0.16 && convertedLocation.y>=screenSize.width*0.02){
                initialSwipeFractionPos[0] = convertedLocation.x;
                initialSwipeFractionPos[1] = convertedLocation.y;
                swipe28Flag = true;
            }
        }

    
        
    }

    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{

    if(!dimFlag){
        /*
        Point location = touch->getLocation();
        if(axisFlag ==0){
            Rect *answerSprRect = new Rect(screenSize.width*0.5, screenSize.height*0.16 + screenSize.width*0.04, screenSize.width*0.36 , screenSize.width*0.28);
            
            if(answerSprRect->containsPoint(location) && isAnswerTouchDown){
                currentAnswerTouchPos[0] = location.x;
                currentAnswerTouchPos[1] = location.y;
            } else {
                isAnswerTouchDown = false;
            }
        }
         */
        auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+rightCount);
        Point layerLocation = problemLayer->getPosition();
        Point convertedLocation = Point(touch->getLocation().x - layerLocation.x, touch->getLocation().y - layerLocation.y);
        
        if(convertedLocation.x<(-screenSize.width*0.02) && convertedLocation.x>=(-screenSize.width*0.08) && convertedLocation.y<screenSize.width*0.16 && convertedLocation.y>=screenSize.width*0.02 && swipe28Flag){
            currentSwipeFractionPos[0] = convertedLocation.x;
            currentSwipeFractionPos[1] = convertedLocation.y;
            
            
        } else {
            swipe28Flag = false;
        }

    }
 
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    if(!dimFlag)
    {
        if(axisFlag == 1 || axisFlag == 2) {
            Point location = touch->getLocation();
            
            auto numberline1Spr = (Sprite*)this->getChildByTag(TAG_GAME_KEYNUMBERLINE1);
            Rect numberline1SprRect = numberline1Spr->getBoundingBox();
            
            if(numberline1SprRect.containsPoint(location)){
                if(!firstEnterFlag){
                    firstEnterFlag = true;
                }

                auto answerpos = location.x;
                float numberlineanswer = 0.0f;
                if(onshowedNlineAnimFlag){
                    removeNlineAnim();
                }
                if(axisFlag == 1){
                    
                    numberlineanswer = (answerpos - screenSize.width*0.15)/(screenSize.width*0.7);
                    
                } else if (axisFlag == 2){
                    numberlineanswer = (answerpos - screenSize.width*0.5 )/(screenSize.width*0.35);
                }
                auto realanswer = atof(answerArray[rightCount].c_str());
                if((realanswer+0.12) > numberlineanswer && (realanswer - 0.12)< numberlineanswer){
                    rightAnswer();
                } else {
                    wrongAnswer();
                }
                
                
                
            }
        } else if(fractionFlag == 4 || level == 20){
            
            if(swipe28Flag == true && (level == 28 || level == 29)){
                
                swipe28Flag = false;
                
                if (initialSwipeFractionPos[1] - currentSwipeFractionPos[1] > screenSize.width * 0.06)
                {
//                    CCLOG("SWIPED top");
//                    fractionSwipeFunc();
                    convertDividertoMultiSign();
                    
                }
                else if (initialSwipeFractionPos[1] - currentSwipeFractionPos[1] < - screenSize.width * 0.06)
                {
//                    CCLOG("SWIPED bottom");
//                    fractionSwipeFunc();
                    convertDividertoMultiSign();
                    
                }else {
                    CCLOG("enter");
                    onTapFractionItem(touch);
                }
                
            } else {
                onTapFractionItem(touch);
            }
            
        }

    } else {
        
        if(onshowedTapAnimFlag){
            removeTapAnimation();
        }
        
        if(onshowedSwipeAnimFlag){
            removeSwipeAnimation();
        }
        
        if(onShowedOneAnimFlag){
            removeOneByOneAnimation();
        }
        
        if(onshowedCancelFrAnimFlag){
            removeCancelFrAnim();
            
        }
        if(onshowedTapFrAnimFlag){
            removeTapFrAnim();
        }
        if(onshowedNlineAnimFlag){
            removeNlineAnim();
        }
        
    }
}

void GameScene::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

void GameScene::AnimStart() {
    if (showingAnswer != true) {
        auto spr = (Sprite*)this->getChildByTag(TAG_GAME_ANSWERIMG);
        auto action_0 = ScaleTo::create(0.1f, 1.3*screenSize.width*0.15/spr->getContentSize().width);
        auto action_1 = ScaleTo::create(0.2f, screenSize.width*0.15/spr->getContentSize().width);
        auto callback = CallFunc::create( [this]() {
            auto label = (Sprite*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
            label->setOpacity(255);
        });
        auto action_2 = Sequence::create(action_0, action_1, callback, NULL);
        spr->runAction(action_2);
        showingAnswer = true;
    }
}

void GameScene::AnimEnd() {
    if (showingAnswer) {
        auto spr = (Sprite*)this->getChildByTag(TAG_GAME_ANSWERIMG);
        auto action_0 = ScaleTo::create(0.2f, 0.13*screenSize.width*0.15/spr->getContentSize().width);
        auto action_1 = ScaleTo::create(0.2f, 0.0f);
        auto callback = CallFunc::create( [this]() {
            auto label = (Sprite*)this->getChildByTag(TAG_GAME_ANSWERLABEL);
            label->setOpacity(0);
        });
        auto action_2 = Sequence::create(action_0, action_1, callback, NULL);
        spr->runAction(action_2);
        showingAnswer = false;
    }
}

void GameScene::WrongAnswer() {
    
}
