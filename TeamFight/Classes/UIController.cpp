#include "UIController.h"
#include "Layer.h"

#define BUTTON_INTERVAL 50

UIController::UIController()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 pos = { visibleSize.width * 0.9f + origin.x  , visibleSize.height * 0.15f + origin.y};

	_skillButtons.push_back(ui::Button::create());
	_skillButtons.push_back(ui::Button::create());

	for (int i = 0; i < _skillButtons.size(); i++)
	{
		pos.x -= BUTTON_INTERVAL * i;

		int index = i;
		_skillButtons[i]->addClickEventListener([=](Ref* sender) {
			this->onSkillButtonClicked(index);
			});
		_skillButtons[i]->setPosition(pos);
		_skillButtons[i]->setScale(2.5f);
		Director::getInstance()->getRunningScene()->addChild(_skillButtons[i],LAYER::UI);
	}
	


}

UIController::~UIController()
{
}

void UIController::setSkillIcons(std::vector<std::string> skillIconPathList)
{
	size_t skillIndex = 0;

	for (skillIndex = 0; skillIndex < skillIconPathList.size() && skillIndex < _skillButtons.size(); skillIndex++)
	{
		_skillButtons[skillIndex]->setEnabled(true);

		auto texture = Director::getInstance()->getTextureCache()->addImage(skillIconPathList[skillIndex]);
		texture->setAliasTexParameters();

		_skillButtons[skillIndex]->loadTextureNormal(skillIconPathList[skillIndex]);
		_skillButtons[skillIndex]->setVisible(true); 
	}

	for (; skillIndex < _skillButtons.size(); skillIndex++)
	{
		_skillButtons[skillIndex]->setEnabled(false);
		_skillButtons[skillIndex]->loadTextureNormal("");
		_skillButtons[skillIndex]->setVisible(false);    
	}


}

void UIController::onSkillButtonClicked(int index)
{
	_currentSkillIndex = index;
}

