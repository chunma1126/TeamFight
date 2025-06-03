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
	
	auto delay = DelayTime::create(0.9f);
	auto animation = CallFunc::create([caster]()
		{
			caster->playAnimation(ANIMATION_STATE::ATTACK1, false);
		});
	auto moveBack = MoveTo::create(0.4f, originalPos);
	auto sequence = Sequence::create(animation, delay, moveBack, nullptr);

	caster->runAction(sequence);
}
