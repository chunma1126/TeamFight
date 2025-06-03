#pragma once
#include <string>
#include "cocos2d.h"
class Entity;

enum class SKILL_TYPE {
    DAMAGE,
    HEAL,
    END,
};

class Skill
{
public:
    Skill(const std::string& skillName, int skillPower, SKILL_TYPE skillType)
        : name(skillName), power(skillPower), type(skillType) {
    }

    virtual ~Skill() = default;
    virtual void execute(Entity* caster, Entity* target) = 0;
    const std::string& getSkillName() const { return name; }

protected:
    std::string name;
    int power;
    SKILL_TYPE type;
};
