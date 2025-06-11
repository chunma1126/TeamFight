#pragma once
#include <unordered_map>
#include <vector>
#include "Entity.h"

class Team
{
public:
	Team();
	~Team();
public:
	static bool entityCompare(Entity* a, Entity* b);
public:
	void addEntity(ENTITY_TYPE entityType , Entity* entity);
	void setActiveTeam(bool active);
	void clearEntities(); 
public:
	bool isAllDead();
	Entity* getEntity();
	Entity* getEntity(ENTITY_TYPE entityType);
	const std::vector<Entity*> getAllEntities() { return _entitiesSortedByType; }
	const std::vector<Entity*> getAliveEntities();
private:
	std::vector<Entity*> _entitiesSortedByType;
	std::vector<Entity*> _entitiesSortedBySpeed;

	size_t _nextEntity = 0;
};

