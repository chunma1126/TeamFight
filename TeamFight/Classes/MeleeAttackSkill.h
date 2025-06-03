#pragma once
#include "Skill.h"
class MeleeAttackSkill : public Skill
{
public:
	MeleeAttackSkill(const std::string& skillName, int skillPower, SKILL_TYPE skillType);
	virtual ~MeleeAttackSkill();
	void execute(Entity* caster, Entity* target) override;
};

