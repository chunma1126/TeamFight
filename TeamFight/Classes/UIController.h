#pragma once
#include <vector>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
struct SkillButtonInfo
{
	cocos2d::ui::Button* skillButton;
	cocos2d::Label* skillTooltipLabel;

	bool hoverState;
};

class UIController
{
public:
	UIController();
	~UIController();

	void init();
	void initSkillButton(cocos2d::Vec2& pos);
	void initSkillButtonMouseHover();
	void update(float dt);

public:
	int getSelecSkillIndex() { return _selectSkillIndex; }
	void setSelectSkillIndex(int index) { _selectSkillIndex = index; }

	int getCurrentSkillIndex() { return _currentSkillIndex; }
	int setCurrentSkillIndex(int index) { _currentSkillIndex = index; }

	void setSkillIcons(std::vector<std::string> skillIconPathList);
	void onSkillButtonClicked(int index);
	void onSkillButtonHover(int index);

	void setSkillTooltipDescription(int index, std::string description);
	void ResetAllSkillTooltip();
private:
	std::vector<SkillButtonInfo> _skillButtonList;

	int _selectSkillIndex = -1;
	int _currentSkillIndex = 1;

};

