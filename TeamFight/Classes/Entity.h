#pragma once
#include "cocos2d.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

#include "StatController.h"
#include "Skill.h"
#include "HealthBar.h"

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

enum class ENTITY_TYPE
{
    KNIGHT,
    ARCHER,
    PAWN,
    PLAYER_ENTITY_END,
    GOBLIN,
    ENEMY_ENEITY_END
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
    virtual ~Entity();
    virtual bool init();
    void tryDead(float value);
    virtual void update(float dt);

    CREATE_FUNC(Entity);
public:
    void playAnimation(ANIMATION_STATE state, bool loop = false, float animationSpeed = 1, CallFunc* animationEndCallback = nullptr);
    virtual void initAnimationSheet(const std::string& path, int row, int col,ANIMATION_STATE animationState = ANIMATION_STATE::ATTACK2);

public:
    std::vector<Skill*> getSkillList() const { return _skillList; }
    Skill* getSkill(int index) const { return _skillList[index]; }
    
    Sprite* getMainSprite() const { return _mainSprite; }
    StatController* getStatController() const { return _statController.get(); }

protected:
    void setDeadAnimationSheet();
    void setAnimationSheet(float frameHeight, float frameWidth, int animationCount, Texture2D* animationSheets, ANIMATION_STATE defaultEndState);
    AnimationSheetInfo getAnimationSheetInfo(const std::string& path);
protected:
    Sprite* _mainSprite; 
    std::vector<Skill*> _skillList;

    std::unique_ptr<StatController> _statController;
    std::unordered_map<ANIMATION_STATE, Vector<SpriteFrame*>> _animator;

    AnimationSheetInfo _animationSheetInfo = {};
    float _animationSheetFrameWidth = 0;
    float _animationSheetFrameHeight = 0;

    HealthBar* _healthBar;
};


