#pragma once
#include "Skill.h"

class RangeSkill : public Skill
{
public:
	void execute(Entity* caster, Entity* target) override;
};

