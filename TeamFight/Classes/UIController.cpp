#include "UIController.h"
#include "Enum.h"

#include "cocos2d.h"

#define BUTTON_INTERVAL 50
#define SKILL_TOOLTIP_LABEL_SIZE 7

#define SKILL_TOOLTIP_FADE_IN_DURATION 0.2f
#define SKILL_TOOLTIP_FADE_OUT_DURATION 0.2f

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
	Vec2 skillPos = { visibleSize.width * 0.9f + origin.x  , visibleSize.height * 0.15f + origin.y };

    initSkillButton(skillPos);
    initSkillButtonMouseHover();
}

void UIController::initSkillButton(cocos2d::Vec2& pos)
{
    _skillButtonList.push_back({ ui::Button::create(),Label::createWithTTF("",FONT_HEIROF_BOLD, SKILL_TOOLTIP_LABEL_SIZE),false });
    _skillButtonList.push_back({ ui::Button::create(),Label::createWithTTF("",FONT_HEIROF_BOLD, SKILL_TOOLTIP_LABEL_SIZE),false });

    for (int i = 0; i < _skillButtonList.size(); i++)
    {
        pos.x -= BUTTON_INTERVAL * i;

        int index = i;
        _skillButtonList[i].skillButton->addClickEventListener([=](Ref* sender) {
            onSkillButtonClicked(index);
            });


        _skillButtonList[i].skillButton->setPosition(pos);
        _skillButtonList[i].skillButton->setScale(2.5f);

        _skillButtonList[i].skillTooltipLabel->setPosition({ pos.x,pos.y + 30 });

        Director::getInstance()->getRunningScene()->addChild(_skillButtonList[i].skillButton, LAYER::UI);
        Director::getInstance()->getRunningScene()->addChild(_skillButtonList[i].skillTooltipLabel, LAYER::UI + 100);
    }
}

void UIController::initSkillButtonMouseHover()
{
#if IS_THIS_DEBUG
    auto drawNode = DrawNode::create();
    Director::getInstance()->getRunningScene()->addChild(drawNode, LAYER::UI + 100);
#endif

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = [=](EventMouse* event) {
        Vec2 mousePos = event->getLocationInView();
        bool anyHovered = false;

#if IS_THIS_DEBUG
        drawNode->clear();
#endif

        for (int i = 0; i < _skillButtonList.size(); i++)
        {
            auto& btnInfo = _skillButtonList[i];

            if (!btnInfo.skillButton->isVisible()) {
                btnInfo.hoverState = false;
                continue;
            }

            Vec2 worldPos = btnInfo.skillButton->convertToWorldSpaceAR(Vec2::ZERO);
            Size contentSize = btnInfo.skillButton->getContentSize();
            Size scaledSize = {
                contentSize.width * btnInfo.skillButton->getScaleX(),
                contentSize.height * btnInfo.skillButton->getScaleY()
            };

            Rect rect(
                worldPos.x - scaledSize.width * btnInfo.skillButton->getAnchorPoint().x,
                worldPos.y - scaledSize.height * btnInfo.skillButton->getAnchorPoint().y,
                scaledSize.width,
                scaledSize.height
            );

#if IS_THIS_DEBUG
            Vec2 verts[4] = {
                Vec2(rect.getMinX(), rect.getMinY()),
                Vec2(rect.getMaxX(), rect.getMinY()),
                Vec2(rect.getMaxX(), rect.getMaxY()),
                Vec2(rect.getMinX(), rect.getMaxY())
            };
            Color4F color = btnInfo.hoverState ? Color4F(0, 1, 0, 0.3f) : Color4F(1, 0, 0, 0.2f);
            drawNode->drawSolidPoly(verts, 4, color);
#endif

            if (rect.containsPoint(mousePos))
            {
                if (!btnInfo.hoverState)
                {
                    onSkillButtonHover(i);
                }
                anyHovered = true;
            }
            else if (btnInfo.hoverState)
            {
                btnInfo.hoverState = false;

                auto labelTextFade = FadeOut::create(SKILL_TOOLTIP_FADE_OUT_DURATION);
                auto offVisible = CallFunc::create([i, this]() {
                    _skillButtonList[i].skillTooltipLabel->setVisible(false);
                    });

                auto seq = Sequence::create(labelTextFade, offVisible, nullptr);
                _skillButtonList[i].skillTooltipLabel->stopAllActions();
                _skillButtonList[i].skillTooltipLabel->runAction(seq);
            }
        }
        };

    ResetAllSkillTooltip();

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, Director::getInstance()->getRunningScene());
}

void UIController::update(float dt)
{
    
}

void UIController::setSkillIcons(std::vector<std::string> skillIconPathList)
{
	size_t skillIndex = 0;

    CCASSERT(skillIconPathList.size() <= _skillButtonList.size(), "ERROR: Skill Icon Path list is bigger than Skill Button list!");
    
	for (skillIndex = 0; skillIndex < skillIconPathList.size(); skillIndex++)
	{
        _skillButtonList[skillIndex].skillButton->setEnabled(true);

		auto texture = Director::getInstance()->getTextureCache()->addImage(skillIconPathList[skillIndex]);
		texture->setAliasTexParameters();

        _skillButtonList[skillIndex].skillButton->loadTextureNormal(skillIconPathList[skillIndex]);
        _skillButtonList[skillIndex].skillButton->setVisible(true);
	}

	for (; skillIndex < _skillButtonList.size(); skillIndex++)
	{
        _skillButtonList[skillIndex].skillButton->setEnabled(false);
        _skillButtonList[skillIndex].skillButton->loadTextureNormal("");
        _skillButtonList[skillIndex].skillButton->setVisible(false);
	}
}

void UIController::onSkillButtonClicked(int index)
{
	_selectSkillIndex = index;
}

void UIController::onSkillButtonHover(int index)
{
	_currentSkillIndex = index;
    _skillButtonList[_currentSkillIndex].hoverState = true;

    auto onVisible = CallFunc::create([=]()
        {
            _skillButtonList[_currentSkillIndex].skillTooltipLabel->setVisible(true);
        });
    auto labelTextFade = FadeIn::create(SKILL_TOOLTIP_FADE_IN_DURATION);

    Sequence* seq = Sequence::create(onVisible,labelTextFade, nullptr);

    _skillButtonList[_currentSkillIndex].skillTooltipLabel->stopAllActions();
    _skillButtonList[_currentSkillIndex].skillTooltipLabel->runAction(seq);

    //CCLOG("%s" , _skillButtonList[_currentSkillIndex].skillTooltipLabel->getString().c_str());
}

void UIController::setSkillTooltipDescription(int index, std::string description)
{
    _skillButtonList[index].skillTooltipLabel->setString(description);
    ResetAllSkillTooltip();
}

void UIController::ResetAllSkillTooltip()
{
    for (auto& buttonInfo : _skillButtonList)
    {
        buttonInfo.hoverState = false;
        buttonInfo.skillTooltipLabel->setVisible(false);
        buttonInfo.skillTooltipLabel->setOpacity(0);
    }
}

