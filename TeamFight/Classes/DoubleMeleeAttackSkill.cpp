#include "DoubleMeleeAttackSkill.h"
#include "Entity.h"


void DoubleMeleeAttackSkill::execute(Entity* caster, Entity* target)
{
	applyDamage(caster, target);

	Vec2 originalPos = caster->getPosition();
	Vec2 enemyPos = target->getPosition();
	enemyPos.x -= caster->getMainSprite()->getContentSize().width / 3;

	auto moveToEnemy = MoveTo::create(0.35f, enemyPos);
	auto delay = DelayTime::create(0.9f);
	auto animation = CallFunc::create([caster]()
		{
			caster->playAnimation(ANIMATION_STATE::ATTACK2, false,1.2f);
		});
	auto animation2 = CallFunc::create([caster]()
		{
			caster->playAnimation(ANIMATION_STATE::ATTACK1, false,1.2f);
		});
	auto moveBack = MoveTo::create(0.4f, originalPos);
	auto sequence = Sequence::create(moveToEnemy, animation, delay->clone(), animation2, delay->clone(), moveBack, nullptr);

	caster->runAction(sequence);
}
