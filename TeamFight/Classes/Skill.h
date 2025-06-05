#pragma once
#include <string>
#include "cocos2d.h"
class Entity;

enum class SKILL_TYPE
{
    DAMAGE,
    HEAL,
    END,
};

class Skill
{
public:
    Skill(const std::string& skillName, int skillPower, SKILL_TYPE skillType, const std::string& skillIconPath);
    virtual ~Skill() = default;
    
    virtual void execute(Entity* caster, Entity* target) = 0;
    const std::string& getSkillName() const { return _name; }
    const std::string& getIconPath() const { return _iconPath; }

protected:
    std::string _name;
    int _power;
    SKILL_TYPE _type;
    const std::string _iconPath;
};
