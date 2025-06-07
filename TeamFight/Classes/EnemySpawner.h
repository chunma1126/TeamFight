#pragma once
#include "Entities.h"
#include "Team.h"

class EnemySpawner
{
public:
	EnemySpawner();
	~EnemySpawner();

	Entity* EnemySpawn(Vec2 pos);

};

