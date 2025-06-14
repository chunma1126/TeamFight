#include "cocos2d.h"
#include "BattleManager.h"
#include "EnemySpawner.h"
#include "UIController.h"
#include "RewardManager.h"
#include "TurnController.h"
#include "TeamController.h"
#include "CommandController.h"
#include "SelectController.h"

#include "Enum.h"
#include <random>

#define LEVEL_CLEAR_DELAY 2.0f

BattleManager::BattleManager()
{

}

BattleManager::~BattleManager() 
{
    
}

void BattleManager::init() 
{
    _uiController = std::make_unique<UIController>();
    _enemySpawner = std::make_unique<EnemySpawner>();
    _rewardManager = std::make_unique<RewardManager>();
    _turnController = std::make_unique<TurnController>();
    _teamController = std::make_unique<TeamController>();
    _commandController = std::make_unique<CommandController>();
    _selectController = std::make_unique<SelectController>();

    _commandController->init(
        _turnController.get(),
        _teamController.get(),
        _uiController.get(),
        _selectController.get());

    _selectController->init(_teamController.get(), _uiController.get());

    _commandController->onLevelClearEvent.add([this](float duration)
        {
            clearCurrentLevel(duration);
        });

    this->initRewardButtons();
}

void BattleManager::update(float dt) 
{
    _uiController->update(dt);

    if (_turnController->isQueueEmpty()) {
        _turnController->fillDefaultTurns();
    }
    _commandController->runCommand(dt);
}

void BattleManager::clearCurrentLevel(float duration)
{
    auto scene = cocos2d::Director::getInstance()->getRunningScene();
    CCASSERT(scene, "ERROR : has not scene!!!");

    _teamController->getEnemyTeam()->clearEntities();

    for (auto* entity : _teamController->getPlayerTeam()->getAliveEntities())
    {
        entity->playAnimation(ANIMATION_STATE::MOVE, true);
    }

    auto delay = DelayTime::create(duration);
    auto animationEvent = CallFunc::create([this]() 
    {
        for (auto* entity : _teamController->getPlayerTeam()->getAliveEntities()) {
            entity->playAnimation(ANIMATION_STATE::IDLE, true);
        }
    });

    auto enemySpawn = CallFunc::create([this]()
    {
        _commandController->setChangeTurn(true);
        _teamController->spawnEnemyTeam();
    });

    auto seq = Sequence::create(delay, animationEvent, enemySpawn, nullptr);
    scene->runAction(seq);
}

void BattleManager::initRewardButtons() 
{
    auto buttons = _uiController->getRewardButtons();
    for (auto& button : buttons) {
        Reward* newReward = _rewardManager->getReward();
        button->setClickCallback([=]() {
            newReward->setTragetTeam(_teamController->getPlayerTeam().get());
            newReward->execute();

            _uiController->setActiveRewardBackground(false);
            _uiController->setActiveRewardButtons(false);

            _commandController->onLevelClearEvent.invoke(LEVEL_CLEAR_DELAY);

            button->hideTooltip();
            });

        button->setTooltipText(typeid(*newReward).name());
    }
}

int BattleManager::getSelectSkillIndex() 
{
    return _uiController->getSelecSkillIndex();
}

bool BattleManager::getCanPlayerInput() 
{
    return _turnController->currentTurn() == TURN_TYPE::PLAYER && !_commandController->getUsedPlayerCommand();
}

void BattleManager::setTeamPositions(std::vector<Vec2>& playerTeamPosition, std::vector<Vec2>& enemyTeamPosition)
{
    _teamController->initPlayerTeam(playerTeamPosition);
    _teamController->initEnemyTeam(enemyTeamPosition, _enemySpawner.get());
}


