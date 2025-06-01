#include "StatController.h"
#include <algorithm>


StatController::StatController()
{
    init();
}

StatController::~StatController()
{

}

void StatController::init()
{
    _stats[STAT_TYPE::ATK] = Stat(1.0f);
    _stats[STAT_TYPE::DEF] = Stat(1.0f);
    _stats[STAT_TYPE::SPD] = Stat(1.0f);
    _stats[STAT_TYPE::HP] = Stat(1.0f);
}

void StatController::update(float dt)
{
    
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