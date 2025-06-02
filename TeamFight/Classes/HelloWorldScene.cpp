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

    mainLabel = Label::createWithTTF("Team Fight", "fonts/SunBatang/SunBatang-Bold.ttf", 35);

    mainLabel->setPosition(screenCenter.x , visibleSize.height * 0.92f);
    addChild(mainLabel);

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

    //mouse Event
    {
        auto mouseListener = EventListenerMouse::create();

        mouseListener->onMouseDown = [&](EventMouse* event) 
            {
                Vec2 worldClick = event->getLocation();

                for (int entityType = 0; entityType < (int)ENTITY_TYPE::END; entityType++)
                {
                    ENTITY_TYPE type = (ENTITY_TYPE)(entityType);
                    Rect entityRect = playerTeam->getEntity(type)->getSpriteBoundingBox();

                    Vec2 localPos = playerTeam->getEntity(type)->convertToNodeSpace(worldClick);


                    if (entityRect.containsPoint(localPos))
                    {
                        //CCLOG("%s", playerTeam->getEntity(type)->getSkill()->name.c_str());
                        mainLabel->setString(playerTeam->getEntity(type)->getSkill()->name.c_str());
                    }
                }

                
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
    
    

    return true;
}