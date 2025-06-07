#include "Knight.h"
#include "MeleeAttackSkill.h"
#include "DoubleMeleeAttackSkill.h"

#pragma execution_character_set("utf-8")

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

    _healthBar->initMaxHealthBar(_statController->getValue(STAT_TYPE::HP));

    MeleeAttackSkill* meleeAttackSkill = new MeleeAttackSkill();
    meleeAttackSkill->setSkillName("Dragon Slash");
    meleeAttackSkill->setPower(7);
    meleeAttackSkill->setType(SKILL_TYPE::DAMAGE);
    meleeAttackSkill->setIconPath("SkillPack/skill_icon_00.png");
    meleeAttackSkill->setDescription("적을 베어 가릅니다.");
    _skillList.push_back(meleeAttackSkill);

    DoubleMeleeAttackSkill* doubleAttackSkill = new DoubleMeleeAttackSkill();
    doubleAttackSkill->setSkillName("DoubleSlash");
    doubleAttackSkill->setPower(7);
    doubleAttackSkill->setType(SKILL_TYPE::DAMAGE);
    doubleAttackSkill->setIconPath("SkillPack/skill_icon_16.png");
    doubleAttackSkill->setDescription("두번의 공격으로 적을 베어 가릅니다.");
    _skillList.push_back(doubleAttackSkill);


    return true;
}

void Knight::update(float dt)
{
}
