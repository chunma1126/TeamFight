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
    Skill() = default;
    virtual ~Skill() = default;

    virtual void execute(Entity* caster, Entity* target) = 0;
    

    // Getters
    const std::string& getSkillName() const { return _name; }
    const std::string& getIconPath() const { return _iconPath; }
    int getPower() const { return _power; }
    SKILL_TYPE getType() const { return _type; }
    const std::string& getDescription() const { return _description; }

    // Setters
    void setSkillName(const std::string& name) { _name = name; }
    void setPower(int power) { _power = power; }
    void setType(SKILL_TYPE type) { _type = type; }
    void setIconPath(const std::string& path) { _iconPath = path; }
    void setDescription(const std::string& description) { _description = description; }
protected:
    virtual void applyDamage(Entity* caster, Entity* target);
protected:
    std::string _name;
    int _power = 0;
    SKILL_TYPE _type = SKILL_TYPE::END;
    std::string _iconPath;
    std::string _description;
};
