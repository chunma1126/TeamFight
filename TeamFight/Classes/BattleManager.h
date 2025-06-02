#pragma once
#include <queue>
#include <string>

#include "Team.h"
#include "BattleCommand.h"
enum class TURN_TYPE
{
	PLAYER,
	ENEMY,
	END
};

class BattleManager {
public:
    BattleManager();
    ~BattleManager();

    void setTeam(Team* playerTeam , Team* enemyTeam);

    void submitPlayerCommand(BattleCommand* cmd);
    bool canPlayerInput() { return _currentTurn == TURN_TYPE::PLAYER && !_usedPlayerCommand; }

    void update(float dt);
    void runCommand(float dt);

    void changeTurn();
    std::string TurnTypeToString(TURN_TYPE turn)
    {
        switch (turn)
        {
        case TURN_TYPE::PLAYER: return "PLAYER";
        case TURN_TYPE::ENEMY:  return "ENEMY";
        default:                return "UNKNOWN";
        }
    }
private:
    std::queue<TURN_TYPE> _turnQueue;
    std::queue<BattleCommand*> _commandQueue;
    BattleCommand* _currentCommand = nullptr;
    TURN_TYPE _currentTurn = TURN_TYPE::END;
    Team* _playerTeam;
    Team* _enemyTeam;


    bool _startTurn;
    bool _usedPlayerCommand = false;
};


