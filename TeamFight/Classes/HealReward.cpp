#include "HealReward.h"

#pragma execution_character_set("utf-8")

HealReward::HealReward()
{
	_iconIndexList.push_back({4,4});
	_iconIndexList.push_back({5,4});
	_iconIndexList.push_back({6,4});

	setDescription("먹으면 회복하는 맛있는 케이크 입니다. +", _healAmount);
}

void HealReward::execute()
{
	for (auto& entity : _team->getAliveEntities())
	{
		entity->getStatController()->addStat(STAT_TYPE::HP ,_healAmount);
	}

}
