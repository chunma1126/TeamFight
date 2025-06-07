#include "BattleManager.h"
#include "UIController.h"
#include "cocos2d.h"
#include "EnemySpawner.h"

#include <random>


#define LEVEL_CLEAR_DELAY 2.0f

BattleManager::BattleManager()
{
    _turnQueue.push(TURN_TYPE::PLAYER);
    _turnQueue.push(TURN_TYPE::ENEMY);

    onLevelClearEvent.add([this](float delayDuration)
        {
            _canChangeTurn = false;

            auto scene = cocos2d::Director::getInstance()->getRunningScene();
            if (scene)
            {
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
            }
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

    _enemyTeam = std::make_unique<Team>();
    _playerTeam = std::make_unique<Team>();

    EnemySpawn();
   

    //init knight
    {
        Knight* entity = Knight::create();
        entity->setPosition(_playerTeamPosition[0]);

        _playerTeam->add(ENTITY_TYPE::KNIGHT, entity);
        cocos2d::Director::getInstance()->getRunningScene()->addChild(entity);

    }

    //init archer
    {
        Archer* entity = Archer::create();
        entity->setPosition(_playerTeamPosition[1]);

        _playerTeam->add(ENTITY_TYPE::ARCHER, entity);
        cocos2d::Director::getInstance()->getRunningScene()->addChild(entity);

    }

    //init pawn
    {
        Pawn* entity = Pawn::create();
        entity->setPosition(_playerTeamPosition[2]);

        _playerTeam->add(ENTITY_TYPE::PAWN, entity);
        cocos2d::Director::getInstance()->getRunningScene()->addChild(entity);

    }
}

void BattleManager::EnemySpawn()
{
    int a = 0;
    for (int i = 0; i < (int)ENTITY_TYPE::PLAYER_ENTITY_END; i++)
    {
        Entity* entity = _enemySpawner->EnemySpawn(_enemyTeamPosition[i]);
        _enemyTeam->add(ENTITY_TYPE::GOBLIN, entity);
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
        _enemyTeam->activeTeam(true);
        _playerTeam->activeTeam(false);

        playEnemyTurn();

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

        _enemyTeam->activeTeam(false);
        _playerTeam->activeTeam(true);
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

void BattleManager::playEnemyTurn()
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

void BattleManager::setPositions(std::vector<Vec2>& playerTeamPosition, std::vector<Vec2>& enemyTeamPosition)
{
    _playerTeamPosition = playerTeamPosition;
    _enemyTeamPosition = enemyTeamPosition;
}

void BattleManager::playPlayerTurn(Entity* enemyEntity,int currentSkillIndex)
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

void BattleManager::submitPlayerCommand(BattleCommand* cmd)
{
    _commandQueue.push(cmd);
}

int BattleManager::getSelectSkillIndex()
{
    return _uiController->getSelecSkillIndex();
}