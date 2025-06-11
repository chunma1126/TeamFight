#include "HealthBar.h"
#include "Enum.h"
#include "Entity.h"

#include <string>

bool HealthBar::init()
{
    if (!Node::init())
        return false;

    _healthBar = Label::createWithTTF("", FONT_BMJUA, 7);
    _healthBar->setColor(Color3B(236, 240, 241));
    _healthBar->setPosition(Vec2::ZERO);
    addChild(_healthBar, LAYER::UI);
    return true;
}

void HealthBar::initMaxHealthBar(float maxHealth)
{
    _maxHealth = maxHealth;

    if (auto* entity = dynamic_cast<Entity*>(getParent()))
    {
        float heightOffset = entity->getMainSprite()->getBoundingBox().size.height / 3;
        setPosition(entity->getMainSprite()->getPosition() + Vec2(0, heightOffset));
    }

    updateHealthText(_maxHealth); 
}

void HealthBar::updateHealthText(float currentHealth)
{
    int cur = static_cast<int>(currentHealth);
    int max = static_cast<int>(_maxHealth);
    _healthBar->setString("HP: " + std::to_string(cur) + "/" + std::to_string(max));
}