#include "RewardManager.h"

RewardManager::RewardManager()
{

}

RewardManager::~RewardManager()
{
}

Reward* RewardManager::getReward()
{
	Reward* newWard = new HealReward;
	return newWard;
}
