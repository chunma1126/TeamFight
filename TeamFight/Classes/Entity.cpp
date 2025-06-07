#include "Entity.h"

Entity::~Entity()
{
    size_t skllListSize = _skillList.size();
    for (size_t i = 0; i < skllListSize; i++)
    {
        delete _skillList[i];
        _skillList[i] = nullptr;
    }
}

bool Entity::init()
{
    if (!Node::init()) 
    {
        return false;
    }

    _healthBar = HealthBar::create();
    addChild(_healthBar);

    _statController = std::make_unique<StatController>();
    _statController->getStat(STAT_TYPE::HP).onChangeValueEvent.add([&](float value)
        {
            this->tryDead(value);

            _healthBar->updateHealthText(value);
        });

    for (size_t state = 0; state < (int)ANIMATION_STATE::END; state++)
    {
        _animator[(ANIMATION_STATE)state].reserve(6);
    }

    scheduleUpdate();
    return true;
}

void Entity::tryDead(float value)
{
    if (value > 0)return;

    playAnimation(ANIMATION_STATE::DEAD, false, 1.0f, CallFunc::create([&]()
    {
        this->setVisible(false);
    }));

}

void Entity::update(float dt)
{
    _statController->update(dt);
}

void Entity::playAnimation(ANIMATION_STATE state, bool loop, float animationSpeed, CallFunc* animationEndCallback)
{
    auto it = _animator.find(state);
    if (it == _animator.end()) return;

    float frameInterval = 0.1f / animationSpeed;

    auto animation = Animation::createWithSpriteFrames(it->second, frameInterval);
    auto animate = Animate::create(animation);

    _mainSprite->stopAllActions();

    if (loop)
        _mainSprite->runAction(RepeatForever::create(animate));
    else {
        auto callback = CallFunc::create([this]()
            {
                this->playAnimation(ANIMATION_STATE::IDLE, true); 
            });

        Vector<FiniteTimeAction*> actions;
        actions.pushBack(animate);
        actions.pushBack(callback);
        if (animationEndCallback != nullptr)
            actions.pushBack(animationEndCallback);

        auto seq = Sequence::create(actions);
        _mainSprite->runAction(seq);
    }

}

void Entity::initAnimationSheet(const std::string& path,int row, int col,ANIMATION_STATE animationState)
{
    _animationSheetInfo = getAnimationSheetInfo(path);
    _animationSheetFrameWidth = _animationSheetInfo.contentSize.x / row;
    _animationSheetFrameHeight = _animationSheetInfo.contentSize.y / col;
    
    _mainSprite = Sprite::createWithTexture(_animationSheetInfo.animationSheet, Rect(0, 0, _animationSheetFrameWidth, _animationSheetFrameHeight));
    addChild(_mainSprite);
    
    setAnimationSheet(_animationSheetFrameWidth, _animationSheetFrameHeight, 6, _animationSheetInfo.animationSheet, animationState);

    playAnimation(ANIMATION_STATE::IDLE, true);
}

void Entity::setAnimationSheet(float frameWidth ,float frameHeight,int animationCount, Texture2D* animationSheets, ANIMATION_STATE defaultEndState)
{
    for (size_t state = 0; state <= (int)defaultEndState; state++)
    {
        int startY = state * frameHeight;
        for (size_t i = 0; i < animationCount; i++)
        {
            int startX = i * frameWidth;

            Rect frameRect = Rect(startX, startY, frameWidth, frameHeight);
            auto spriteFrame = SpriteFrame::createWithTexture(animationSheets, frameRect);
            _animator[(ANIMATION_STATE)state].pushBack(spriteFrame);
        }
    }
    setDeadAnimationSheet();
}

void Entity::setDeadAnimationSheet()
{
    std::string deadAnimationSheetPath = "Characters/Knights/Troops/Dead/Dead.png";
    AnimationSheetInfo deadAnimationInfo = getAnimationSheetInfo(deadAnimationSheetPath);

    float frameWidth = deadAnimationInfo.contentSize.x / 7;
    float frameHeight = deadAnimationInfo.contentSize.y / 2;

    for (size_t i = 0; i < 2; i++)
    {
        int animationCount = 7;
        int startY = i * frameHeight;
        for (int i = 0; i < animationCount; i++)
        {
            int startX = i * frameWidth;

            Rect frameRect = Rect(startX, startY, frameWidth, frameHeight);

            auto spriteFrame = SpriteFrame::createWithTexture(deadAnimationInfo.animationSheet, frameRect);
            _animator[ANIMATION_STATE::DEAD].pushBack(spriteFrame);
        }
    }
}

AnimationSheetInfo Entity::getAnimationSheetInfo(const std::string& path)
{
    AnimationSheetInfo animationInfo;

    auto deadanimationSheet = Director::getInstance()->getTextureCache()->addImage(path);
    animationInfo.animationSheet = deadanimationSheet;

    float animationSheetWidht = deadanimationSheet->getContentSize().width;
    float animationSheetHeight = deadanimationSheet->getContentSize().height;
    animationInfo.contentSize = Vec2(animationSheetWidht, animationSheetHeight);

    return  animationInfo;
}

