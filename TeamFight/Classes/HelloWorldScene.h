#pragma once
#include "cocos2d.h"
#include "Team.h"
#include "memory"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
private:
    void mouseDownEvent(EventMouse* event);

    Entity* selectPlayerEntity(cocos2d::Vec2& worldClick);

private:
    std::unique_ptr<Team> playerTeam = nullptr;
    std::unique_ptr<Team> enemyTeam = nullptr;


    cocos2d::Label* mainLabel = nullptr;
    Entity* currentEntity;

};