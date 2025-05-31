#pragma once
#include "cocos2d.h"
#include <map>
USING_NS_CC;

enum class STATE 
{
    IDLE,
    MOVE,
    ATTACK1,
    ATTACK2,
    ATTACK3,
    DEAD,
};

class Entity : public Node
{
public :
    virtual bool init();
    CREATE_FUNC(Entity);
    void playAnimation(STATE state, bool loop = true);

private:
    Sprite* _sprite; 
    std::unordered_map<STATE, Vector<SpriteFrame*>> _animator;
};


