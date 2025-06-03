#include "BattleManager.h"
#include "cocos2d.h"

BattleManager::BattleManager()
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

void BattleManager::setTeam(Team* playerTeam, Team* enemyTeam)
{
    _playerTeam = playerTeam;
    _enemyTeam = enemyTeam;
}

void BattleManager::update(float dt)
{
    if (_turnQueue.empty())
    {
        CCLOG("turn queue is empty");
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
    if (_commandQueue.empty() && !_turnQueue.empty() && _startTurn)
    {
        changeTurn();
        return;
    }

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
        _startTurn = true;
        _currentCommand = _commandQueue.front();
        _commandQueue.pop();
        _currentCommand->start();
    }

}

void BattleManager::changeTurn()
{
    _startTurn = false;

    _currentTurn = _turnQueue.front();
    _turnQueue.pop();

    if (_currentTurn == TURN_TYPE::ENEMY)
    {
        _commandQueue.push(new BattleCommand(2.1f, [&]()
            {
                _enemyTeam->getEntity()->playAnimation(ANIMATION_STATE::ATTACK1 , false);
            }));
        _commandQueue.push(new BattleCommand(0.4f, [&]()
            {
                _playerTeam->activeTeam(true);
                _enemyTeam->activeTeam(false);
            }));
    }
    else if(_currentTurn == TURN_TYPE::PLAYER)
    {
        _currentPlayerEntity = selectPlayerEntity();
        _usedPlayerCommand = false;
    }
}

Entity* BattleManager::selectPlayerEntity()
{
    Entity* entity = _playerTeam->getEntity();
    CCLOG("%s", typeid(*entity).name());

    auto sizeUpEvent = ScaleTo::create(0.1f, 1.1f);
    entity->runAction(sizeUpEvent);

    return entity;
}

Entity* BattleManager::selectEnemyEntity(Vec2 worldMousePos)
{
    for (const auto& entity : _enemyTeam->getAllEntities())
    {
        Rect entityRect = entity->getMainSprite()->getBoundingBox();
        Vec2 localPos = entity->convertToNodeSpace(worldMousePos);

        if (entityRect.containsPoint(localPos))
        {
            return entity;
        }

    }

    return nullptr;
}

void BattleManager::PlayPlayerTurn(Entity* enemyEntity)
{
    submitPlayerCommand(new BattleCommand(0.1f, [&]()
        {
            for (const auto& entity : _playerTeam->getAllEntities())
            {
                ScaleTo* scaleResizeAction = ScaleTo::create(0.1f, 1);
                entity->runAction(scaleResizeAction);
            }
        }));

    submitPlayerCommand(new BattleCommand(2.1f, [=]()
        {
            _currentPlayerEntity->getSkill()->execute(_currentPlayerEntity, enemyEntity);
        }));

    submitPlayerCommand(new BattleCommand(0.1f, [&]()
        {
            _playerTeam->activeTeam(false);
            _enemyTeam->activeTeam(true);
        }));
}

void BattleManager::submitPlayerCommand(BattleCommand* cmd)
{
    _usedPlayerCommand = true;
    _commandQueue.push(cmd);
}