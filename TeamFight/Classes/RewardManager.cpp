#include "RewardManager.h"

#include <random>

RewardManager::RewardManager()
{
	_rewardList.push_back(new HealReward);
	_rewardList.push_back(new AttackUpReward);
}

RewardManager::~RewardManager()
{
    for (auto reward : _rewardList)
    {
        delete reward;
    }
    _rewardList.clear(); 
}

Reward* RewardManager::getReward()
{
    int randomIndex = rand() % _rewardList.size();
    
	return _rewardList[randomIndex];
}
