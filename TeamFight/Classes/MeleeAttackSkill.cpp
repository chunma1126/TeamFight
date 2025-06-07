#include "MeleeAttackSkill.h"
#include "Entity.h"

void MeleeAttackSkill::execute(Entity* caster, Entity* target)
{
    Vec2 originalPos = caster->getPosition();
    Vec2 enemyPos = target->getPosition();

    _direction = (originalPos - enemyPos).getNormalized().x;
    enemyPos.x += _direction * caster->getMainSprite()->getContentSize().width / 3;
    
    auto moveToEnemy = MoveTo::create(0.35f, enemyPos);
    auto animation = CallFunc::create([caster]() {
        caster->playAnimation(ANIMATION_STATE::ATTACK1, false);
        });
    auto delay1 = DelayTime::create(0.3f);
    auto applyDmg = CallFunc::create([this, caster, target]() {
        applyDamage(caster, target);
        });

    auto delay2 = DelayTime::create(0.65f);
    auto moveBack = MoveTo::create(0.4f, originalPos);

    auto sequence = Sequence::create(
        moveToEnemy,
        animation,
        delay1,
        applyDmg,
        delay2,
        moveBack,
        nullptr
    );

    caster->runAction(sequence);
}

