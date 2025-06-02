#pragma once
#include "Entity.h"
class Archer : public Entity
{
public:
    virtual bool init();
    virtual void update(float dt);

    CREATE_FUNC(Archer);
    virtual void initAnimationSheet(const std::string& path, int row, int col, ANIMATION_STATE animationState = ANIMATION_STATE::DEAD) override;
};

