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
    
    playMusic();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    this->schedule(schedule_selector(GameScene::UpdateTimer),1.0f);
    this->scheduleUpdate();
    return true;
}

void GameScene::playMusic(){
    audio= CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("res/music/map.mp3", false);
}



void GameScene::initFlags(){
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
    
    if(level>=12){
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
    
    Button* homeButton = Button::create("res/game/home.png", "res/game/home.png");
    homeButton->setPosition(Vec2(screenSize.width*0.05, screenSize.height*0.9));
    homeButton->addTouchEventListener(CC_CALLBACK_2(GameScene::gotoHome, this));
    homeButton->setScale(screenSize.width * 0.05f/homeButton->getContentSize().width);
    
    this->addChild(homeButton);
    
    
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
    achispr->setPosition(screenSize.width*0.32, screenSize.height*0.16);
    achispr->setAnchorPoint(Point(1.0f,0.0f));
    achispr->setScale(screenSize.width*0.22/achispr->getContentSize().width);
    this->addChild(achispr);
    
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/fibo/fibo.plist");
    auto fibospr = Sprite::createWithSpriteFrameName("fibo0.png");
    fibospr->setTag(TAG_SPRITE_FIBO);
    fibospr->setPosition(screenSize.width*0.63, screenSize.height*0.14);
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
                                               StringUtils::format("res/key/key%d.png", (ii + 1)));
            keyButton->setPosition(Vec2(screenSize.width*0.05+screenSize.width*ii/10, screenSize.height*0.04f));
            keyButton->setAnchorPoint(Point(0.5f,0.0f));
            keyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
            keyButton->setTag(TAG_GAME_KEY+ii);
            keyButton->setScale(screenSize.width * 0.07f/keyButton->getContentSize().width);
            
            this->addChild(keyButton);
        }
        
        if(addKeyFlag){
            Button* addKeyButton = Button::create("res/key/negative.png", "res/key/negative.png");
            
            
            addKeyButton->setPosition(Vec2(screenSize.width*0.95, screenSize.height*0.06f + screenSize.width * 0.08f));
            addKeyButton->setAnchorPoint(Point(0.5f,0.0f));
            addKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
            addKeyButton->setTag(TAG_GAME_KEYADD);
            addKeyButton->setScale(screenSize.width * 0.07f/addKeyButton->getContentSize().width);
            this->addChild(addKeyButton);
        }
        
        if(fractionFlag>0){
            Button* fractionKeyButton = Button::create("res/key/divide.png", "res/key/divide.png");
            fractionKeyButton->setPosition(Vec2(screenSize.width*0.95, screenSize.height*0.08 + screenSize.width * 0.13));
            fractionKeyButton->setAnchorPoint(Point(0.5f,0.0f));
            fractionKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
            fractionKeyButton->setTag(TAG_GAME_KEYFRACTION);
            fractionKeyButton->setScale(screenSize.width * 0.07/fractionKeyButton->getContentSize().width);
            this->addChild(fractionKeyButton);
        }
        
        if(deciamlFlag){
            Button* deciamlButton = Button::create("res/key/decimal.png", "res/key/decimal.png");
            deciamlButton->setPosition(Vec2(screenSize.width*0.95, screenSize.height*0.1f + screenSize.width * 0.18f));
            deciamlButton->setAnchorPoint(Point(0.5f,0.0f));
            deciamlButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
            deciamlButton->setTag(TAG_GAME_KEYDECIMAL);
            deciamlButton->setScale(screenSize.width * 0.07f/deciamlButton->getContentSize().width);
            this->addChild(deciamlButton);
        }
    } else if(axisFlag == 1 || axisFlag == 2){
        auto numberline1Spr = Sprite::Sprite::create(StringUtils::format("res/key/numberline%d.png", axisFlag));
        numberline1Spr->setTag(TAG_GAME_KEYNUMBERLINE1);
        numberline1Spr->setPosition(screenSize.width*0.5, screenSize.height*0.03);
        numberline1Spr->setAnchorPoint(Point(0.5f,0.0f));
        numberline1Spr->setScale(screenSize.width*0.9/numberline1Spr->getContentSize().width);
        this->addChild(numberline1Spr);
    } else if(axisFlag == 3){
        Button* smallKeyButton = Button::create("res/key/left.png", "res/key/left.png");
        smallKeyButton->setPosition(Vec2(screenSize.width*0.3, screenSize.height*0.04f));
        smallKeyButton->setAnchorPoint(Point(0.5f,0.0f));
        smallKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        smallKeyButton->setTag(TAG_GAME_KEYSMALL);
        smallKeyButton->setScale(screenSize.width * 0.07f/smallKeyButton->getContentSize().width);
        this->addChild(smallKeyButton);
        
        Button* equalKeyButton = Button::create("res/key/equal.png", "res/key/equal.png");
        equalKeyButton->setPosition(Vec2(screenSize.width*0.5, screenSize.height*0.04f));
        equalKeyButton->setAnchorPoint(Point(0.5f,0.0f));
        equalKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        equalKeyButton->setTag(TAG_GAME_KEYEQUAL);
        equalKeyButton->setScale(screenSize.width * 0.07f/equalKeyButton->getContentSize().width);
        this->addChild(equalKeyButton);
        
        Button* bigKeyButton = Button::create("res/key/right.png", "res/key/right.png");
        bigKeyButton->setPosition(Vec2(screenSize.width*0.7, screenSize.height*0.04f));
        bigKeyButton->setAnchorPoint(Point(0.5f,0.0f));
        bigKeyButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        bigKeyButton->setTag(TAG_GAME_KEYBIG);
        bigKeyButton->setScale(screenSize.width * 0.07f/bigKeyButton->getContentSize().width);
        this->addChild(bigKeyButton);
    }
}

