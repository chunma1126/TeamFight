#include "Team.h"
#include "algorithm"

#define MAX_ENTITY_COUNT 3

Team::Team()
{
	_entitiesSortedByType.resize(MAX_ENTITY_COUNT);
	_entitiesSortedBySpeed.resize(MAX_ENTITY_COUNT);
}

Team::~Team()
{
	_entitiesSortedByType.clear();
	_entitiesSortedBySpeed.clear();
}

bool Team::entityCompare(Entity* a, Entity* b)
{
	if (!a) return false;
	if (!b) return true;

	auto aStat = a->getStatController();
	auto bStat = b->getStatController();

	return aStat->getValue(STAT_TYPE::SPD) > bStat->getValue(STAT_TYPE::SPD);
}

void Team::addEntity(ENTITY_TYPE entityType, Entity* entity)
{
	if ((int)entityType < (int)ENTITY_TYPE::PLAYER_ENTITY_END)
	{
		size_t index = (int)entityType;
		_entitiesSortedByType[index] = entity;
		_entitiesSortedBySpeed[index] = entity;
	}
	else
	{
		for (int i = 0; i < _entitiesSortedByType.size(); i++)
		{
			if (_entitiesSortedByType[i] == nullptr)
			{
				_entitiesSortedByType[i] = entity;
				_entitiesSortedBySpeed[i] = entity;

				break;
			}
		}
	}

	std::sort(_entitiesSortedBySpeed.begin(), _entitiesSortedBySpeed.end(),Team::entityCompare);

}

bool Team::isAllDead()
{
	for (const auto& entity : _entitiesSortedByType)
	{
		if (!entity->getStatController()->isDead())
		{
			return false;
		}
	}

	return true;
}

void Team::setActiveTeam(bool active)
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
			entity->getMainSprite()->setOpacity(200);
		}
	}
}


Entity* Team::getEntity()
{
	if (isAllDead()) return nullptr;

	size_t count = _entitiesSortedBySpeed.size();
	for (size_t i = 0; i < count; ++i)
	{
		size_t index = _nextEntity++ % count;
		Entity* entity = _entitiesSortedBySpeed[index];
		if (!entity->getStatController()->isDead())
			return entity;
	}

	return nullptr;
}

Entity* Team::getEntity(ENTITY_TYPE entityType)
{
	size_t index = (int)entityType % (int)(ENTITY_TYPE::PLAYER_ENTITY_END);
	return _entitiesSortedByType[index];
}

const std::vector<Entity*> Team::getAliveEntities()
{
	std::vector<Entity*> entities;

	for (auto& entity : _entitiesSortedByType)
	{
		if (entity->getStatController()->isDead() == false) {
			entities.push_back(entity);
		}
	}

	return entities;
}



void Team::clearEntities()
{
	for (auto*& entity : _entitiesSortedByType)
	{
		if (entity && entity->getParent())
			entity->removeFromParent();
	}

	_entitiesSortedByType.clear();
	_entitiesSortedByType.resize(MAX_ENTITY_COUNT);

	_entitiesSortedBySpeed.clear();
	_entitiesSortedBySpeed.resize(MAX_ENTITY_COUNT);


}

