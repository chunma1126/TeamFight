#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;
class UIController
{
public:
	UIController();
	~UIController();
public:
	int getCurrentSkillIndex() { return _currentSkillIndex; }
	void setCurrentSkillIndex(int index) { _currentSkillIndex = index; }

	void setSkillIcons(std::vector<std::string> skillIconPathList);
	void onSkillButtonClicked(int index);
private:
	std::vector<cocos2d::ui::Button*> _skillButtons;
	int _currentSkillIndex = -1;
};