void GameScene::initProAns(){
    if(fractionFlag>0){
        auto problemImg = Sprite::create("res/game/question1.png"); //here the background.png is a "red screen" png.
        problemImg->setPosition(screenSize.width*0.27, screenSize.height*0.16 + screenSize.width*0.08);
        problemImg->setAnchorPoint(Point(0.0f,0.0f));
        this->addChild(problemImg);
        problemImg->setScale(screenSize.width*0.27/problemImg->getContentSize().width);
        
        if(axisFlag !=0){
        } else {
            auto answerImg = Sprite::create("res/game/answer1.png"); //here the background.png is a "red screen" png.
            answerImg->setPosition(screenSize.width*0.75, screenSize.height*0.16 + screenSize.width*0.08);
            answerImg->setAnchorPoint(Point(1.0f,0.0f));
            answerImg->setTag(TAG_GAME_ANSWERIMG);
            this->addChild(answerImg);
            answerImg->setScale(screenSize.width*0.15/answerImg->getContentSize().width);
        }
    } else {
        auto problemImg = Sprite::create("res/game/problem.png"); //here the background.png is a "red screen" png.
        problemImg->setPosition(screenSize.width*0.27, screenSize.height*0.16 + screenSize.width*0.08);
        problemImg->setAnchorPoint(Point(0.0f,0.0f));
        this->addChild(problemImg);
        problemImg->setScale(screenSize.width*0.27/problemImg->getContentSize().width);
        
        auto answerImg = Sprite::create("res/game/answer.png"); //here the background.png is a "red screen" png.
        answerImg->setPosition(screenSize.width*0.75, screenSize.height*0.16 + screenSize.width*0.08);
        answerImg->setAnchorPoint(Point(1.0f,0.0f));
        answerImg->setTag(TAG_GAME_ANSWERIMG);
        this->addChild(answerImg);
        answerImg->setScale(screenSize.width*0.15/answerImg->getContentSize().width);
    }
    
    this->makeproblem();
    this->makeproblem();
}

void GameScene::initTimerScore(){
    auto timerLabel = Label::createWithSystemFont("0", "", screenSize.width*0.035);
    timerLabel->setColor(Color3B::GREEN);
    timerLabel->setPosition(screenSize.width*0.28, screenSize.height - screenSize.width*0.047);
    timerLabel->setTag(TAG_GAME_TIMER);
    this->addChild(timerLabel);
    
    auto scoreLabel = Label::createWithSystemFont("", "", screenSize.width*0.035);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setPosition(screenSize.width*0.5, screenSize.height - screenSize.width*0.06);
    scoreLabel->setTag(TAG_GAME_SCORE);
    this->addChild(scoreLabel);
    
    
    auto levelLabel = Label::createWithSystemFont(StringUtils::format("%d", level), "", screenSize.width*0.035);
    levelLabel->setColor(Color3B::BLACK);
    levelLabel->setPosition(screenSize.width*0.75, screenSize.height - screenSize.width*0.047);
    levelLabel->setTag(TAG_GAME_LEVEL);
    this->addChild(levelLabel);
}


