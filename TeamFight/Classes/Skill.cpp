#include "Skill.h"
#include "Entity.h"

Skill::Skill(const std::string& skillName, int skillPower, SKILL_TYPE skillType, const std::string& skillIconPath)
	: _name(skillName), _power(skillPower), _type(skillType) , _iconPath(skillIconPath)
{

}
