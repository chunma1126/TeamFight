#pragma once

#include <queue>
#include <string>
#include <memory>
#include <vector>

#include "cocos2d.h" 
#include "Entity.h"
#include "Action.h"
#include "BattleCommand.h"

#include "TurnController.h"
#include "UIController.h"
#include "RewardManager.h"
#include "TeamController.h"
#include "EnemySpawner.h"
#include "CommandController.h"
#include "SelectController.h"

class BattleManager 
{
public:
    BattleManager();
    ~BattleManager();

    void init();
    void initRewardButtons();
    void update(float dt);
    void setTeamPositions(std::vector<cocos2d::Vec2>& playerTeamPosition, std::vector<cocos2d::Vec2>& enemyTeamPosition);
public:
    int getSelectSkillIndex();
    bool getCanPlayerInput();
public:
   TurnController* getTurnController() { return _turnController.get(); }
   UIController* getUIController() { return _uiController.get(); }
   RewardManager* getRewardManager() { return _rewardManager.get(); }
   TeamController* getTeamController() { return _teamController.get(); }
   EnemySpawner* getEnemySpawner() { return _enemySpawner.get(); }
   CommandController* getCommandController() { return _commandController.get(); }
   SelectController* getSelectController() { return _selectController.get(); }

private:
    void gameOver();
    void clearCurrentLevel(float duration);
private:
    std::unique_ptr<TurnController> _turnController;
    std::unique_ptr<UIController> _uiController;
    std::unique_ptr<RewardManager> _rewardManager;
    std::unique_ptr<TeamController> _teamController;
    std::unique_ptr<EnemySpawner> _enemySpawner;
    std::unique_ptr<CommandController> _commandController;
    std::unique_ptr<SelectController> _selectController;

};
