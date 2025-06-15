#include "CommandController.h"
#include "BattleCommand.h"
#include "TurnController.h"
#include "TeamController.h"
#include "UIController.h"
#include "SelectController.h"

CommandController::CommandController()
{
     
}

CommandController::~CommandController()
{
    if (_currentCommand) {
        delete _currentCommand;
        _currentCommand = nullptr;
    }

    while (!_commandQueue.empty()) {
        delete _commandQueue.front();
        _commandQueue.pop();
    }
}

void CommandController::init(TurnController* turnController, TeamController* teamController, UIController* uiController, SelectController* selectController)
{
    _turnController = turnController;
    _teamController = teamController;
    _uiController = uiController;
    _selectController = selectController;
}

void CommandController::update(float dt)
{
    if (_currentCommand != nullptr) {
        _currentCommand->update(dt);

        if (_currentCommand->isEnd()) {
            _currentCommand->reset();
            delete _currentCommand;
            _currentCommand = nullptr;
        }
    }

    if (_currentCommand == nullptr && !_commandQueue.empty()) {
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

void CommandController::executePlayerTurn(Entity* enemyEntity, int currentSkillIndex)
{
    _usedPlayerCommand = true;

    submitPlayerCommand(
        new BattleCommand(0.1f, [&]()
            {
                for (const auto& entity : _teamController->getPlayerTeam()->getAllEntities())
                {
                    entity->runAction(ScaleTo::create(0.1f, 1));
                }
            }));

    submitPlayerCommand(
        new BattleCommand(2.7f, [=]()
            {
                _currentPlayerEntity->getSkill(currentSkillIndex)->execute(_currentPlayerEntity, enemyEntity);
            }));
}

void CommandController::gameOver()
{
    _teamController->getPlayerTeam()->clearEntities();
}

void CommandController::changeTurn()
{
    _canChangeTurn = false;
    _turnController->nextTurn();

    if (_teamController->isPlayerTeamDead())
    {
        gameOver();
        onGameOverEvent.invoke(true);
    }
    else if (_teamController->isEnemyTeamDead())
    {
        _uiController->setActiveRewardBackground(true);
        _uiController->setActiveRewardButtons(true);
    }
    else if (_turnController->currentTurn() == TURN_TYPE::ENEMY)
    {
        _teamController->setEnemyTeamActive(true);
        _teamController->setPlayerTeamActive(false);

        executeEnemyTurn();
    }
    else if (_turnController->currentTurn() == TURN_TYPE::PLAYER) 
    {
        _usedPlayerCommand = false;
        _currentPlayerEntity = _selectController->selectPlayerEntity();
        _uiController->setSelectSkillIndex(-1);

        int skillCount = _currentPlayerEntity->getSkillList().size();
        for (int i = 0; i < skillCount; ++i) {
            _uiController->setSkillTooltipDescription(i, _currentPlayerEntity->getSkill(i)->getDescription());
        }

        _teamController->setEnemyTeamActive(false);
        _teamController->setPlayerTeamActive(true);
    }
}

void CommandController::executeEnemyTurn()
{
    submitPlayerCommand(new BattleCommand(2.1f, [&]()
        {
            Entity* entity = _teamController->getEnemyEntity();

            int skillCount = entity->getSkillList().size();
            int randomSkillIndex = std::rand() % skillCount;

            auto alivePlayers = _teamController->getAlivePlayers();
            int randomIndex = std::rand() % alivePlayers.size();

            Entity* target = alivePlayers[randomIndex];
            entity->getSkill(randomSkillIndex)->execute(entity, target);
        }));
}