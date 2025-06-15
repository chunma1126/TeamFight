#include "AttackUpReward.h"
#include "Entity.h"

#include <random>

#pragma execution_character_set("utf-8")

AttackUpReward::AttackUpReward()
{
	_iconIndexList.push_back({4,3});
	_iconIndexList.push_back({5,3});

	setDescription("공격력이 상승하는 매운 고추 입니다. +", _attackAmount);
}

void AttackUpReward::execute()
{
	int randomIndex = random() % getTragetTeam()->getAliveEntities().size();
	Entity* randomEntity = getTragetTeam()->getAliveEntities()[randomIndex];

	randomEntity->getStatController()->addStat(STAT_TYPE::ATK , _attackAmount);
}
