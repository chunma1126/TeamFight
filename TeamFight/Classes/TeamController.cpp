#include "TeamController.h"
#include "Knight.h"
#include "Archer.h"
#include "Pawn.h"
#include "cocos2d.h"

TeamController::TeamController() {
    _playerTeam = std::make_shared<Team>();
    _enemyTeam = std::make_shared<Team>();
}

TeamController::~TeamController() {
    clearPlayerTeam();
    clearEnemyTeam();
}

void TeamController::initPlayerTeam(const std::vector<Vec2>& positions) {
    _playerTeamPositions = positions;

    _playerTeam->addEntity(ENTITY_TYPE::KNIGHT, Knight::create());
    _playerTeam->addEntity(ENTITY_TYPE::ARCHER, Archer::create());
    _playerTeam->addEntity(ENTITY_TYPE::PAWN, Pawn::create());

    for (int i = 0; i < _playerTeam->getAllEntities().size(); ++i) {
        Entity* entity = _playerTeam->getEntity((ENTITY_TYPE)i);
        entity->setPosition(_playerTeamPositions[i]);
        cocos2d::Director::getInstance()->getRunningScene()->addChild(entity);
    }
}

void TeamController::initEnemyTeam(const std::vector<Vec2>& positions, EnemySpawner* spawner)
{
    _enemyTeamPositions = positions;
    _enemySpawner = spawner;

    spawnEnemyTeam();
}

void TeamController::spawnEnemyTeam()
{
    for (int i = 0; i < (int)ENTITY_TYPE::PLAYER_ENTITY_END; ++i) {
        Entity* entity = _enemySpawner->EnemySpawn(_enemyTeamPositions[i]);
        _enemyTeam->addEntity(ENTITY_TYPE::GOBLIN, entity);
    }
}

void TeamController::clearPlayerTeam() {
    _playerTeam->clearEntities();
}

void TeamController::clearEnemyTeam() {
    _enemyTeam->clearEntities();
}

bool TeamController::isPlayerTeamDead() const {
    return _playerTeam->isAllDead();
}

bool TeamController::isEnemyTeamDead() const {
    return _enemyTeam->isAllDead();
}

Entity* TeamController::getRandomAliveEnemyEntity() 
{
    const auto& enemies = _enemyTeam->getAliveEntities();
    if (enemies.empty()) return nullptr;
    return enemies[rand() % enemies.size()];
}

Entity* TeamController::getRandomAlivePlayerEntity() 
{
    const auto& players = _playerTeam->getAliveEntities();
    if (players.empty()) return nullptr;
    return players[rand() % players.size()];
}

Entity* TeamController::getPlayerEntity() 
{
    return _playerTeam->getEntity();
}

Entity* TeamController::getEnemyEntity() 
{
    return _enemyTeam->getEntity();
}

std::vector<Entity*> TeamController::getAliveEnemies() const 
{
    return _enemyTeam->getAliveEntities();
}

std::vector<Entity*> TeamController::getAlivePlayers() const 
{
    return _playerTeam->getAliveEntities();
}

void TeamController::setPlayerTeamActive(bool active)
{
    _playerTeam->setActiveTeam(active);
}

void TeamController::setEnemyTeamActive(bool active) 
{
    _enemyTeam->setActiveTeam(active);
}

void TeamController::resetTeams()
{
    clearPlayerTeam();
    clearEnemyTeam();
    _playerTeam = std::make_shared<Team>();
    _enemyTeam = std::make_shared<Team>();
}
