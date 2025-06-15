#pragma once
#include "Team.h"
#include <vector>

class Reward
{
public:
	void setTragetTeam(Team* team) { _team = team; };
	Team* getTragetTeam() { return  _team; };
	std::pair<int, int> getIconIndex();
	const std::string& getDescription() const { return _description; }
public:
	virtual void execute() = 0; 
protected:
	void setDescription(const char* description, int amount);
	Team* _team;
	std::vector<std::pair<int,int>> _iconIndexList;
	std::string _description;

};

