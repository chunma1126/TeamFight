#pragma once
#include "cocos2d.h"
class CameraShakeAction : public cocos2d::ActionInterval 
{
public:
    static CameraShakeAction* create(float duration, float strengthX, float strengthY);

    bool initWithDuration(float duration, float strengthX, float strengthY);
    void startWithTarget(cocos2d::Node* target) override;
    void update(float time) override;
    void stop() override;

protected:
    float _initialX, _initialY;
    float _strengthX, _strengthY;
};

