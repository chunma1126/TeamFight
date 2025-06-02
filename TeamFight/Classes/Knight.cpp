#include "Knight.h"

bool Knight::init()
{
    if (!Entity::init())
    {
        return false;
    }

    initAnimationSheet("Characters/Knights/Troops/Warrior/Red/Warrior_Red.png", 6, 8);

    return true;
}

void Knight::update(float dt)
{
}
