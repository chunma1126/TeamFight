#pragma once
#include <string>
class Entity;

enum class SKILL_TYPE {
    DAMAGE,
    HEAL,
    END,
};

class Skill
{
public:
    Skill(const std::string& skillName, int skillPower, SKILL_TYPE skillType);
    void execute(Entity* caster, Entity* target);
public:
    std::string name;
    int power;
    SKILL_TYPE type;
};