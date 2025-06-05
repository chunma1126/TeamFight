#pragma once
#include "Skill.h"
class DoubleMeleeAttackSkill : public Skill
{
public:
	DoubleMeleeAttackSkill(const std::string& skillName, int skillPower, SKILL_TYPE skillType, const std::string& skillIconPath);
	virtual ~DoubleMeleeAttackSkill();
public:
	void execute(Entity* caster, Entity* target) override;
};

