#include "DoubleMeleeAttackSkill.h"
#include "Entity.h"


void DoubleMeleeAttackSkill::execute(Entity* caster, Entity* target)
{
    Vec2 originalPos = caster->getPosition();
    Vec2 enemyPos = target->getPosition();
    enemyPos.x -= caster->getMainSprite()->getContentSize().width / 3;

    auto moveToEnemy = MoveTo::create(0.35f, enemyPos);
    auto attackAnim1 = CallFunc::create([caster]() {
        caster->playAnimation(ANIMATION_STATE::ATTACK2, false, 1.2f);
        });
    auto delay1 = DelayTime::create(0.3f);  
    auto applyDmg1 = CallFunc::create([this, caster, target]() {
        applyDamage(caster, target);
        });
    auto attackAnim2 = CallFunc::create([caster]() {
        caster->playAnimation(ANIMATION_STATE::ATTACK1, false, 1.2f);
        });
    auto delay2 = DelayTime::create(0.3f);
    auto applyDmg2 = CallFunc::create([this, caster, target]() {
        applyDamage(caster, target);
        });
    auto moveBack = MoveTo::create(0.4f, originalPos);

    auto sequence = Sequence::create(
        moveToEnemy,
        attackAnim1,
        delay1,
        applyDmg1,
        delay1->clone(),
        attackAnim2,
        delay2,
        applyDmg2,
        delay2->clone(),
        moveBack,
        nullptr
    );

    caster->runAction(sequence);
}
