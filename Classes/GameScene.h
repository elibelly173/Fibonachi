//
//  GameScene.hpp
//  fibonachi-cpp
//
//  Created by Future on 2/18/17.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include <stdlib.h>
#include "SimpleAudioEngine.h"
using namespace std;

USING_NS_CC_EXT;
USING_NS_CC;

#define TAG_GAME_DIMLAYER      49
#define TAG_SPRITE_ACHI      50
#define TAG_SPRITE_FIBO      51
#define TAG_GAME_VINEYET      52
#define TAG_GAME_REPORTLAYER      53
#define TAG_GAME_TAPSPR      54
#define TAG_GAME_TAPANIM      55
#define TAG_GAME_SWIPEANIM      56
#define TAG_GAME_SWIPESPR      57
#define TAG_GAME_ONEANIM      58
#define TAG_GAME_ONESPR      59
#define TAG_GAME_NEXTLAYER      60

#define TAG_GAME_CANCELFRANIM      157
#define TAG_GAME_CANCELFRANIM1      158
#define TAG_GAME_CANCELFRSPR      159
#define TAG_GAME_TAPFRANIM      160
#define TAG_GAME_TAPFRSPR      161

#define TAG_GAME_NLINEANIM      162
#define TAG_GAME_NLINESPR      163
#define TAG_GAME_PROBLEM      1000
#define TAG_GAME_PROBLEM_ELEMENT      1100
#define TAG_GAME_ANSWERLAYER      100
#define TAG_GAME_ANSWERIMG      101
#define TAG_GAME_ANSWERLABEL      102
#define TAG_GAME_ANSWERBAR      103
#define TAG_GAME_KEY      201
#define TAG_GAME_KEYADD      211
#define TAG_GAME_KEYFRACTION      212
#define TAG_GAME_KEYNUMBERLINE1      213
#define TAG_GAME_KEYNUMBERLINE2      214
#define TAG_GAME_KEYSMALL      215
#define TAG_GAME_KEYEQUAL      216
#define TAG_GAME_KEYBIG      217
#define TAG_GAME_KEYDECIMAL      218
#define TAG_GAME_NEXTLEVEL      219
#define TAG_GAME_CLOSE      220
#define TAG_GAME_KEYDIVIDER 300


#define TAG_GAME_REPORTBACK      251
#define TAG_GAME_REPORTCONTINUE      252
#define TAG_GAME_REPORTFAILURE      253
#define TAG_GAME_REPORTEXIT      254

#define TAG_GAME_TIMER      61
#define TAG_GAME_SCORE      62
#define TAG_GAME_LEVEL      63


#define TAG_GAME_MOLANS1      64
#define TAG_GAME_DENANS1      65
#define TAG_GAME_MOLANS2      66
#define TAG_GAME_DENANS2      67

