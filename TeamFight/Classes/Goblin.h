#pragma once
#include "Entity.h"
class Goblin : public Entity
{
public:
    virtual bool init();
    virtual void update(float dt);

    CREATE_FUNC(Goblin);

};

