#include "BattleCommand.h"

BattleCommand::BattleCommand(float duration, std::function<void()> action)
    : _duration(duration), _action(action)
{
}

BattleCommand::~BattleCommand()
{
}

void BattleCommand::start()
{
    _elapsedTime = 0.0f;
    _started = true;

    if (_action)
        _action();
}

void BattleCommand::update(float dt)
{
    if (!_started)
        return;

    _elapsedTime += dt;
}

void BattleCommand::reset()
{
    _elapsedTime = 0.0f;
    _started = false;
}
