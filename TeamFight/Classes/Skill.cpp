#include "Skill.h"
#include "Entity.h"

Skill::Skill(const std::string& skillName, int skillPower, SKILL_TYPE skillType)
{
	name = skillName;
	power = skillPower;
	type = skillType;
}

void Skill::execute(Entity* caster, Entity* target)
{
	if (type == SKILL_TYPE::DAMAGE) 
	{
		float damage = caster->getStatController()->getValue(STAT_TYPE::ATK);
		damage += power;
		//방어력 적용을 해야함.
		target->getStatController()->removeStat(STAT_TYPE::HP,damage);
	}

	if (type == SKILL_TYPE::HEAL)
	{
		float healAmount = caster->getStatController()->getValue(STAT_TYPE::ATK);
		healAmount += power;
		target->getStatController()->addStat(STAT_TYPE::HP, healAmount);
	}
}
