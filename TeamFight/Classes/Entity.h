#pragma once
#include "cocos2d.h"
#include <map>
#include <unordered_map>
#include <memory>

#include "StatController.h"

USING_NS_CC;

enum class ANIMATION_STATE 
{
    IDLE,
    MOVE,
    ATTACK1,
    ATTACK2,
    DEAD,
    END
};

class StatController;

class Entity : public Node
{
public :
    virtual bool init();
    virtual void update(float dt);

    CREATE_FUNC(Entity);
    void playAnimation(ANIMATION_STATE state, bool loop = true);
    virtual void setAnimationSheet(const std::string& path);
private:
    Sprite* _sprite; 
    
    std::unique_ptr<StatController> _statController ;
    std::unordered_map<ANIMATION_STATE, Vector<SpriteFrame*>> _animator;
};


