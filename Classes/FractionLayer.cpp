//
//  FractionLayer.cpp
//  fibonachi-cpp
//
//  Created by Future on 3/1/17.
//
//

#include "FractionLayer.h"
using namespace ui;

FractionLayer::FractionLayer(int molecule, int denomentor, float offset, bool flag1){
    mol = molecule;
    den = denomentor;
    offsetPos = offset;
    allowswipeFlag = flag1;
    init();
}

FractionLayer::~FractionLayer(){
    
}
bool FractionLayer::init(){
    screenSize = Director::getInstance()->getWinSize();
    
    auto moleculeLabel = Label::createWithSystemFont(StringUtils::format("%d", mol), "", screenSize.width*0.04);
    moleculeLabel->setColor(Color3B::BLACK);
    moleculeLabel->setPosition(-screenSize.width*0.09+offsetPos*screenSize.width, screenSize.width*0.107);
    //    moleculeLabel->setPosition(0, 0);
    moleculeLabel->setTag(TAG_FRACTION_MOLECULE);
    this->addChild(moleculeLabel);
    
    auto denLabel = Label::createWithSystemFont(StringUtils::format("%d", den), "", screenSize.width*0.04);
    denLabel->setColor(Color3B::BLACK);
    denLabel->setPosition(-screenSize.width*0.09+offsetPos*screenSize.width, screenSize.width*0.068);
    //    moleculeLabel->setPosition(0, 0);
    denLabel->setTag(TAG_FRACTION_DENOMINATOR);
    this->addChild(denLabel);
    
    auto lineSpr = Sprite::create("res/game/line.png");
    lineSpr->setPosition(-screenSize.width*0.09+offsetPos*screenSize.width, screenSize.width*0.085);
    lineSpr->setScale(screenSize.width*0.045/lineSpr->getContentSize().width, screenSize.width*0.003/lineSpr->getContentSize().height);
    lineSpr->setTag(TAG_FRACTION_LINE);
    this->addChild(lineSpr);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(FractionLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(FractionLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(FractionLayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(FractionLayer::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

bool FractionLayer::onTouchBegan(Touch *touch, Event *event)
{
//    CCLOG("xxxlocation = %f", touch->getLocation().x);
        return true;
}

void FractionLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}

void FractionLayer::onTouchEnded(Touch *touch, Event *event)
{
    Point location = touch->getLocation();
    auto molLabel1 = (Label*)this->getChildByTag(TAG_FRACTION_MOLECULE);
    Rect molLabel1Rect = molLabel1->getBoundingBox();
                    CCLOG("xxxmax = %f", molLabel1Rect.getMaxX());
                    CCLOG("xxxmin = %f", molLabel1Rect.getMinX());
                    CCLOG("xxxlocation = %f", location.x);
    if(molLabel1Rect.containsPoint(location)){
        CCLOG("aaaa");
    }
}

void FractionLayer::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}


