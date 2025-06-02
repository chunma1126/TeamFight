#include "Team.h"
#include "algorithm"

Team::Team()
{
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
		[](Entity* a,Entity* b) {
			return a->getStatController()->getValue(STAT_TYPE::SPD) >
				b->getStatController()->getValue(STAT_TYPE::SPD);
		});

}

bool Team::isAllDead()
{
	return false;
}

Entity* Team::getEntity()
{
	size_t nextIndex = _nextEntity++ % _entityList.size();
	return _entityList[nextIndex];
}

Entity* Team::getEntity(ENTITY_TYPE entityType)
{
	return _entityMap[entityType];
}
