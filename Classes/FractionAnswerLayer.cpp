//
//  FractionAnswerLayer.cpp
//  fibonachi-cpp
//
//  Created by Future on 3/2/17.
//
//

#include "FractionAnswerLayer.h"
using namespace ui;

FractionAnswerLayer::FractionAnswerLayer(int index){
    init(index);
    order = index;
}

FractionAnswerLayer::~FractionAnswerLayer(){
    
}
bool FractionAnswerLayer::init(int index){
    screenSize = Director::getInstance()->getWinSize();
    
    auto moleculeLabel = Label::createWithSystemFont("", "", screenSize.width*0.04);
    moleculeLabel->setColor(Color3B::BLACK);
    moleculeLabel->setPosition(-screenSize.width*0.09, screenSize.width*0.085);
//    moleculeLabel->setPosition(0, 0);
    moleculeLabel->setTag(TAG_FRACTIONANSWER_MOLECULE);
    this->addChild(moleculeLabel);
    return true;
}

void FractionAnswerLayer::onClickDividerKey(){
    
    if(molucle != 0 && !clickedDividerFlag ){
        replaceMolecule();
    }
    clickedDividerFlag = true;
}

void FractionAnswerLayer::onClickNormalKey(int keyValue){
    if(clickedDividerFlag){
        denomentor =denomentor*10 +  keyValue;
        makeDenomentor();
    } else {
        molucle = molucle*10 + keyValue;
        makeMolecule();
    }
}

void FractionAnswerLayer::replaceMolecule() {
    auto moleculeLabel = (Label*)this->getChildByTag(TAG_FRACTIONANSWER_MOLECULE);
    auto action_0 = MoveTo::create(0.1, Point(-screenSize.width*0.09 , screenSize.width*0.107));
    moleculeLabel->runAction(action_0);
    
    auto lineSpr = Sprite::create("res/game/line.png");
    lineSpr->setPosition(-screenSize.width*0.09, screenSize.width*0.085);
    lineSpr->setScale(screenSize.width*0.04/lineSpr->getContentSize().width, screenSize.width*0.003/lineSpr->getContentSize().height);
    lineSpr->setTag(TAG_FRACTIONANSWER_LINE);
    this->addChild(lineSpr);
    lineSprScale = 0.03;
    
    auto denomentorLabel = Label::createWithSystemFont("", "", screenSize.width*0.04);
    denomentorLabel->setColor(Color3B::BLACK);
    denomentorLabel->setPosition(-screenSize.width*0.09, screenSize.width*0.068);
    denomentorLabel->setTag(TAG_FRACTIONANSWER_DENOMINATOR);
    this->addChild(denomentorLabel);
    
}

void FractionAnswerLayer::makeMolecule(){
    auto moleculeLabel = (Label*)this->getChildByTag(TAG_FRACTIONANSWER_MOLECULE);
    moleculeLabel->setString(StringUtils::format("%d", molucle));
}

void FractionAnswerLayer::makeDenomentor(){
    auto denomentorLabel = (Label*)this->getChildByTag(TAG_FRACTIONANSWER_DENOMINATOR);
    denomentorLabel->setString(StringUtils::format("%d", denomentor));
    if(denomentorCount == 0){
        lineSprScale = 0.03;
    } else {
        lineSprScale+=0.025;
    }
    denomentorCount++;
    auto lineSpr = (Sprite*)this->getChildByTag(TAG_FRACTIONANSWER_LINE);
    lineSpr->setScale(screenSize.width*lineSprScale/lineSpr->getContentSize().width, screenSize.width*0.003/lineSpr->getContentSize().height);
}


void FractionAnswerLayer::reset(){
    molucle = 0;
    denomentor = 0;
    clickedDividerFlag = false;
    denomentorCount = 0;
    auto moleculeLabel = (Label*)this->getChildByTag(TAG_FRACTIONANSWER_MOLECULE);
    moleculeLabel->setString("");
    auto action_0 = MoveTo::create(0.1, Point(-screenSize.width*0.09 , screenSize.width*0.085));
    moleculeLabel->runAction(action_0);
    
    auto lineSpr = (Sprite*)this->getChildByTag(TAG_FRACTIONANSWER_LINE);
    this->removeChild(lineSpr);
    
    auto denomentorLabel = (Label*)this->getChildByTag(TAG_FRACTIONANSWER_DENOMINATOR);
    this->removeChild(denomentorLabel);
}






