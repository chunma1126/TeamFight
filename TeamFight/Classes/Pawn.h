#pragma once
#include "Entity.h"
#include "MeleeAttackSkill.h"
class Pawn : public Entity
{
public:
    virtual bool init();
    virtual void update(float dt);
    
    CREATE_FUNC(Pawn);
};

