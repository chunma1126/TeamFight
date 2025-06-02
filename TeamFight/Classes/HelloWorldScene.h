#pragma once
#include "cocos2d.h"
#include "memory"
#include "Team.h"
#include "BattleManager.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void update(float dt);

    CREATE_FUNC(HelloWorld);
private:
    void mouseDownEvent(EventMouse* event);
    Entity* selectPlayerEntity(cocos2d::Vec2& worldClick);

private:
    std::unique_ptr<Team> _playerTeam = nullptr;
    std::unique_ptr<Team> _enemyTeam = nullptr;
    std::unique_ptr<BattleManager> _battleManager = nullptr;
private:
    cocos2d::Label* _mainLabel = nullptr;
    Entity* _currentEntity;
    bool _canInput = true;;
};