void GameScene::update(float delta)
{
    problemTime+=delta;
    musicTime += delta;
    
    if(startingTapFlag && !tapenteranimFlag && !levelCompleteFlag) {
        waittingTaptimer += delta;
    }
    
    if(waittingTaptimer > 2 && !tapenteranimFlag) {
        onTapAnimation();
    }
    if(onkeyswipeFlag && !levelCompleteFlag){
        taptimer+=delta;
    }
    
    if(taptimer > 2 && tapentertimeFlag && onkeyswipeFlag){
        taptimer = 0;
        UserDefault::getInstance()->setIntegerForKey("swipeflag", true);
        onSwipeAnimation();
    }
    
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
        auto timerLabel = (Label*)this->getChildByTag(TAG_GAME_TIMER);
        if(timer > targettime1 && timer < targettime){
            timerLabel->setColor(Color3B::YELLOW);
        } else if(timer >= targettime){
            timerLabel->setColor(Color3B::RED);
        }
        timerLabel->setString(StringUtils::format("%d", timer));
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
    
    if(fractionFlag>0 && !deciamlFlag){
        std::stringstream test(StringUtils::format("%s", answerArray[rightCount].c_str()));
        std::string segment;
        std::vector<std::string> seglist;
        
        while(std::getline(test, segment, '/'))
        {
            seglist.push_back(segment);
        }
        answer = 1;
        showFractionAnswer(atoi(seglist[0].c_str()));
        onClickDividerKey();
        showFractionAnswer(atoi(seglist[1].c_str()));
        
    } else if(deciamlFlag){
        answer = 1;
        showDecimalAnswer1(answerArray[rightCount]);
    } else {
        auto inseadAns = atoi(answerArray[rightCount].c_str());
        answer = atoi(answerArray[rightCount].c_str());
        showAnswer(inseadAns);
    }
    onShowedOneAnimFlag = true;
    auto oneAnimTitle = Sprite::create("res/animation/answer-this-one.png");
    oneAnimTitle->setTag(TAG_GAME_ONESPR);
    
    oneAnimTitle->setScale(screenSize.width*0.25/oneAnimTitle->getContentSize().width);
    oneAnimTitle->setAnchorPoint(Vec2(0.5, 1));
    this->addChild(oneAnimTitle);
    
    auto oneAnimhand = Sprite::create("res/animation/taphand.png");
    oneAnimhand->setTag(TAG_GAME_ONEANIM);
    oneAnimhand->setScale(screenSize.width*0.13/oneAnimhand->getContentSize().width);
    oneAnimhand->setAnchorPoint(Vec2(0, 0.8));
    this->addChild(oneAnimhand);
    
    if(fractionFlag>0){
        oneAnimTitle->setPosition(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.3);
        oneAnimhand->setPosition(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.16);
    }
    else {
        oneAnimTitle->setPosition(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.27);
        oneAnimhand->setPosition(screenSize.width*0.43, screenSize.height*0.16 + screenSize.width*0.12);
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
        answerLayer->setPosition(screenSize.width*0.75, screenSize.height*0.16 + screenSize.width*0.08);
        answerLayer->setTag(TAG_GAME_ANSWERLABEL);
        this->addChild(answerLayer);
    } else if(fractionFlag>0 && deciamlFlag){
        auto answerlabel = Label::createWithSystemFont("", "", screenSize.width*0.04);
        answerlabel->setColor(Color3B::BLACK);
        answerlabel->setPosition(screenSize.width*0.66, screenSize.height*0.16 + screenSize.width*0.17);
        answerlabel->setTag(TAG_GAME_ANSWERLABEL);
        this->addChild(answerlabel);
        
        auto answerBar = Label::createWithSystemFont("_", "", screenSize.width*0.05);
        answerBar->setColor(Color3B::WHITE);
        answerBar->setPosition(screenSize.width*0.67, screenSize.height*0.16 + screenSize.width*0.21);
        answerBar->setTag(TAG_GAME_ANSWERBAR);
        this->addChild(answerBar);
    } else {
        auto answerlabel = Label::createWithSystemFont("", "", screenSize.width*0.04);
        answerlabel->setColor(Color3B::BLACK);
        answerlabel->setPosition(screenSize.width*0.66, screenSize.height*0.16 + screenSize.width*0.13);
        answerlabel->setTag(TAG_GAME_ANSWERLABEL);
        this->addChild(answerlabel);
    }
}



