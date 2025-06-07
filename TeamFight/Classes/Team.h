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
	void add(ENTITY_TYPE entityType , Entity* entity);
	bool isAllDead();
	void activeTeam(bool active);
	Entity* getEntity();
	Entity* getEntity(ENTITY_TYPE entityType);
	const std::vector<Entity*> getAllEntities() { return _entityList; }
	const std::vector<Entity*> getAliveEntities();
	void clearEntities(); 
private:
	std::unordered_map<ENTITY_TYPE,Entity*> _entityMap;
	std::vector<Entity*> _entityList;
	size_t _nextEntity = 0;
};

