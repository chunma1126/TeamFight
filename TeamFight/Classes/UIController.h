#pragma once

#include <vector>
#include "cocos2d.h"
#include "JYDButton.h"

USING_NS_CC;

class UIController 
{
public:
    UIController();
    ~UIController();

    void init();
    void update(float dt);

    void setSkillIcons(const std::vector<std::string>& icons);

    void setSkillTooltipDescription(int index, const std::string& description);
    void ResetAllSkillTooltip();

    int getSelecSkillIndex() const { return _selectSkillIndex; }
    void setSelectSkillIndex(int index) { _selectSkillIndex = index; }

    void setActiveRewardButtons(bool active);
    void setActiveRewardBackground(bool active);

    std::vector<JYDButton*>& getRewardButtons() { return _rewardButtons; }

private:
    void initSkillButton(const cocos2d::Vec2& pos);
    void initRewardButton(const cocos2d::Vec2& pos);
    void initRewardBackground(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin);
private:
    LayerColor* _rewardBackground;

    std::vector<JYDButton*> _skillButtons;
    std::vector<JYDButton*> _rewardButtons;
    std::vector<Sprite*> rewardSprites;


    int _selectSkillIndex = -1;
    int _currentSkillIndex = 1;
};

