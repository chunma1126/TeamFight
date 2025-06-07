#include "EnemySpawner.h"

EnemySpawner::EnemySpawner()
{

}

EnemySpawner::~EnemySpawner()
{
}

Entity* EnemySpawner::EnemySpawn(Vec2 pos)
{
	Entity* entity = Goblin::create();
	entity->setPosition(pos);
	cocos2d::Director::getInstance()->getRunningScene()->addChild(entity);

	return entity;
}
