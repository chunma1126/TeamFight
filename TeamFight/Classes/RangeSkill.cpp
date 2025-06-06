#include "RangeSkill.h"
#include "Entity.h"

void RangeSkill::execute(Entity* caster, Entity* target)
{
    Vec2 originalPos = caster->getPosition();
    Vec2 enemyPos = target->getPosition();
    enemyPos.x -= enemyPos.x / 3;

    auto moveToEnemy = MoveTo::create(0.35f, enemyPos);

    auto playAttackAnim = CallFunc::create([caster]() {
        caster->playAnimation(ANIMATION_STATE::ATTACK1, false);
        });

    auto delay1 = DelayTime::create(0.6f);
    auto delay2 = DelayTime::create(0.4f);
    auto applyDmg = CallFunc::create([caster, target, this]() {
        applyDamage(caster, target);
        });

    auto moveBack = MoveTo::create(0.4f, originalPos);

    auto sequence = Sequence::create(
        moveToEnemy,
        playAttackAnim,
        delay1,
        applyDmg,
        delay2,
        moveBack,
        nullptr
    );

    caster->runAction(sequence);
}
