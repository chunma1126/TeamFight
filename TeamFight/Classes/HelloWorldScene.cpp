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
    if ( !Scene::init() )
    {
        return false;
    }

    playerTeam = std::make_unique<Team>();
    enemyTeam = std::make_unique<Team>();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 screenCenter = { visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y };

    std::string defaultString = "hellow";
    mainLabel = Label::createWithTTF(defaultString.c_str(), "fonts/SunBatang/SunBatang-Bold.ttf", 35);

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

        Vec2 pos = { visibleSize.width * 0.21f + origin.x, visibleSize.height * 0.3f + origin.y };
        entity->setPosition(pos);

        playerTeam->add(ENTITY_TYPE::ARCHER, entity);
    }

    //init pawn
    {
        Pawn* entity = Pawn::create();
        //entity->playAnimation(ANIMATION_STATE::ATTACK2);

        Vec2 pos = { visibleSize.width * 0.21f + origin.x, visibleSize.height * 0.7f + origin.y };
        entity->setPosition(pos);

        playerTeam->add(ENTITY_TYPE::PAWN, entity);
    }
    
    for (const auto& entity : playerTeam->getAllEntities())
    {
#if false
        auto drawNode = DrawNode::create();
        auto boundingBox = entity->getMainSprite()->getBoundingBox();

        Vec2 bottomLeft(boundingBox.getMinX(), boundingBox.getMinY());
        Vec2 bottomRight(boundingBox.getMaxX(), boundingBox.getMinY());
        Vec2 topRight(boundingBox.getMaxX(), boundingBox.getMaxY());
        Vec2 topLeft(boundingBox.getMinX(), boundingBox.getMaxY());

        drawNode->drawPolygon(
            std::vector<Vec2>{bottomLeft, bottomRight, topRight, topLeft}.data(),
            4,
            Color4F(0, 0, 0, 0),
            1.0f,
            Color4F::RED
        );

        entity->addChild(drawNode);
#endif 

        addChild(entity);
    }
    
    //enemyInit
    {
        Entity* entity = Entity::create();
        entity->initAnimationSheet("Characters/Goblins/Troops/Torch/Blue/Torch_Blue.png" ,7 ,5 );
        entity->getMainSprite()->setFlippedX(true);
        entity->playAnimation(ANIMATION_STATE::IDLE , true);


        Vec2 pos = { visibleSize.width * 0.7f + origin.x, visibleSize.height * 0.5f + origin.y };
        entity->setPosition(pos);
        
        enemyTeam->add(ENTITY_TYPE::KNIGHT, entity);
        addChild(entity);
    }

    //mouse Event
    {
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::mouseDownEvent , this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
    

    return true;
}

void HelloWorld::mouseDownEvent(EventMouse* event)
{
    Vec2 worldClick = event->getLocationInView();
    currentEntity = selectPlayerEntity(worldClick);

    if (currentEntity != nullptr)
    {
        auto sizeUpEvent = ScaleTo::create(0.1f, 1.1f);
        currentEntity->runAction(sizeUpEvent);
    }
    else
    {
        mainLabel->setString("");
    }

    for (const auto& entity : enemyTeam->getAllEntities())
    {
        Rect entityRect = entity->getMainSprite()->getBoundingBox();
        Vec2 localPos = entity->convertToNodeSpace(worldClick);

        if (entityRect.containsPoint(localPos))
        {
            currentEntity->playAnimation(ANIMATION_STATE::ATTACK1,false);
            mainLabel->setString("enemy");
        }
    }

    

}

Entity* HelloWorld::selectPlayerEntity(cocos2d::Vec2& worldClick)
{
    //currentEntity = nullptr;

    for (const auto& entity : playerTeam->getAllEntities())
    {
        Rect entityRect = entity->getMainSprite()->getBoundingBox();
        Vec2 localPos = entity->convertToNodeSpace(worldClick);

        auto resizeAction = ScaleTo::create(0.1f, 1.0f);
        entity->runAction(resizeAction);

        if (entityRect.containsPoint(localPos))
        {
            currentEntity = entity;
            mainLabel->setString(currentEntity->getSkill()->name.c_str());
        }
    }

    
    
    return currentEntity;
}
