//
//  FractionLayer.hpp
//  fibonachi-cpp
//
//  Created by Future on 3/1/17.
//
//

#ifndef FractionLayer_h
#define FractionLayer_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

#include <stdlib.h>
using namespace std;

USING_NS_CC_EXT;
USING_NS_CC;

#define TAG_FRACTION_MOLECULE      511
#define TAG_FRACTION_DENOMINATOR      512
#define TAG_FRACTION_LINE      513

class FractionLayer : public cocos2d::Layer{
public:
    
    FractionLayer(int mol, int den, float offset, bool flag1);
    ~FractionLayer();
    virtual bool init();
    void getDenSize(int den);
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    
public:
    int mol;
    int den;
    int fraSize = 0;
    
    float offsetPos = 0.0f;
    bool allowswipeFlag = false;
    cocos2d::Size screenSize;

//    CREATE_FUNC(FractionLayer);

};

#endif /* FractionLayer_h */
