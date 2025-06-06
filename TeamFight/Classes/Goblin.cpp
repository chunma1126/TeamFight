#include "Goblin.h"
#include "MeleeAttackSkill.h"

bool Goblin::init()
{
	if (!Entity::init()) {
		return false;
	}
	initAnimationSheet("Characters/Goblins/Troops/Torch/Blue/Torch_Blue.png", 7, 5);
	getMainSprite()->setFlippedX(true);

	auto* meleeAttackSkill = new MeleeAttackSkill;
	meleeAttackSkill->setPower(10);
	meleeAttackSkill->setType(SKILL_TYPE::DAMAGE);

	_skillList.push_back(meleeAttackSkill);

	return true;
}

void Goblin::update(float dt)
{
}
