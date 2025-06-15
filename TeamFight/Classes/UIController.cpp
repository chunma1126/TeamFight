#include "UIController.h"
#include "Enum.h"
#include <string>

#define SKILL_BUTTON_INTERVAL 50
#define SKILL_TOOLTIP_LABEL_SIZE 7

#define RWARD_BUTTON_INTERVAL 95
#define RWARD_BUTTON_SIZE 4.5f

UIController::UIController()
{
    init();
}

UIController::~UIController()
{
}

void UIController::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vec2 skillPos = { visibleSize.width * 0.9f + origin.x, visibleSize.height * 0.15f + origin.y };
    Vec2 rewardPos = { visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y };

    initSkillButton(skillPos);
    initRewardButton(rewardPos);
    initRewardBackground(visibleSize, origin);
}

void UIController::initRewardBackground(const cocos2d::Size& visibleSize, const cocos2d::Vec2& origin)
{
    _rewardBackground = LayerColor::create(Color4B(45, 52, 54, 0), visibleSize.width + origin.x, visibleSize.height + origin.y);
    _rewardBackground->runAction(FadeTo::create(0.4f, 128));
    Director::getInstance()->getRunningScene()->addChild(_rewardBackground, LAYER::UI);

    setActiveRewardBackground(false);
}

void UIController::setActiveRewardButtons(bool active)
{
    for (auto& button : _rewardButtons)
    {
        button->setScale(0.6f);
        button->setVisible(active);
        button->runAction(ScaleTo::create(0.25f , RWARD_BUTTON_SIZE));
    }
}

void UIController::setActiveRewardBackground(bool active)
{
    if (active) 
    {
        _rewardBackground->setVisible(true); 
        _rewardBackground->setOpacity(0);    

        auto fadeIn = FadeTo::create(0.4f, 128);
        _rewardBackground->runAction(fadeIn);
    }
    else {
        auto fadeOut = FadeTo::create(0.4f, 0); 
        auto hide = CallFunc::create([this]() {
            _rewardBackground->setVisible(false);
            });
        auto sequence = Sequence::create(fadeOut, hide, nullptr);
        _rewardBackground->runAction(sequence);
    }
}

void UIController::initSkillButton(const Vec2& startPos)
{
    for (int i = 0; i < 2; ++i) {
        Vec2 pos = startPos - Vec2(i * SKILL_BUTTON_INTERVAL, 0);

        auto btn = JYDButton::create("", "");
        btn->setPosition(pos);
        btn->setScale(2.5f);

        int index = i;
        btn->setClickCallback([=]() {
            _selectSkillIndex = index;
            });

        btn->setHoverCallback([=](bool isEnter) 
        {
            if (isEnter) {
                _currentSkillIndex = index;
                btn->showTooltip();
            }
            else {
                btn->hideTooltip();
            }
        });

        Director::getInstance()->getRunningScene()->addChild(btn,LAYER::UI);
        _skillButtons.push_back(btn);
    }
}

void UIController::initRewardButton(const Vec2& startPos) 
{
    int rewardButtonCount = 3;
    int middleIndex = rewardButtonCount / 2; 
    
    for (int i = 0; i < rewardButtonCount; ++i)
    {
        int offsetIndex = i - middleIndex; 
        Vec2 pos = startPos + Vec2(offsetIndex * RWARD_BUTTON_INTERVAL, 0);

        auto btn = JYDButton::create("", "");
        btn->setPosition(pos);
        btn->setScale(RWARD_BUTTON_SIZE);
        btn->setVisible(false);
        btn->setTooltipColor((Color3B(116, 247, 83)));

        btn->setHoverCallback([=](bool isEnter)
            {
                if (isEnter) {
                    btn->showTooltip();
                }
                else {
                    btn->hideTooltip();
                }
            });

        _rewardButtons.push_back(btn);
        Director::getInstance()->getRunningScene()->addChild(btn,LAYER::UI + 10);
    }
}

void UIController::setSkillIcons(const std::vector<std::string>& icons) {
    CCASSERT(icons.size() <= _skillButtons.size(), "Too many icons");

    for (size_t i = 0; i < _skillButtons.size(); ++i) {
        if (i < icons.size()) {
            _skillButtons[i]->setIcon(icons[i]);
            _skillButtons[i]->setVisible(true);
        }
        else {
            _skillButtons[i]->setVisible(false);
        }
    }
}

void UIController::setSkillTooltipDescription(int index, const std::string& description) {
    if (index < _skillButtons.size()) {
        _skillButtons[index]->setTooltipText(description);
    }
}

void UIController::ResetAllSkillTooltip() 
{
    for (auto btn : _skillButtons) {
        btn->hideTooltip();
    }
}

void UIController::update(float dt) 
{

}
