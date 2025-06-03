#include "Pawn.h"

bool Pawn::init()
{
    if (!Entity::init())
    {
        return false;
    }

    initAnimationSheet("Characters/Knights/Troops/Pawn/Red/Pawn_Red.png", 6, 6);

    _statController->setDefaultStat(STAT_TYPE::ATK, 10);
    _statController->setDefaultStat(STAT_TYPE::SPD, 5);
    _statController->setDefaultStat(STAT_TYPE::DEF, 20);
    _statController->setDefaultStat(STAT_TYPE::HP, 25);

    skil = new MeleeAttackSkill("Take a ohama", 10, SKILL_TYPE::DAMAGE);

    return true;
}

void Pawn::update(float dt)
{
}
