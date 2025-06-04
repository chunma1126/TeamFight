#include "Goblin.h"

bool Goblin::init()
{
	if (!Entity::init()) {
		return false;
	}
	initAnimationSheet("Characters/Goblins/Troops/Torch/Blue/Torch_Blue.png", 7, 5);
	getMainSprite()->setFlippedX(true);


	return true;
}

void Goblin::update(float dt)
{
}
