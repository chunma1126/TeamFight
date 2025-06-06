#pragma once
#include "Skill.h"
class DoubleMeleeAttackSkill : public Skill
{
public:
	void execute(Entity* caster, Entity* target) override;
};

