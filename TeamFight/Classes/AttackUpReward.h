#pragma once
#include "Reward.h"
class AttackUpReward : public Reward
{
public:
	AttackUpReward();
	void execute() override;
private:
	int _attackAmount = 2;
};

