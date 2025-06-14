#include "TurnController.h"

TurnController::TurnController() : _currentTurn(TURN_TYPE::END) 
{

}

void TurnController::fillDefaultTurns()
{
    for (int i = 0; i < 4; ++i) {
        _turnQueue.push(TURN_TYPE::PLAYER);
        _turnQueue.push(TURN_TYPE::ENEMY);
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
