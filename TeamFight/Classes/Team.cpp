#include "Team.h"
#include "algorithm"

Team::Team()
{
	_entityList.resize(3);
}

Team::~Team()
{
	_entityList.clear();
}

void Team::add(ENTITY_TYPE entityType, Entity* entity)
{
	if ((int)entityType < (int)ENTITY_TYPE::PLAYER_ENTITY_END)
	{
		size_t index = (int)entityType;
		_entityList[index] = entity;
	}
	else
	{
		for (int i = 0; i < _entityList.size(); i++)
		{
			if (_entityList[i] == nullptr)
			{
				_entityList[i] = entity;
				break;
			}
		}
	}

	std::sort(_entityList.begin(), _entityList.end(),
		[](Entity* a, Entity* b)
		{
			if (!a) return false;
			if (!b) return true;

			auto aStat = a->getStatController();
			auto bStat = b->getStatController();

			if (!aStat) return false;
			if (!bStat) return true;

			return aStat->getValue(STAT_TYPE::SPD) > bStat->getValue(STAT_TYPE::SPD);
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
	size_t index = (int)entityType % (int)(ENTITY_TYPE::PLAYER_ENTITY_END);
	return _entityList[index];
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
	for (auto*& entity : _entityList)
	{
		if (entity && entity->getParent())
			entity->removeFromParent();
	}
	_entityList.clear();
	_entityList.resize(3);

}

