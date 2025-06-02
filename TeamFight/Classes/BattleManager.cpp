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
        _startTurn = false;

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
    _currentTurn = _turnQueue.front();
    _turnQueue.pop();

    if (_currentTurn == TURN_TYPE::ENEMY)
    {
        _commandQueue.push(new BattleCommand(3.0f, [&]()
            {
                _enemyTeam->getEntity()->playAnimation(ANIMATION_STATE::ATTACK1 , false);
            }));
        _commandQueue.push(new BattleCommand(0.4f, [&]()
            {
                _playerTeam->activeTeam(true);
                _enemyTeam->activeTeam(false);
            }));
    }
    else 
    {
        _usedPlayerCommand = false;
    }
}

void BattleManager::submitPlayerCommand(BattleCommand* cmd)
{
    _usedPlayerCommand = true;
    _commandQueue.push(cmd);
}