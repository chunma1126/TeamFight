#pragma once
#include <queue>

enum class TURN_TYPE
{
    PLAYER,
    ENEMY,
    END
};

class TurnController {
public:
    TurnController();

    void fillDefaultTurns();
    TURN_TYPE nextTurn();
    bool isQueueEmpty() const;
    TURN_TYPE currentTurn() const;

private:
    std::queue<TURN_TYPE> _turnQueue;
    TURN_TYPE _currentTurn;
};
