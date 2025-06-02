#include "HelloWorldScene.h"

#include "Entities.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    playerTeam = std::make_unique<Team>();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 screenCenter = { visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y };


    //init tilemap
    {
        auto map = TMXTiledMap::create("Tilemap/BattleBackground.tmx");
        map->setAnchorPoint({ 0.5f , 0.5f });
        map->setPosition(screenCenter);
        addChild(map,-100);
    }

    //init knight
    {
        Knight* entity = Knight::create();
        //entity->playAnimation(ANIMATION_STATE::ATTACK2);

        Vec2 pos = { visibleSize.width * 0.34f + origin.x, visibleSize.height * 0.5f + origin.y };
        entity->setPosition(pos);

        playerTeam->add(ENTITY_TYPE::KNIGHT , entity);
    }

    //init archer
    {
        Archer* entity = Archer::create();
        //entity->playAnimation(ANIMATION_STATE::ATTACK2);

        Vec2 pos = { visibleSize.width * 0.21f + origin.x, visibleSize.height * 0.4f + origin.y };
        entity->setPosition(pos);

        playerTeam->add(ENTITY_TYPE::ARCHER, entity);
    }

    //init pawn
    {
        Pawn* entity = Pawn::create();
        //entity->playAnimation(ANIMATION_STATE::ATTACK2);

        Vec2 pos = { visibleSize.width * 0.21f + origin.x, visibleSize.height * 0.6f + origin.y };
        entity->setPosition(pos);

        playerTeam->add(ENTITY_TYPE::PAWN, entity);
    }
    
    for (int entityType = 0; entityType < (int)ENTITY_TYPE::END; entityType++)
    {
        addChild(playerTeam->getEntity((ENTITY_TYPE)entityType));
    }


    
    

    return true;
}