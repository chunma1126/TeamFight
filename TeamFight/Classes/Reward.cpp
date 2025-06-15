#include "Reward.h"

#include <random>

std::pair<int, int> Reward::getIconIndex()
{
	int randomIndex = rand() % _iconIndexList.size();
	return _iconIndexList[randomIndex];
}
