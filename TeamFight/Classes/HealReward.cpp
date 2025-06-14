#include "HealReward.h"

void HealReward::execute()
{
	for (auto& entity : _team->getAliveEntities())
	{
		entity->getStatController()->addStat(STAT_TYPE::HP ,_healAmount);
	}

}
