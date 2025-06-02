#pragma once
#include <functional>

class BattleCommand
{
public:
    BattleCommand(float duration = 1.0f, std::function<void()> action = nullptr);
    virtual ~BattleCommand();

    virtual void start();
    virtual void update(float dt);
    virtual void reset();

    bool isEnd() const { return _elapsedTime >= _duration; }

protected:
    float _elapsedTime = 0.0f;
    float _duration = 1.0f;
    std::function<void()> _action;
    bool _started = false;
};
