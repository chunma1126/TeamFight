#pragma once
#include <cocos2d.h>

USING_NS_CC;
class Entity;
class TeamController;
class UIController;
class SelectController
{
public:
	SelectController();
	void init(TeamController* teamController, UIController* uiController);
public:
	Entity* selectPlayerEntity();
	Entity* selectEnemyEntity(Vec2 worldMousePos);
private:
	TeamController* _teamController;
	UIController* _uiController;
};

