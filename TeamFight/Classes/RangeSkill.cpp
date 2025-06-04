#include "RangeSkill.h"
#include "Entity.h"

RangeSkill::RangeSkill(const std::string& skillName, int skillPower, SKILL_TYPE skillType)
	:Skill(skillName , skillPower , skillType)
{
}

RangeSkill::~RangeSkill()
{
}

void RangeSkill::execute(Entity* caster, Entity* target)
{
	Vec2 originalPos = caster->getPosition();
	Vec2 enemyPos = target->getPosition();
	enemyPos.x -= enemyPos.x / 3;

	auto moveToEnemy = MoveTo::create(0.35f, enemyPos);
	auto delay = DelayTime::create(0.9f);
	auto animation = CallFunc::create([caster]()
		{
			caster->playAnimation(ANIMATION_STATE::ATTACK1, false);
		});
	auto moveBack = MoveTo::create(0.4f, originalPos);
	auto sequence = Sequence::create(moveToEnemy,animation, delay, moveBack, nullptr);

	caster->runAction(sequence);
}
