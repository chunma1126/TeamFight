#pragma once
#include "Team.h"

class Reward
{
public:
	Reward();
	virtual ~Reward();
	void setTragetTeam(Team* team) { _team = team; };
	Team* getTragetTeam() { return  _team; };
	virtual void execute() = 0; 
protected:
	Team* _team;

};

