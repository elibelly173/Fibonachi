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
    getDenSize(denomentor);
    init();
}

FractionLayer::~FractionLayer(){
    
}


void FractionLayer::getDenSize(int denomentor){
    int instead1 = denomentor;
    int instead2 = mol;
    int size1 = 0, size2 = 0;
    while(instead1 > 0){
        instead1 = (int)(instead1/10);
        size1++;
    }
    
    while(instead2 > 0){
        instead2 = (int)(instead2/10);
        size2++;
    }
    
    if(size1>size2){
        fraSize = size1;
    } else {
        fraSize = size2;
    }
}
bool FractionLayer::init(){
    screenSize = Director::getInstance()->getWinSize();
    
    auto moleculeLabel = Label::createWithSystemFont(StringUtils::format("%d", mol), "", screenSize.width*0.04);
    moleculeLabel->setColor(Color3B::BLACK);
    
    //    moleculeLabel->setPosition(0, 0);
    moleculeLabel->setTag(TAG_FRACTION_MOLECULE);
    if(den == 1){
        moleculeLabel->setPosition(-screenSize.width*0.09+offsetPos*screenSize.width, screenSize.width*0.085);
        this->addChild(moleculeLabel);
    } else {
        moleculeLabel->setPosition(-screenSize.width*0.09+offsetPos*screenSize.width, screenSize.width*0.107);
        this->addChild(moleculeLabel);
        auto denLabel = Label::createWithSystemFont(StringUtils::format("%d", den), "", screenSize.width*0.04);
        denLabel->setColor(Color3B::BLACK);
        denLabel->setPosition(-screenSize.width*0.09+offsetPos*screenSize.width, screenSize.width*0.068);
        //    moleculeLabel->setPosition(0, 0);
        denLabel->setTag(TAG_FRACTION_DENOMINATOR);
        this->addChild(denLabel);
        
        auto lineSpr = Sprite::create("res/game/line.png");
        lineSpr->setPosition(-screenSize.width*0.09+offsetPos*screenSize.width, screenSize.width*0.085);
        lineSpr->setScale(screenSize.width*0.025 * fraSize/lineSpr->getContentSize().width, screenSize.width*0.003/lineSpr->getContentSize().height);
        lineSpr->setTag(TAG_FRACTION_LINE);
        this->addChild(lineSpr);
    }
    
    
    return true;
}

bool FractionLayer::onTouchBegan(Touch *touch, Event *event)
{

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


