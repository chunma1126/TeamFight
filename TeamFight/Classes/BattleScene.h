#pragma once
#include "cocos2d.h"
#include "memory"
#include "Team.h"
#include "BattleManager.h"

class BattleScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    virtual void update(float dt);

    CREATE_FUNC(BattleScene);
private:
    void mouseDownEvent(EventMouse* event);
private:
    std::unique_ptr<BattleManager> _battleManager = nullptr;


};