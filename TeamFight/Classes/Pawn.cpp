#include "Pawn.h"

bool Pawn::init()
{
    if (!Entity::init())
    {
        return false;
    }


    initAnimationSheet("Characters/Knights/Troops/Pawn/Red/Pawn_Red.png", 6, 6);
    return true;
}

void Pawn::update(float dt)
{
}
