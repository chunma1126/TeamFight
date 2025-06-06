#include "MeleeAttackSkill.h"
#include "Entity.h"


void MeleeAttackSkill::execute(Entity* caster, Entity* target)
{
	applyDamage(caster , target);

	Vec2 originalPos = caster->getPosition();
	Vec2 enemyPos = target->getPosition();

	_direction = (originalPos - enemyPos).getNormalized().x;
	enemyPos.x += _direction * caster->getMainSprite()->getContentSize().width / 3;

	auto moveToEnemy = MoveTo::create(0.35f, enemyPos);
	auto delay = DelayTime::create(0.9f);
	auto animation = CallFunc::create([caster]()
		{
			caster->playAnimation(ANIMATION_STATE::ATTACK1, false);
		});
	auto moveBack = MoveTo::create(0.4f, originalPos);
	auto sequence = Sequence::create(moveToEnemy, animation, delay, moveBack, nullptr);

	caster->runAction(sequence);
}
