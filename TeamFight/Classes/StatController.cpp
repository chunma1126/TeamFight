#include "StatController.h"
#include "CameraShakeAction.h"

#include <algorithm>
#include <cocos2d.h>

StatController::StatController()
{
    init();
}

StatController::~StatController()
{

}

void StatController::init()
{
    _stats[STAT_TYPE::ATK] = Stat(0.0f);
    _stats[STAT_TYPE::DEF] = Stat(0.0f);
    _stats[STAT_TYPE::SPD] = Stat(0.0f);
    _stats[STAT_TYPE::HP] = Stat(0.0f);

    _stats[STAT_TYPE::HP].onChangeValueEvent.add([&](float value)
        {
            auto camShake = CameraShakeAction::create(0.1f, 1.2f, 1.2f);

            auto camera = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
            if (camera)
            {
                camera->stopAllActions(); 
                camera->runAction(camShake);
            }
        });

}

void StatController::update(float dt)
{
    //CCLOG("hp : %f" , _stats[STAT_TYPE::HP].getValue());
}

void StatController::setDefaultStat(STAT_TYPE stat, float amount)
{
    _stats[stat].setValue(amount);
}

void StatController::addStat(STAT_TYPE stat, float amount)
{
    _stats[stat].addStat(amount);
}

void StatController::removeStat(STAT_TYPE stat, float amount)
{
    _stats[stat].removeStat(amount);
}

const float StatController::getValue(STAT_TYPE stat) 
{
    return _stats[stat].getValue();
}