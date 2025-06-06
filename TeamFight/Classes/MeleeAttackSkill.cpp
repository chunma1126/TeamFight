#include "MeleeAttackSkill.h"
#include "Entity.h"


void MeleeAttackSkill::execute(Entity* caster, Entity* target)
{
	if (_type == SKILL_TYPE::DAMAGE)
	{
		float damage = caster->getStatController()->getValue(STAT_TYPE::ATK);
		damage += _power;
		//방어력 적용을 해야함.
		target->getStatController()->removeStat(STAT_TYPE::HP, damage);
	}

	if (_type == SKILL_TYPE::HEAL)
	{
		float healAmount = caster->getStatController()->getValue(STAT_TYPE::ATK);
		healAmount += _power;
		target->getStatController()->addStat(STAT_TYPE::HP, healAmount);
	}

	Vec2 originalPos = caster->getPosition();
	Vec2 enemyPos = target->getPosition();
	enemyPos.x -= caster->getMainSprite()->getContentSize().width / 3;

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
