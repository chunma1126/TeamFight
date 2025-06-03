#include "Knight.h"

bool Knight::init()
{
    if (!Entity::init())
    {
        return false;
    }

    initAnimationSheet("Characters/Knights/Troops/Warrior/Red/Warrior_Red.png", 6, 8);

    _statController->setDefaultStat(STAT_TYPE::ATK, 7.5f);
    _statController->setDefaultStat(STAT_TYPE::SPD, 10);
    _statController->setDefaultStat(STAT_TYPE::DEF, 15);
    _statController->setDefaultStat(STAT_TYPE::HP, 20);

    skil = new MeleeAttackSkill("Dragon Slash", 7, SKILL_TYPE::DAMAGE);

    return true;
}

void Knight::update(float dt)
{
}
