#include "Team.h"
#include "algorithm"

Team::Team()
{
	_entityList.reserve(3);
}

Team::~Team()
{
	_entityMap.clear();
	_entityList.clear();
}

void Team::add(ENTITY_TYPE entityType, Entity* entity)
{
	_entityMap[entityType] = entity;
	_entityList.push_back(entity);

	std::sort(_entityList.begin(), _entityList.end(),
		[](Entity* a,Entity* b) 
		{
			return a->getStatController()->getValue(STAT_TYPE::SPD) >
				   b->getStatController()->getValue(STAT_TYPE::SPD);
		});

}

bool Team::isAllDead()
{
	for (const auto& entity : _entityList)
	{
		if (!entity->getStatController()->isDead())
		{
			return false;
		}
	}

	return true;
}

void Team::activeTeam(bool active)
{
	if (active) 
	{
		for (const auto& entity : getAllEntities())
		{
			entity->getMainSprite()->setOpacity(255);
		}
	}
	else {
		for (const auto& entity : getAllEntities())
		{
			entity->getMainSprite()->setOpacity(128);
		}
	}
}


Entity* Team::getEntity()
{
	if (isAllDead()) return nullptr;

	size_t count = _entityList.size();
	for (size_t i = 0; i < count; ++i)
	{
		size_t index = _nextEntity++ % count;
		Entity* entity = _entityList[index];
		if (!entity->getStatController()->isDead())
			return entity;
	}

	return nullptr;
}

Entity* Team::getEntity(ENTITY_TYPE entityType)
{
	return _entityMap[entityType];
}

const std::vector<Entity*> Team::getAliveEntities()
{
	std::vector<Entity*> entities;

	for (auto& entity : _entityList )
	{
		if (entity->getStatController()->isDead() == false) {
			entities.push_back(entity);
		}
	}

	return entities;
}

void Team::clearEntities()
{
	for (auto* entity : _entityList)
	{
		if (entity->getParent())
			entity->removeFromParent();
	}

	_entityList.clear(); 
}

