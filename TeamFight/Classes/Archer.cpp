#include "Archer.h"
#include "RangeSkill.h"

#pragma execution_character_set("utf-8")

bool Archer::init()
{
    if (!Entity::init()) {
        return false;
    }
    
    initAnimationSheet("Characters/Knights/Troops/Archer/Red/Archer_Red.png", 8, 7, ANIMATION_STATE::MOVE);

    _statController->setDefaultStat(STAT_TYPE::ATK , 20);
    _statController->setDefaultStat(STAT_TYPE::SPD , 15);
    _statController->setDefaultStat(STAT_TYPE::DEF , 5);
    _statController->setDefaultStat(STAT_TYPE::HP , 10);

    _healthBar->initMaxHealthBar(_statController->getValue(STAT_TYPE::HP));

    RangeSkill* rangeSkill = new RangeSkill;
    rangeSkill->setSkillName("Legend Shot");
    rangeSkill->setPower(10);
    rangeSkill->setType(SKILL_TYPE::DAMAGE);
    rangeSkill->setIconPath("SkillPack/skill_icon_04.png");
    rangeSkill->setDescription("적을 향해 화살을 쏩니다.");

    _skillList.push_back(rangeSkill);

    auto texture = Director::getInstance()->getTextureCache()->addImage("Characters/Knights/Troops/Archer/Arrow/Arrow.png");
    Rect frameRect(0, 0, 30, 32);
    auto arrowSprite = Sprite::createWithTexture(texture, frameRect);

    _arrow = Node::create();
    _arrow->addChild(arrowSprite);
    _arrowPosition = getPosition();
    _arrowPosition.y -= 6;
    _arrowPosition.x += 2;
    _arrow->setPosition(_arrowPosition);
    _arrow->setVisible(false);
    addChild(_arrow);


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
        _animator[ANIMATION_STATE::ATTACK2].pushBack(spriteFrame);
    }
   
    playAnimation(ANIMATION_STATE::IDLE, true);
}

