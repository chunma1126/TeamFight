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
    _turnController->init(_teamController.get());

    _commandController->onLevelClearEvent.add([this](float duration)
        {
            clearCurrentLevel(duration);
            initRewardButtons();
        });

    initRewardButtons();
}

void BattleManager::initRewardButtons() 
{
    auto buttons = _uiController->getRewardButtons();

    auto texture = Director::getInstance()->getTextureCache()->addImage("Food.png");
    Size textureSize = texture->getContentSize();
    
    float offsetX = textureSize.width / 8;
    float offsetY = textureSize.height / 8;

    for (auto& button : buttons) 
    {
        Reward* newReward = _rewardManager->getReward();

        button->setClickCallback([=]() 
        {
            newReward->setTragetTeam(_teamController->getPlayerTeam().get());
            newReward->execute();

            _uiController->setActiveRewardBackground(false);
            _uiController->setActiveRewardButtons(false);

            _commandController->onLevelClearEvent.invoke(LEVEL_CLEAR_DELAY);

            button->hideTooltip();
        });

        std::pair<int,int> iconIndex = { newReward->getIconIndex().first , newReward->getIconIndex().second };
        button->setIcon("Food.png", typeid(*newReward).name(), offsetX * iconIndex.first, offsetY * iconIndex.second, offsetX, offsetY);
        button->setTooltipText(newReward->getDescription());
    }

}

void BattleManager::update(float dt) 
{
    if (_turnController->isQueueEmpty()) 
    {
        _turnController->fillDefaultTurns();
    }

    _uiController->update(dt);
    _commandController->update(dt);
}

void BattleManager::clearCurrentLevel(float duration)
{
    _teamController->getEnemyTeam()->clearEntities();

    auto scene = cocos2d::Director::getInstance()->getRunningScene();
    CCASSERT(scene, "ERROR : has not scene!!!");

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
        _turnController->clearTurn();

    });
    auto seq = Sequence::create(delay, animationEvent, enemySpawn, nullptr);
    
    scene->runAction(seq);
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