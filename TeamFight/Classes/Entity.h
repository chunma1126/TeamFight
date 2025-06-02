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

struct AnimationSheetInfo
{
    Texture2D* animationSheet;
    Vec2 contentSize;
};


class StatController;
class Entity : public Node
{
public :
    virtual bool init();
    virtual void update(float dt);

    CREATE_FUNC(Entity);
    void playAnimation(ANIMATION_STATE state, bool loop = true);
    virtual void initAnimationSheet(const std::string& path, int row, int col,ANIMATION_STATE animationState = ANIMATION_STATE::DEAD);
protected:
    void setDeadAnimationSheet();
    void setAnimationSheet(float frameHeight, float frameWidth, int animationCount, Texture2D* animationSheets, ANIMATION_STATE defaultEndState);
    AnimationSheetInfo getAnimationSheetInfo(const std::string& path);
protected:
    Sprite* _sprite; 
    
    std::unique_ptr<StatController> _statController;
    std::unordered_map<ANIMATION_STATE, Vector<SpriteFrame*>> _animator;

    AnimationSheetInfo _animationSheetInfo = {};
    float _animationSheetFrameWidth = 0;
    float _animationSheetFrameHeight = 0;


};


