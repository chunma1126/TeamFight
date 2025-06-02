#include "Archer.h"

bool Archer::init()
{
    if (!Entity::init()) {
        return false;
    }
    
    initAnimationSheet("Characters/Knights/Troops/Archer/Red/Archer_Red.png", 8, 7, ANIMATION_STATE::MOVE);

    return true;
}

void Archer::update(float dt)
{
}

void Archer::initAnimationSheet(const std::string& path, int row, int col, ANIMATION_STATE animationState)
{
    Entity::initAnimationSheet(path , row , col,animationState);
    int startY = 4 * _animationSheetFrameHeight;
    int animationCount = 8;
    for (size_t i = 0; i < animationCount; i++)
    {
        int startX = i * _animationSheetFrameWidth;

        Rect frameRect = Rect(startX, startY, _animationSheetFrameWidth, _animationSheetFrameHeight);
        auto spriteFrame = SpriteFrame::createWithTexture(_animationSheetInfo.animationSheet, frameRect);
        _animator[ANIMATION_STATE::ATTACK1].pushBack(spriteFrame);
        //_animator[ANIMATION_STATE::ATTACK2].pushBack(spriteFrame);
    }
   
    playAnimation(ANIMATION_STATE::IDLE, true);
}

