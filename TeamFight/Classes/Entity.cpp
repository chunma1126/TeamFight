#include "Entity.h"

bool Entity::init()
{
    if (!Node::init()) 
    {
        return false;
    }



    auto texture = Director::getInstance()->getTextureCache()->addImage("Characters/Knights/Troops/Warrior/Blue/Warrior_Blue.png");
    int textureWidht = texture->getContentSize().width;
    int textureHeight = texture->getContentSize().height;

    int frameWidth = textureWidht / 6;
    int frameHeight = textureHeight / 8;

    _sprite = Sprite::createWithTexture(texture, Rect(0, 0, frameWidth, frameHeight));
    addChild(_sprite);

    {
        int animationCount = 6;
        int startY = 0;
        for (int i = 0; i < animationCount; i++)
        {
            int startX = i * frameWidth;

            Rect frameRect = Rect(startX, startY, frameWidth, frameHeight);
            auto spriteFrame = SpriteFrame::createWithTexture(texture, frameRect);
            _animator[STATE::IDLE].pushBack(spriteFrame);
        }
    }

    return true;
}

void Entity::playAnimation(STATE state, bool loop)
{
    auto it = _animator.find(state);
    if (it == _animator.end()) return;

    auto animation = Animation::createWithSpriteFrames(it->second, 0.1f);
    auto animate = Animate::create(animation);

    _sprite->stopAllActions();
    if (loop)
        _sprite->runAction(RepeatForever::create(animate));
    else
        _sprite->runAction(animate);
}
