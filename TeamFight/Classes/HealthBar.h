#pragma once
#include "cocos2d.h"
USING_NS_CC;

class HealthBar : public Node   
{
public:
    virtual bool init();
    void initMaxHealthBar(float maxHealth);
    void updateHealthText(float currentHealth);
    CREATE_FUNC(HealthBar);
private:
    Label* _healthBar;
    float _maxHealth;
};

