#include "Reward.h"

#include <random>

std::pair<int, int> Reward::getIconIndex()
{
	int randomIndex = rand() % _iconIndexList.size();
	return _iconIndexList[randomIndex];
}

void Reward::setDescription(const char* description, int amount)
{
	_description = std::string(description) + std::to_string(amount);
}
