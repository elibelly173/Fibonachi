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

#include "CCPUPathFollower.h"
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"

NS_CC_BEGIN

PUPathFollower::PUPathFollower( void )
{

}

PUPathFollower::~PUPathFollower( void )
{

}

//-----------------------------------------------------------------------
void PUPathFollower::addPoint(const Vec3& point)
{
    _spline.addPoint(point);
}
//-----------------------------------------------------------------------
void PUPathFollower::clearPoints (void)
{
    _spline.clear();
}
//-----------------------------------------------------------------------

void PUPathFollower::updatePUAffector( PUParticle3D *particle, float deltaTime )
{
    //for (auto iter : _particleSystem->getParticles())
    {
        //PUParticle3D *particle = iter;
        if (_spline.getNumPoints() > 0)
        {
            // PU 1.4
            float timeLeft = particle->totalTimeToLive - particle->timeToLive;
            float timeFraction = timeLeft / particle->totalTimeToLive;
            float timeFractionPlusDelta = (timeLeft + deltaTime ) / particle->totalTimeToLive;
            timeFractionPlusDelta = timeFractionPlusDelta < 1.0f ? timeFractionPlusDelta : 1.0f;
            Vec3 inter = _spline.interpolate(timeFractionPlusDelta) - _spline.interpolate(timeFraction);
            particle->position.add(_affectorScale.x * inter.x, _affectorScale.y * inter.y, _affectorScale.z * inter.z);
        }
    }
}

PUPathFollower* PUPathFollower::create()
{
    auto ppf = new (std::nothrow) PUPathFollower();
    ppf->autorelease();
    return ppf;
}

void PUPathFollower::copyAttributesTo( PUAffector* affector )
{
    PUAffector::copyAttributesTo(affector);
    PUPathFollower* pathFollower = static_cast<PUPathFollower*>(affector);
    unsigned short numPoints = _spline.getNumPoints();
    pathFollower->_spline.clear();
    for (unsigned short i = 0; i < numPoints; ++i)
    {
        pathFollower->_spline.addPoint(_spline.getPoint(i));
    }
}

NS_CC_END
