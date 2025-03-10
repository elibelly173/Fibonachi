/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __UIEDITBOXIMPLTIZEN_H__
#define __UIEDITBOXIMPLTIZEN_H__

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN)

#include "ui/UIEditBox/UIEditBoxImpl.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

class Label;

namespace ui {

class EditBox;

class EditBoxImplTizen : public EditBoxImpl
{
public:
    /**
     * @js NA
     */
    EditBoxImplTizen(EditBox* pEditText);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxImplTizen();

    virtual void draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) {};

    virtual bool initWithSize(const Size& size);
    virtual void setFont(const char* pFontName, int fontSize);
    virtual void setFontColor(const Color4B& color);
    virtual void setPlaceholderFont(const char* pFontName, int fontSize);
    virtual void setPlaceholderFontColor(const Color4B& color);
    virtual void setInputMode(EditBox::InputMode inputMode);
    virtual void setInputFlag(EditBox::InputFlag inputFlag);
    virtual void setMaxLength(int maxLength);
    virtual void setTextHorizontalAlignment(cocos2d::TextHAlignment alignment) { };
    virtual int  getMaxLength();
    virtual void setReturnType(EditBox::KeyboardReturnType returnType);
    virtual bool isEditing();

    virtual void setText(const char* pText);
    virtual const char* getText(void);
    virtual void setPlaceHolder(const char* pText);
    virtual void setPosition(const Vec2& pos);
    virtual void setVisible(bool visible);
    virtual void setContentSize(const Size& size);
    virtual void setAnchorPoint(const Vec2& anchorPoint);
    /**
     * @js NA
     * @lua NA
     */
    virtual void visit(void);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onEnter(void);
    virtual void doAnimationWhenKeyboardMove(float duration, float distance);
    virtual void openKeyboard();
    virtual void closeKeyboard();

private:
    Label* _label;
    Label* _labelPlaceHolder;
    EditBox::InputMode    _editBoxInputMode;
    EditBox::InputFlag    _editBoxInputFlag;
    EditBox::KeyboardReturnType  _keyboardReturnType;

    std::string _text;
    std::string _placeHolder;

    Color4B _colText;
    Color4B _colPlaceHolder;

    int   _maxLength;
    Size _editSize;
};


}

NS_CC_END

#endif /* #if (CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) */

#endif /* __UIEDITBOXIMPLTIZEN_H__ */

