#pragma once
#include <queue>

enum class TURN_TYPE
{
    PLAYER,
    ENEMY,
    END
};
class TeamController;
class TurnController {
public:
    TurnController();
    void init(TeamController* teamController);
    void clearTurn();
    void fillDefaultTurns();
    bool isQueueEmpty() const;
    TURN_TYPE nextTurn();
    TURN_TYPE currentTurn() const;

private:
    std::queue<TURN_TYPE> _turnQueue;
    TURN_TYPE _currentTurn;
    TeamController* _teamController;
};
