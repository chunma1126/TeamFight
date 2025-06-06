#include "CameraShakeAction.h"

CameraShakeAction* CameraShakeAction::create(float duration, float strengthX, float strengthY)
{
    CameraShakeAction* ret = new (std::nothrow) CameraShakeAction();
    if (ret && ret->initWithDuration(duration, strengthX, strengthY)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool CameraShakeAction::initWithDuration(float duration, float strengthX, float strengthY)
{
    if (!ActionInterval::initWithDuration(duration))
        return false;

    _strengthX = strengthX;
    _strengthY = strengthY;
    return true;
}

void CameraShakeAction::startWithTarget(cocos2d::Node* target)
{
    ActionInterval::startWithTarget(target);

    _initialX = target->getPositionX();
    _initialY = target->getPositionY();
}

void CameraShakeAction::update(float time)
{
    float randX = ((float)rand() / RAND_MAX - 0.5f) * 2 * _strengthX;
    float randY = ((float)rand() / RAND_MAX - 0.5f) * 2 * _strengthY;

    _target->setPosition(_initialX + randX, _initialY + randY);
}

void CameraShakeAction::stop()
{
    _target->setPosition(_initialX, _initialY);
    ActionInterval::stop();
}
