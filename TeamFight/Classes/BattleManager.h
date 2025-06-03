#pragma once
#include <queue>
#include <string>

#include "Team.h"
#include "BattleCommand.h"
#include "Entity.h"

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
    Entity* selectPlayerEntity();
    Entity* selectEnemyEntity(Vec2 worldMousePos);

    void PlayPlayerTurn(Entity* enemyEntity);

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
    Team* _playerTeam = nullptr;
    Team* _enemyTeam = nullptr;

    Entity* _currentEnemyEntity;
    Entity* _currentPlayerEntity;

    TURN_TYPE _currentTurn = TURN_TYPE::END;

    bool _startTurn;
    bool _usedPlayerCommand = false;
};


