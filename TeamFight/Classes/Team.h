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
	Entity* getEntity();
	Entity* getEntity(ENTITY_TYPE entityType);
private:
	std::unordered_map<ENTITY_TYPE,Entity*> _entityMap;
	std::vector<Entity*> _entityList;
	size_t _nextEntity = 0;
};