#define TAG_GAME_MOLANS1LABEL      68
#define TAG_GAME_DENANS1LABEL      69
#define TAG_GAME_MOLANS2LABEL      70
#define TAG_GAME_DENANS2LABEL      71
class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int level);
    
    
    virtual bool init();
    void playMusic();
    void initTicks();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    void UpdateTimer(float dt);
    void update(float delta);
    void initFlags();
    void initScreen();
    void initKey();
    void initFiboAchi();
    void achianim();
    void fiboanim();
    void getLevelProblems();
    void initProAns();
    void makeproblem();
    
    void addTick(int order);
    
    void Fraction26(int mol1, int den1,int mol2, int den2, int order, float offset, std::string op);
    void Fraction20(int mol2, int den2, int order);
    void makineAnsSpr();
    void initanswerLayer();
    void initTimerScore();
    void rightAnswer();
    void wrongAnswer();
    void enterAnswer();
    void updateScore();
    void showAnswerBox(int ans);
    void showAnswer(int ans);
    void showFractionAnswer(int keyValue);
    void showDecimalAnswer(int keyValue);
    void showDecimalAnswer1(std::string insteadAns);
    void removeProblem(int order);
    void animationProblem(int order);
    void onShowReportLayer();
    void onRemoveReportLayer(int status);
    void onClickDividerKey();
    void onClickDeciamlKey();
    void convertDividertoMultiSign();
    
    
    void CompareNumber(int ans);
    // left-right
    void answerSwipeFunc();
    // top - bottom
    void fractionSwipeFunc();
    
    void onTapFractionItem(Touch *touch);
    void onTapAnimation();
    void removeTapAnimation();
    void onSwipeAnimation();
    void removeSwipeAnimation();
    
    void onOneByOneAnimation();
    void removeOneByOneAnimation();
    
    void onCancelFrAnim();
    void removeCancelFrAnim();
    
    void onTapFrAnim();
    void removeTapFrAnim();
    
    void onNlineAnim();
    void removeNlineAnim();
        
    void reportCallback(cocos2d::Ref* sender, int status);
    void onKeyTouchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void gotoHome(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    
    void nextLevel();
    void onIntroduceLevel(cocos2d::Ref* sender);
    void getLevelInfo();
    void onRemoveIntroduceLevel(bool activeFlag);
    void onShowDimLayer();
    void onRemoveDimLayer();
public:
    cocos2d::Size screenSize;
    ValueVector arrLevelsProblems;
    CocosDenshion::SimpleAudioEngine *audio;
       
    ValueVector arrTicks;
    int level;
    int timer = 0;
    int score = 0;
    int rightCount=0;
    int problemCount= 0;
    int wrongCount = 0;
    std::string answerArray[200];
    std::string answerString = "";
    int answer= 0;
    int targettime = 0;
    int targetnumber = 0;
    int targettime1 = 0;
    int targettime2 = 0;
    
    bool isAnswerTouchDown;
    int is_Negative = 1;
    float problemTime= 0.0f;
    
    int ticksCount=0;
    
    
    
    float initialTouchPos[2];
    float currentTouchPos[2];
    
    float initialSwipeFractionPos[2];
    float currentSwipeFractionPos[2];
    
    float initialAnswerTouchPos[2];
    float currentAnswerTouchPos[2];
    int clickedKeyValue;
    int clickedkeycount=0;
    bool fractionBoxArray[4];
    int selectedAnswerBox = 0;
    
    
    float levelSpeed, levelAccuracy;
    int completedLevel;
    int lockLevel;
    
    float waittingTaptimer = 0.0f;
    bool startingTapFlag = false;
    float taptimer = 0.0f;
    float swipetimer = 0.0f;
    
    ValueVector arrLevels;
    
    int holdnowVal=0;
    int holdpreVal = 0;
    int holdCount = 0;
    bool holdFlag = false;
    float holdTime = 0.0f;
    
    float musicTime = 0.0f;
    
//    Flags
    bool levelCompleteFlag = false;
    int fractionFlag = 0;
    bool deciamlFlag = 0;
    bool addKeyFlag = false;
    int axisFlag = 0;
    bool clickedDividerKeyFlag = false;
    bool level28Flag = false;
    bool swipe28Flag = false;
    
    bool fractionSwipeFlagArray[100];
    int tapClickedFlag = 0;
    bool onshowedTapAnimFlag = false;
    bool onshowedSwipeAnimFlag = false;
    bool onkeyswipeFlag = false;
    int swipeFlag = 0;
    
    bool onShowedOneAnimFlag = false;
    
    bool onshowedCancelFrAnimFlag = false;
    bool onshowedTapFrAnimFlag = false;
    bool onshowedNlineAnimFlag = false;
    
    bool tapenteranimFlag = false;
    bool tapentertimeFlag = false;
    bool firstEnterFlag = false;
    bool level20animFlag = false;
    bool level21animFlag = false;
    
    bool nextLevelFlag = false;
    bool dimFlag = false;
    int wrongCountofOne = 0;
    
    bool audioFlag = false;

private:
    CREATE_FUNC(GameScene);
    
    
    
};

#endif /* GameScene_h */