void GameScene::Fraction26(int mol1, int den1, int mol2, int den2, int order, float offsetPos, std::string op){
    
    auto *problemLayer = (Layer*)this->getChildByTag(TAG_GAME_PROBLEM+order);
    
    if(den1 != 1){
        auto moleculeLabel = Label::createWithSystemFont(StringUtils::format("%d", mol1), "", screenSize.width*0.04);
        moleculeLabel->setColor(Color3B::BLACK);
        moleculeLabel->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.107);
        moleculeLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4);
        problemLayer->addChild(moleculeLabel);
        
        auto denLabel = Label::createWithSystemFont(StringUtils::format("%d", den1), "", screenSize.width*0.04);
        denLabel->setColor(Color3B::BLACK);
        denLabel->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.068);
        denLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +1);
        problemLayer->addChild(denLabel);
        
        auto lineSpr = Sprite::create("res/game/line.png");
        lineSpr->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.085);
        lineSpr->setScale(screenSize.width*0.045/lineSpr->getContentSize().width, screenSize.width*0.003/lineSpr->getContentSize().height);
        
        problemLayer->addChild(lineSpr);
    } else {
        auto moleculeLabel = Label::createWithSystemFont(StringUtils::format("%d", mol1), "", screenSize.width*0.04);
        moleculeLabel->setColor(Color3B::BLACK);
        moleculeLabel->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.085);
        moleculeLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4);
        problemLayer->addChild(moleculeLabel);
        
        auto denLabel = Label::createWithSystemFont(StringUtils::format("%d", den1), "", 0);
        denLabel->setColor(Color3B::BLACK);
        denLabel->setPosition(-screenSize.width*0.09 - 0.04*screenSize.width, screenSize.width*0.068);
        denLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +1);
        problemLayer->addChild(denLabel);
    }
    
    auto moleculeLabel2 = Label::createWithSystemFont(StringUtils::format("%d", mol2), "", screenSize.width*0.04);
    moleculeLabel2->setColor(Color3B::BLACK);
    moleculeLabel2->setPosition(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.107);
    moleculeLabel2->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +2);
    problemLayer->addChild(moleculeLabel2);
    
    auto denLabel2 = Label::createWithSystemFont(StringUtils::format("%d", den2), "", screenSize.width*0.04);
    denLabel2->setColor(Color3B::BLACK);
    denLabel2->setPosition(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.068);
    denLabel2->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 + 3);
    problemLayer->addChild(denLabel2);
    
    auto lineSpr2 = Sprite::create("res/game/line.png");
    lineSpr2->setPosition(-screenSize.width*0.09+0.04*screenSize.width, screenSize.width*0.085);
    lineSpr2->setScale(screenSize.width*0.045/lineSpr2->getContentSize().width, screenSize.width*0.003/lineSpr2->getContentSize().height);
    problemLayer->addChild(lineSpr2);
    
    if(std::strcmp(op.c_str(), "x") == 0){
        auto oplabel = Label::createWithSystemFont("x", "", screenSize.width*0.04);
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
    auto moleculeLabel = Label::createWithSystemFont(StringUtils::format("%d", mol1), "", 0);
    moleculeLabel->setColor(Color3B::BLACK);
    moleculeLabel->setPosition(0, 0);
    moleculeLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4);
    problemLayer->addChild(moleculeLabel);
    
    auto denLabel = Label::createWithSystemFont(StringUtils::format("%d", den1), "", 0);
    denLabel->setColor(Color3B::BLACK);
    denLabel->setPosition(0, 0);
    denLabel->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +1);
    problemLayer->addChild(denLabel);
    
    auto moleculeLabel2 = Label::createWithSystemFont(StringUtils::format("%d", mol1), "", screenSize.width*0.04);
    moleculeLabel2->setColor(Color3B::BLACK);
    moleculeLabel2->setPosition(-screenSize.width*0.09, screenSize.width*0.107);
    moleculeLabel2->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 +2);
    problemLayer->addChild(moleculeLabel2);
    
    auto denLabel2 = Label::createWithSystemFont(StringUtils::format("%d", den1), "", screenSize.width*0.04);
    denLabel2->setColor(Color3B::BLACK);
    denLabel2->setPosition(-screenSize.width*0.09, screenSize.width*0.068);
    denLabel2->setTag(TAG_GAME_PROBLEM_ELEMENT + order*4 + 3);
    problemLayer->addChild(denLabel2);
    
    auto lineSpr2 = Sprite::create("res/game/line.png");
    lineSpr2->setPosition(-screenSize.width*0.09, screenSize.width*0.085);
    lineSpr2->setScale(screenSize.width*0.045/lineSpr2->getContentSize().width, screenSize.width*0.003/lineSpr2->getContentSize().height);
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
    this->addChild(problemlayer);
    problemlayer->setTag(TAG_GAME_PROBLEM+problemCount);
    if(problemCount == 0 && fractionFlag==0){
        problemlayer->setPosition(screenSize.width*0.52, screenSize.height*0.16 + screenSize.width*0.04);
    } else if(problemCount == 0 && fractionFlag>0){
        problemlayer->setPosition(screenSize.width*0.52, screenSize.height*0.16 + screenSize.width*0.08);
    }else {
        problemlayer->setPosition(screenSize.width*0.34, screenSize.height*0.74-screenSize.width*0.085);
    }
    answerArray[problemCount] = answer1;
    
    switch(fractionFlag){
        case 0:
        {
            auto x1 =  sdata["x1"].asString();
            
            auto problemlabel = Label::createWithSystemFont(x1, "", screenSize.width*0.04);
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
            
            
            auto oplabel = Label::createWithSystemFont("___", "", screenSize.width*0.04);
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
            
            auto oplabel = Label::createWithSystemFont("x", "", screenSize.width*0.04);
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
    wrongCountofOne = 0;
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
    if(wrongCountofOne == 3)
    {
        onOneByOneAnimation();
        wrongCountofOne = 0;
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
    score+=1000;
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
    int accuracyStarCount = 0;
//    if(levelSpeed ==100) speedStarCount = 4;
//    else if(levelSpeed>75 && levelSpeed<=99) speedStarCount = 3;
//    else if(levelSpeed >50 && levelSpeed <=75) speedStarCount = 2;
//    else speedStarCount = 1;
    if(timer <= targettime1) speedStarCount = 4;
    else if(timer>targettime1 && timer<=targettime) speedStarCount = 3;
    else if(timer >targettime && timer <=targettime2) speedStarCount = 2;
    else speedStarCount = 1;
    
    
//    StringUtils::format("res/title/level/level%d.png", newlevel)
    
//    UserDefault::getInstance()->setIntegerForKey("completedLevel",level);
//    int insteadlevel = UserDefault::getInstance()->getIntegerForKey("completedLevel");
    const char *levelstarString = StringUtils::format("level%dstar", level).c_str();
    int starCount = UserDefault::getInstance()->getIntegerForKey(levelstarString, 0);
    if(speedStarCount > starCount) {
        UserDefault::getInstance()->setIntegerForKey(levelstarString,speedStarCount);
    }
    
    if(levelAccuracy ==100) accuracyStarCount = 4;
    else if(levelAccuracy>75 && levelAccuracy<=99) accuracyStarCount = 3;
    else if(levelAccuracy >50 && levelAccuracy <=75) accuracyStarCount = 2;
    else accuracyStarCount = 1;
    
    
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
    reportBg->setScale(screenSize.width*0.76/reportBg->getContentSize().width);
    reportLayer->addChild(reportBg);
    
    //    CCLOG("level %d", level);
    
    
    //Report title
//    if(speedStarCount > 2 && levelAccuracy == 100){
    if(level > completedLevel){
        UserDefault::getInstance()->setIntegerForKey("completedLevel",level);
    }
    if(level > lockLevel && speedStarCount>2){
        UserDefault::getInstance()->setIntegerForKey("lockLevel",level);
    }
    
    if(level<lockLevel || speedStarCount> 2){
        auto reportTitle = Sprite::create("res/report/success_title.png");
        reportTitle->setPosition(screenSize.width*0.52, screenSize.width*0.2+screenSize.height*0.5);
        reportTitle->setScale(screenSize.width*0.45/reportTitle->getContentSize().width);
        
        reportLayer->addChild(reportTitle);
        
        Button* reportContinueButton = Button::create("res/report/report_continue.png", "res/report/report_continue.png");
        reportContinueButton->setPosition(Vec2(screenSize.width*0.52, screenSize.height*0.5 - screenSize.width * 0.205f));
        reportContinueButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        reportContinueButton->setTag(TAG_GAME_REPORTCONTINUE);
        reportContinueButton->setScale(this->screenSize.width * 0.1f/reportContinueButton->getContentSize().width);
        reportLayer->addChild(reportContinueButton);
        
    } else {
        auto reportTitle = Sprite::create("res/report/failure_title.png");
        reportTitle->setPosition(screenSize.width*0.52, screenSize.width*0.2+screenSize.height*0.5);
        reportTitle->setScale(screenSize.width*0.6/reportTitle->getContentSize().width);
        
        reportLayer->addChild(reportTitle);
        
        Button* reportContinueButton = Button::create("res/report/continue_failure.png", "res/report/continue_failure.png");
        reportContinueButton->setPosition(Vec2(screenSize.width*0.52, screenSize.height*0.5 - screenSize.width * 0.205f));
        reportContinueButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
        reportContinueButton->setTag(TAG_GAME_REPORTFAILURE);
        reportContinueButton->setScale(this->screenSize.width * 0.1f/reportContinueButton->getContentSize().width);
        reportLayer->addChild(reportContinueButton);
    }

    
//    Top star
    for(int ii=0; ii<speedStarCount; ii++){
        auto starSpr = Sprite::create("res/report/star.png");
        starSpr->setPosition(screenSize.width*0.54+screenSize.width*0.067*ii , screenSize.height/2+screenSize.width*0.035);
        starSpr->setScale(screenSize.width*0.064/starSpr->getContentSize().width);
        reportLayer->addChild(starSpr);
    }
    // Bottom star
    for(int ii=0; ii<accuracyStarCount; ii++){
        auto starSpr = Sprite::create("res/report/star.png");
        starSpr->setPosition(screenSize.width*0.54+screenSize.width*0.067*ii , screenSize.height/2-screenSize.width*0.048);
        starSpr->setScale(screenSize.width*0.064/starSpr->getContentSize().width);
        reportLayer->addChild(starSpr);
    }
    
    // report buttons
    Button* reportBackButton = Button::create("res/report/report_back.png", "res/report/report_back.png");
    reportBackButton->setPosition(Vec2(screenSize.width*0.34, screenSize.height*0.5 - screenSize.width * 0.205f));
    reportBackButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
    reportBackButton->setTag(TAG_GAME_REPORTBACK);
    reportBackButton->setScale(this->screenSize.width * 0.1f/reportBackButton->getContentSize().width);
    reportLayer->addChild(reportBackButton);
    
    Button* reportExitButton = Button::create("res/report/report_exit.png", "res/report/report_exit.png");
    reportExitButton->setPosition(Vec2(screenSize.width*0.7, screenSize.height*0.5 - screenSize.width * 0.205f));
    reportExitButton->addTouchEventListener(CC_CALLBACK_2(GameScene::onKeyTouchEvent, this));
    reportExitButton->setTag(TAG_GAME_REPORTEXIT);
    reportExitButton->setScale(this->screenSize.width * 0.1f/reportExitButton->getContentSize().width);
    reportLayer->addChild(reportExitButton);

    auto action_0 = MoveTo::create(0.4, Point(0 , screenSize.height*0.1));
    auto action_1 = MoveTo::create(0.1, Point(0 , 0));
    auto action_2 = Sequence::create(action_0, action_1, NULL);
    //    auto action_3 = RepeatForever::create(action_2);
    reportLayer->runAction(action_2);
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
    targetnumber =  sdata["targetnumber"].asInt();
    targettime =  sdata["time2"].asInt();
    targettime1 =  sdata["time1"].asInt();
    targettime2 =  sdata["time3"].asInt();
    
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
    Button* buttonPlay = Button::create("res/title/Continue.png", "res/title/Continue.png");
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
    
    auto levelNumber = Sprite::create(StringUtils::format("res/title/number%d.png", targetnumber));
    levelNumber->setPosition(levelBgPos.x - screenSize.width*0.21, levelBgPos.y - screenSize.width*0.02);
    levelNumber->setScale(screenSize.width*0.08/levelNumber->getContentSize().width);
    
    levelExplainLayer->addChild(levelNumber);
    
    auto levelTime = Sprite::create(StringUtils::format("res/title/timer/timer%d.png", targettime));
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
        //        auto mapScene = MapviewScene::createScene();
        //        Director::getInstance()->replaceScene(mapScene);
        CCLOG("popsecne");
        Director::getInstance()->popScene();
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
        destinationPos = Point(screenSize.width*0.52, screenSize.height*0.16 + screenSize.width*0.08);
    } else {
        destinationPos = Point(screenSize.width*0.52, screenSize.height*0.16 + screenSize.width*0.04);
    }
    
    
    auto action_0 = MoveTo::create(0.7, destinationPos);
    problemLayer->runAction(action_0);
}

void GameScene::gotoHome(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            
            break;
            
        case Widget::TouchEventType::MOVED:
            
            break;
            
        case Widget::TouchEventType::ENDED:
        {
            Director::getInstance()->popScene();
            break;
        }
            
        case Widget::TouchEventType::CANCELED:
            
            break;
            
        default:
            break;
    }

    //    auto mapScene = MapviewScene::createScene();
//    Director::getInstance()->replaceScene(mapScene);
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
                lineSpr->setScale(screenSize.width*0.045/lineSpr->getContentSize().width, screenSize.width*0.003/lineSpr->getContentSize().height);
                //    lineSpr->setTag(TAG_FRACTION_LINE);
                problemLayer->addChild(lineSpr);
                
                auto answerBoxSpr = Sprite::create("res/game/answerboxlayer.png");
                auto ansLabel = Label::createWithSystemFont("", "", screenSize.width*0.03);
                
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
                ansLabel->setPosition(point.x + xx , point.y + yy);
                
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
    
    
    auto oplabel = Label::createWithSystemFont("x", "", screenSize.width*0.04);
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
        Point location = touch->getLocation();
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
        if(isAnswerTouchDown){
            holdCount = 0;
            holdTime = 0.0f;
            if(level == 30) {
                auto answerbar = (Label*)this->getChildByTag(TAG_GAME_ANSWERBAR);
                answerbar->setColor(Color3B::WHITE);
                
            }
            answerSwipeFunc();
        } else if(axisFlag == 1 || axisFlag == 2) {
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
                    numberlineanswer = (screenSize.width*0.5 - answerpos)/(screenSize.width*0.35);
                }
                auto realanswer = atof(answerArray[rightCount].c_str());
                if((realanswer+0.12) > numberlineanswer && (realanswer - 0.12)< numberlineanswer){
                    rightAnswer();
                } else {
                    wrongAnswer();
                }
                
                
                
            }
        } else if(fractionFlag == 4 || level == 20){
            
            if(swipe28Flag == true){
                
                swipe28Flag = false;
                
                if (initialSwipeFractionPos[1] - currentSwipeFractionPos[1] > screenSize.width * 0.06)
                {
                    CCLOG("SWIPED top");
                    fractionSwipeFunc();
                    
                }
                else if (initialSwipeFractionPos[1] - currentSwipeFractionPos[1] < - screenSize.width * 0.06)
                {
                    CCLOG("SWIPED bottom");
                    fractionSwipeFunc();
                    
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





