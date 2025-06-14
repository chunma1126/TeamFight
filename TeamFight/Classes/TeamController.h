#pragma once

#include <memory>
#include <vector>
#include "Team.h"
#include "Entity.h"
#include "EnemySpawner.h"
#include "Enum.h"

class TeamController {
public:
    TeamController();
    ~TeamController();

    void initPlayerTeam(const std::vector<Vec2>& positions);
    void initEnemyTeam(const std::vector<Vec2>& positions, EnemySpawner* spawner);

    void spawnEnemyTeam();

    void clearPlayerTeam();
    void clearEnemyTeam();

    bool isPlayerTeamDead() const;
    bool isEnemyTeamDead() const;

    Entity* getRandomAliveEnemyEntity();
    Entity* getRandomAlivePlayerEntity();

    Entity* getPlayerEntity();
    Entity* getEnemyEntity();

    std::vector<Entity*> getAliveEnemies() const;
    std::vector<Entity*> getAlivePlayers() const;

    void setPlayerTeamActive(bool active);
    void setEnemyTeamActive(bool active);

    void resetTeams();

    std::shared_ptr<Team> getPlayerTeam() const { return _playerTeam; }
    std::shared_ptr<Team> getEnemyTeam() const { return _enemyTeam; }

private:
    std::shared_ptr<Team> _playerTeam;
    std::shared_ptr<Team> _enemyTeam;

    std::vector<Vec2> _playerTeamPositions;
    std::vector<Vec2> _enemyTeamPositions;

    EnemySpawner* _enemySpawner = nullptr;
};
