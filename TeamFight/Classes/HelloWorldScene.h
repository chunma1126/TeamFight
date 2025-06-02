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
    std::unique_ptr<Team> playerTeam;
    cocos2d::Label* mainLabel;
};