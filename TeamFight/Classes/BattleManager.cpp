#include "BattleManager.h"
#include "UIController.h"
#include "cocos2d.h"

BattleManager::BattleManager()
{
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

void BattleManager::init()
{
    _uiController = std::make_unique<UIController>();
}

void BattleManager::setTeam(Team* playerTeam, Team* enemyTeam)
{
    _playerTeam = playerTeam;
    _enemyTeam = enemyTeam;
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

    if (_currentTurn == TURN_TYPE::ENEMY)
    {
        playEnemyTurn();

        _enemyTeam->activeTeam(true);
        _playerTeam->activeTeam(false);
    }
    else if(_currentTurn == TURN_TYPE::PLAYER)
    {
        _currentPlayerEntity = selectPlayerEntity();
        _usedPlayerCommand = false;

        int skillCount = _currentPlayerEntity->getSkillList().size();
        for (int i = 0; i < skillCount; i++)
        {
            _uiController->setSkillTooltipDescription(i , _currentPlayerEntity->getSkill(i)->getDescription());
        }

        _enemyTeam->activeTeam(false);
        _playerTeam->activeTeam(true);
    }
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
    for (const auto& entity : _enemyTeam->getAllEntities())
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
        _enemyTeam->getEntity()->playAnimation(ANIMATION_STATE::ATTACK1, false);
    }));
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


