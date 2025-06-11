#include "BattleManager.h"
#include "EnemySpawner.h"

#include "cocos2d.h"

#include <random>

#define LEVEL_CLEAR_DELAY 2.0f

BattleManager::BattleManager()
{
    onLevelClearEvent.add([this](float delayDuration)
    {
        auto scene = cocos2d::Director::getInstance()->getRunningScene();
        CCASSERT(scene , "ERROR : has not scene!!!");

        auto delay = DelayTime::create(delayDuration);
        auto animationEvent = CallFunc::create([this]()
                {
                    for (auto* entity : _playerTeam->getAliveEntities())
                    {
                        entity->playAnimation(ANIMATION_STATE::IDLE, true);
                    }
                });
        auto enemySpawn = CallFunc::create([this]()
                {
                    _canChangeTurn = true;
                    EnemySpawn();
                });
        auto seq = Sequence::create(delay, animationEvent, enemySpawn, nullptr);
        
        scene->runAction(seq);
    });
    
}

BattleManager::~BattleManager()
{
    if (_currentCommand)
    {
        delete _currentCommand;
        _currentCommand = nullptr;
    }

    while (!_commandQueue.empty())
    {
        delete _commandQueue.front();
        _commandQueue.pop();
    }

}

void BattleManager::init()
{
    _uiController = std::make_unique<UIController>();
    _enemySpawner = std::make_unique<EnemySpawner>();

    _playerTeam = std::make_unique<Team>();
    _enemyTeam = std::make_unique<Team>();

    _playerTeam->addEntity(ENTITY_TYPE::KNIGHT, Knight::create());
    _playerTeam->addEntity(ENTITY_TYPE::ARCHER, Archer::create());
    _playerTeam->addEntity(ENTITY_TYPE::PAWN, Pawn::create());

    for (int i = 0; i < _playerTeam->getAllEntities().size(); i++)
    {
        Entity* entity = _playerTeam->getEntity((ENTITY_TYPE)i);
        entity->setPosition(_playerTeamPosition[i]);

        cocos2d::Director::getInstance()->getRunningScene()->addChild(entity);
    }

    this->EnemySpawn();
}

void BattleManager::EnemySpawn()
{
    for (int i = 0; i < (int)ENTITY_TYPE::PLAYER_ENTITY_END; i++)
    {
        Entity* entity = _enemySpawner->EnemySpawn(_enemyTeamPosition[i]);
        _enemyTeam->addEntity(ENTITY_TYPE::GOBLIN, entity);
    }
}

void BattleManager::update(float dt)
{
    _uiController->update(dt);

    if (_turnQueue.empty())
    {
        _turnQueue.push(TURN_TYPE::PLAYER);
        _turnQueue.push(TURN_TYPE::ENEMY);

        _turnQueue.push(TURN_TYPE::PLAYER);
        _turnQueue.push(TURN_TYPE::ENEMY);

        _turnQueue.push(TURN_TYPE::PLAYER);
        _turnQueue.push(TURN_TYPE::ENEMY);

        _turnQueue.push(TURN_TYPE::PLAYER);
        _turnQueue.push(TURN_TYPE::ENEMY);
    }
    runCommand(dt);
}

void BattleManager::runCommand(float dt)
{
    if (_currentCommand != nullptr)
    {
        _currentCommand->update(dt);

        if (_currentCommand->isEnd())
        {
            _currentCommand->reset();
            delete _currentCommand;
            _currentCommand = nullptr;
        }
    }

    if (_currentCommand == nullptr && !_commandQueue.empty())
    {
        _canChangeTurn = true;
        _currentCommand = _commandQueue.front();
        _commandQueue.pop();
        _currentCommand->start();
    }

    if (_currentCommand == nullptr && _commandQueue.empty() && _canChangeTurn)
    {
        changeTurn();
    }

}

