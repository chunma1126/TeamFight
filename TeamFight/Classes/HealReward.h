#pragma once
#include "Reward.h"
class HealReward : public Reward
{
public:
	void execute() override;
private:
	float _healAmount = 5;
};

