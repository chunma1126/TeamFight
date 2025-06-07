#include "Goblin.h"
#include "MeleeAttackSkill.h"

bool Goblin::init()
{
	if (!Entity::init()) {
		return false;
	}
	initAnimationSheet("Characters/Goblins/Troops/Torch/Blue/Torch_Blue.png", 7, 5);
	getMainSprite()->setFlippedX(true);

	getStatController()->setDefaultStat(STAT_TYPE::HP , 1);
	_healthBar->initMaxHealthBar(_statController->getValue(STAT_TYPE::HP));

	auto* meleeAttackSkill = new MeleeAttackSkill;
	meleeAttackSkill->setPower(5);
	meleeAttackSkill->setType(SKILL_TYPE::DAMAGE);

	_skillList.push_back(meleeAttackSkill);

	return true;
}

void Goblin::update(float dt)
{
}
