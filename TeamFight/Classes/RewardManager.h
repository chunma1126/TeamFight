#pragma once
#include "Reward.h"
#include "HealReward.h"
#include "AttackUpReward.h"

#include <vector>

class RewardManager
{
public:
	RewardManager();
	~RewardManager();
public:
	Reward* getReward();
private:
	std::vector<Reward*> _rewardList;

};

