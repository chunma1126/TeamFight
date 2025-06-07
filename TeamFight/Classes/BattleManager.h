#pragma once
#include <queue>
#include <string>
#include <memory>

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

    void init();
    void update(float dt);
    void runCommand(float dt);
public:
    Entity* selectPlayerEntity();
    Entity* selectEnemyEntity(Vec2 worldMousePos);

    void changeTurn();
    void clearCurrentLevel();
    void gameOver();
    void submitPlayerCommand(BattleCommand* cmd);
    void setTeam(Team* playerTeam , Team* enemyTeam);
    
    void playPlayerTurn(Entity* enemyEntity,int currentSkillIndex);
    void playEnemyTurn();
    
    int getSelectSkillIndex();
public:
    bool canPlayerInput() { return _currentTurn == TURN_TYPE::PLAYER && !_usedPlayerCommand; }
    const char* turnTypeToString(TURN_TYPE turn)
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
    std::unique_ptr<class UIController> _uiController;
private:
    BattleCommand* _currentCommand = nullptr;
    Team* _playerTeam = nullptr;
    Team* _enemyTeam = nullptr;

    Entity* _currentEnemyEntity = nullptr;
    Entity* _currentPlayerEntity = nullptr;

    TURN_TYPE _currentTurn = TURN_TYPE::END;

    bool _canChangeTurn = true;
    bool _usedPlayerCommand = false;

};


