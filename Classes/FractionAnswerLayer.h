//
//  FractionAnswerLayer.h
//  fibonachi-cpp
//
//  Created by Future on 3/2/17.
//
//

#ifndef FractionAnswerLayer_h
#define FractionAnswerLayer_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include <stdlib.h>
using namespace std;

USING_NS_CC_EXT;
USING_NS_CC;
#define TAG_FRACTIONANSWER_MOLECULE      500
#define TAG_FRACTIONANSWER_DENOMINATOR      501
#define TAG_FRACTIONANSWER_LINE      502
class FractionAnswerLayer : public cocos2d::Layer{
public:
    
    FractionAnswerLayer(int index);
    ~FractionAnswerLayer();
    virtual bool init(int index);
    void reset();
    void onClickDividerKey();
    void replaceMolecule();
    void onClickNormalKey(int keyValue);
    void makeMolecule();
    void makeDenomentor();
    
//    CREATE_FUNC(FractionAnswerLayer);
    
public:
    int order = 0;
    int molucle = 0;
    int denomentor = 0;
    int denomentorCount = 0;
    float lineSprScale = 0.0f;
    bool clickedDividerFlag = false;
    cocos2d::Size screenSize;
    
};


#endif /* FractionAnswerLayer_hpp */
