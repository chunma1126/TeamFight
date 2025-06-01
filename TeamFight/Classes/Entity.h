#pragma once
#include "cocos2d.h"
#include <map>
#include <memory>
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
    CREATE_FUNC(Entity);
    void playAnimation(ANIMATION_STATE state, bool loop = true);
    virtual void setAnimationSheet(const std::string& path);
private:
    Sprite* _sprite; 
    
    std::unique_ptr<StatController> _statController ;
    std::unordered_map<ANIMATION_STATE, Vector<SpriteFrame*>> _animator;
};


