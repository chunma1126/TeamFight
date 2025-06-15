#pragma once
#include <queue>
#include "Action.h"

class BattleCommand;
class TurnController;
class TeamController;
class UIController;
class SelectController;
class Entity;

class CommandController
{
public:
	CommandController();
	~CommandController();
	void init(TurnController* turnController, TeamController* teamController, UIController* uiController, SelectController* selectController);
public:
	void changeTurn();
	void update(float dt);
	void executePlayerTurn(Entity* enemyEntity, int currentSkillIndex);
public:
	void submitPlayerCommand(BattleCommand* cmd) { _commandQueue.push(cmd); }

	bool getCanChangeTurn() const { return _canChangeTurn; }
	void setChangeTurn(bool canChangeTurn) { _canChangeTurn = canChangeTurn; }

	bool getUsedPlayerCommand() const { return _usedPlayerCommand; }
	void setUsedPlayerCommand(bool usedPlayerCommand) { _usedPlayerCommand = usedPlayerCommand; }

public:
	::Action<float> onLevelClearEvent;
	::Action<float> onGameOverEvent;
private:
	void gameOver();
	void executeEnemyTurn();

private:
	std::queue<BattleCommand*> _commandQueue;

	TurnController* _turnController = nullptr;
	TeamController* _teamController = nullptr;
	BattleCommand* _currentCommand = nullptr;
	UIController* _uiController = nullptr;
	SelectController* _selectController = nullptr;

	Entity* _currentEnemyEntity = nullptr;
	Entity* _currentPlayerEntity = nullptr;

	bool _canChangeTurn = true;
	bool _usedPlayerCommand = false;

};