void BattleManager::changeTurn()
{
    _canChangeTurn = false;
    _currentTurn = _turnQueue.front();
    _turnQueue.pop();

    if (_playerTeam->isAllDead())
    {
        gameOver();

        onGameOverEvent.invoke(true);
    }
    else if (_enemyTeam->isAllDead())
    {
        clearCurrentLevel();

        onLevelClearEvent.invoke(LEVEL_CLEAR_DELAY);
    }
    else if (_currentTurn == TURN_TYPE::ENEMY)
    {
        _enemyTeam->setActiveTeam(true);
        _playerTeam->setActiveTeam(false);

        executeEnemyTurn();

    }
    else if(_currentTurn == TURN_TYPE::PLAYER)
    {
        _usedPlayerCommand = false;
        _currentPlayerEntity = selectPlayerEntity();
        _uiController->setSelectSkillIndex(-1);

        int skillCount = _currentPlayerEntity->getSkillList().size();
        for (int i = 0; i < skillCount; i++)
        {
            _uiController->setSkillTooltipDescription(i , _currentPlayerEntity->getSkill(i)->getDescription());
        }

        _enemyTeam->setActiveTeam(false);
        _playerTeam->setActiveTeam(true);
    }
}

void BattleManager::clearCurrentLevel()
{
    _enemyTeam->clearEntities();

    for (const auto& player : _playerTeam->getAliveEntities())
    {
        player->playAnimation(ANIMATION_STATE::MOVE,true);
    }
}

void BattleManager::gameOver()
{
    _playerTeam->clearEntities();
}

Entity* BattleManager::selectPlayerEntity()
{
    Entity* entity = _playerTeam->getEntity();

    auto sizeUpEvent = ScaleTo::create(0.1f, 1.15f);
    entity->runAction(sizeUpEvent);

    std::vector<std::string> skillPaths;
    for (const auto& skill : entity->getSkillList())
    {
        skillPaths.push_back(skill->getIconPath()); 
    }

    _uiController->setSkillIcons(skillPaths);
    
    return entity;
}

Entity* BattleManager::selectEnemyEntity(Vec2 worldMousePos)
{
    for (const auto& entity : _enemyTeam->getAliveEntities())
    {
        Rect entityRect = entity->getMainSprite()->getBoundingBox();

        entityRect.origin.x += entityRect.size.width / 4;
        entityRect.origin.y += entityRect.size.height / 4;
        entityRect.size.width /= 2;
        entityRect.size.height /= 2;

        Vec2 localPos = entity->convertToNodeSpace(worldMousePos);

        if (entityRect.containsPoint(localPos))
        {
            return entity;
        }
    }

    return nullptr;
}

void BattleManager::executeEnemyTurn()
{
    submitPlayerCommand(new BattleCommand(2.1f, [&]()
    {
        Entity* entity;
        entity = _enemyTeam->getEntity();

        int skillCount = entity->getSkillList().size();
        int randomSkillIndex = std::rand() % skillCount;

        int playerEntityIndex = _playerTeam->getAliveEntities().size();
        int randomEntityIndex = std::rand() % playerEntityIndex;

        Entity* target = _playerTeam->getAliveEntities()[randomEntityIndex];
        entity->getSkill(randomSkillIndex)->execute(entity, target);
    }));
}

void BattleManager::setTeamPositions(std::vector<Vec2>& playerTeamPosition, std::vector<Vec2>& enemyTeamPosition)
{
    _playerTeamPosition = playerTeamPosition;
    _enemyTeamPosition = enemyTeamPosition;
}

void BattleManager::executePlayerTurn(Entity* enemyEntity,int currentSkillIndex)
{
    _usedPlayerCommand = true;

    submitPlayerCommand(new BattleCommand(0.1f, [&]()
    {
        for (const auto& entity : _playerTeam->getAllEntities())
        {
            ScaleTo* scaleResizeAction = ScaleTo::create(0.1f, 1);
            entity->runAction(scaleResizeAction);
        }
    }));

    submitPlayerCommand(new BattleCommand(2.7f, [=]()
    {
        _currentPlayerEntity->getSkill(currentSkillIndex)->execute(_currentPlayerEntity, enemyEntity);
    }));

}