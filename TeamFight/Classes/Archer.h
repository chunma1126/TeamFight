#pragma once
#include "Entity.h"
#include <cocos2d.h>

class Archer : public Entity
{
public:
    virtual bool init();
    virtual void update(float dt);

    CREATE_FUNC(Archer);
    virtual void initAnimationSheet(const std::string& path, int row, int col, ANIMATION_STATE animationState = ANIMATION_STATE::DEAD) override;
public:
    cocos2d::Node* getArrow() { return _arrow; }
    cocos2d::Vec2  getArrowPosition() { return _arrowPosition; }
private:
    cocos2d::Node* _arrow;
    cocos2d::Vec2 _arrowPosition;
};

