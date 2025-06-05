#pragma once
#include "Skill.h"

class RangeSkill : public Skill
{
public:
	RangeSkill(const std::string& skillName, int skillPower, SKILL_TYPE skillType, const std::string& skillIconPath);
	virtual ~RangeSkill();
	void execute(Entity* caster, Entity* target) override;
};

