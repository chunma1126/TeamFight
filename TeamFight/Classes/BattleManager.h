#pragma once
#include <queue>
#include <string>
#include <memory>

#include "BattleCommand.h"
#include "Entity.h"
#include "Action.h"
#include "UIController.h"

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
    void EnemySpawn();
    void update(float dt);
    void runCommand(float dt);
public:
    void setTeamPositions(std::vector<Vec2>& playerTeamPosition , std::vector<Vec2>& enemyTeamPosition);
    void executePlayerTurn(Entity* enemyEntity,int currentSkillIndex);
   
public:
    const char* turnTypeToString(TURN_TYPE turn)
    {
        switch (turn)
        {
        case TURN_TYPE::PLAYER: return "PLAYER";
        case TURN_TYPE::ENEMY:  return "ENEMY";
        default:                return "UNKNOWN";
        }
    }
    Entity* selectPlayerEntity();
    Entity* selectEnemyEntity(Vec2 worldMousePos);

    int getSelectSkillIndex() { return _uiController->getSelecSkillIndex(); };
    bool getCanPlayerInput()  { return _currentTurn == TURN_TYPE::PLAYER && !_usedPlayerCommand; }
private:
    void executeEnemyTurn();
    void changeTurn();
    void submitPlayerCommand(BattleCommand* cmd) { _commandQueue.push(cmd); }

    void clearCurrentLevel();
    void gameOver();
public:
    ::Action<float> onLevelClearEvent;
    ::Action<float> onGameOverEvent;
private:
    std::queue<TURN_TYPE> _turnQueue;
    std::queue<BattleCommand*> _commandQueue;
    std::unique_ptr<class UIController> _uiController;
    std::unique_ptr<class EnemySpawner> _enemySpawner;

    std::vector<Vec2> _playerTeamPosition;
    std::vector<Vec2> _enemyTeamPosition;

private:
    BattleCommand* _currentCommand = nullptr;
    std::unique_ptr <class Team> _playerTeam = nullptr;
    std::unique_ptr <class Team> _enemyTeam = nullptr;

    Entity* _currentEnemyEntity = nullptr;
    Entity* _currentPlayerEntity = nullptr;

    TURN_TYPE _currentTurn = TURN_TYPE::END;

    bool _canChangeTurn = true;
    bool _usedPlayerCommand = false;

};


