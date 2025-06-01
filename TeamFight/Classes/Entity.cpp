#include "Entity.h"
#include "StatController.h"
bool Entity::init()
{
    if (!Node::init()) 
    {
        return false;
    }

    _statController = std::make_unique<StatController>();


    return true;
}

void Entity::playAnimation(ANIMATION_STATE state, bool loop)
{
    auto it = _animator.find(state);
    if (it == _animator.end()) return;

    float frameInterval = 0.1f; 

    auto animation = Animation::createWithSpriteFrames(it->second, frameInterval);
    auto animate = Animate::create(animation);

    _sprite->stopAllActions();
    if (loop)
        _sprite->runAction(RepeatForever::create(animate));
    else
        _sprite->runAction(animate);
}

void Entity::setAnimationSheet(const std::string& path)
{
    auto animationSheet = Director::getInstance()->getTextureCache()->addImage(path);

    int animationSheetWidht = animationSheet->getContentSize().width;
    int animationSheetHeight = animationSheet->getContentSize().height;

    int frameWidth = animationSheetWidht / 6;
    int frameHeight = animationSheetHeight / 8;

    _sprite = Sprite::createWithTexture(animationSheet, Rect(0, 0, frameWidth, frameHeight));
    addChild(_sprite);

    for (size_t state = 0; state < (int)ANIMATION_STATE::DEAD; state++)
    {
        int animationCount = 6;
        int startY = state * frameHeight;
        for (size_t i = 0; i < animationCount; i++)
        {
            int startX = i * frameWidth;

            Rect frameRect = Rect(startX, startY, frameWidth, frameHeight);
            auto spriteFrame = SpriteFrame::createWithTexture(animationSheet, frameRect);
            _animator[(ANIMATION_STATE)state].pushBack(spriteFrame);
        }
    }

    auto deadanimationSheet = Director::getInstance()->getTextureCache()->addImage("Characters/Knights/Troops/Dead/Dead.png");

    animationSheetWidht = deadanimationSheet->getContentSize().width;
    animationSheetHeight = deadanimationSheet->getContentSize().height;

    frameWidth = animationSheetWidht / 7;
    frameHeight = animationSheetHeight / 2;

    for (size_t i = 0; i < 2; i++)
    {
        int animationCount = 7;
        int startY = i * frameHeight;
        for (int i = 0; i < animationCount; i++)
        {
            int startX = i * frameWidth;

            Rect frameRect = Rect(startX, startY, frameWidth, frameHeight);
            auto spriteFrame = SpriteFrame::createWithTexture(deadanimationSheet, frameRect);
            _animator[ANIMATION_STATE::DEAD].pushBack(spriteFrame);
        }
    }

    playAnimation(ANIMATION_STATE::IDLE, true);
        
}
