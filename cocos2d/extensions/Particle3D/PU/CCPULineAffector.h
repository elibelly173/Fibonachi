/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015 Chukong Technologies Inc.
 
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


#ifndef __CC_PU_PARTICLE_3D_LINE_AFFECTOR_H__
#define __CC_PU_PARTICLE_3D_LINE_AFFECTOR_H__

#include "extensions/Particle3D/PU/CCPUAffector.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

class  CC_DLL PULineAffector : public PUAffector
{
public:
    // Constants
    static const float DEFAULT_MAX_DEVIATION;
    static const float DEFAULT_TIME_STEP;
    static const Vec3 DEFAULT_END;
    static const float DEFAULT_DRIFT;

    static PULineAffector* create();

        /**
    */
    virtual void notifyRescaled(const Vec3& scale) override;
    virtual void preUpdateAffector(float deltaTime) override;
    virtual void updatePUAffector(PUParticle3D *particle, float deltaTime) override;
    virtual void postUpdateAffector(float deltaTime) override;
    virtual void firstParticleUpdate(PUParticle3D *particle, float deltaTime) override;
    /** 
    */
    float getMaxDeviation(void) const;
    void setMaxDeviation(float maxDeviation);

    /** 
    */
    const Vec3& getEnd(void) const;
    void setEnd(const Vec3& end);

    /** 
    */
    float getTimeStep(void) const;
    void setTimeStep(float timeStep);

    /** 
    */
    float getDrift(void) const;
    void setDrift(float drift);

    virtual void copyAttributesTo (PUAffector* affector) override;

CC_CONSTRUCTOR_ACCESS:          
    PULineAffector(void);
    virtual ~PULineAffector(void);

protected:

    float _maxDeviation;
    float _scaledMaxDeviation;
    Vec3 _end;
    float _timeSinceLastUpdate;
    float _timeStep;
    float _drift;
    float _oneMinusDrift;
    bool _update;
    bool _first;
};
NS_CC_END

#endif