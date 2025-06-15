#include "TurnController.h"
#include "TeamController.h"
#include "Entity.h"

TurnController::TurnController() : _currentTurn(TURN_TYPE::END) 
{

}

void TurnController::init(TeamController* teamController)
{
    _teamController = teamController;
}

void TurnController::clearTurn()
{
    while (!_turnQueue.empty())
    {
        _turnQueue.pop();
    }
}

void TurnController::fillDefaultTurns()
{
    std::vector<std::pair<int, TURN_TYPE>> turnCandidates;

    for (const auto& player : _teamController->getAlivePlayers())
    {
        int spd = player->getStatController()->getValue(STAT_TYPE::SPD);
        turnCandidates.push_back({ spd, TURN_TYPE::PLAYER });
    }

    for (const auto& enemy : _teamController->getAliveEnemies())
    {
        int spd = enemy->getStatController()->getValue(STAT_TYPE::SPD);
        turnCandidates.push_back({ spd, TURN_TYPE::ENEMY });
    }

    std::sort(turnCandidates.begin(), turnCandidates.end(),
        [](const std::pair<int, TURN_TYPE>& a, const std::pair<int, TURN_TYPE>& b)
        {
            return a.first > b.first; 
        });

    for (const auto& candidate : turnCandidates)
    {
        _turnQueue.push(candidate.second);
    }
}

TURN_TYPE TurnController::nextTurn() 
{
    if (!_turnQueue.empty())
    {
        _currentTurn = _turnQueue.front();
        _turnQueue.pop();
    }
    else 
    {
        _currentTurn = TURN_TYPE::END;
    }
    return _currentTurn;
}

bool TurnController::isQueueEmpty() const
{
    return _turnQueue.empty();
}

TURN_TYPE TurnController::currentTurn() const 
{
    return _currentTurn;
}
