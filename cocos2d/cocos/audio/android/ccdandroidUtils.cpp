/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.

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
#include "audio/android/ccdandroidUtils.h"

#include <jni.h>
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#include "platform/CCFileUtils.h"


USING_NS_CC;

namespace CocosDenshion {
    namespace android {
        std::string getFullPathWithoutAssetsPrefix(const char* pszFilename) {
            // Changing file path to full path
            std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(pszFilename);
            // Removing `assets` since it isn't needed for the API of playing sound.
            size_t pos = fullPath.find("assets/");
            if (pos == 0)
            {
                fullPath = fullPath.substr(strlen("assets/"));
            }
            return fullPath;
        }
    }
}
