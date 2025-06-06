#pragma once
#include "Skill.h"
class MeleeAttackSkill : public Skill
{
public:
	void execute(Entity* caster, Entity* target) override;
private:
	float _direction = 0;
};

