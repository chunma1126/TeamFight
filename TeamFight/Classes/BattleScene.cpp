#include "BattleScene.h"
#include "Entities.h"


USING_NS_CC;

enum LAYER
{
    NONE = 0,
    BACKGROUND = -100,
    ENEMY = -99,
    PLAYER = 1,
    
};

Scene* BattleScene::createScene()
{
    return BattleScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool BattleScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    //init unique_ptr
    {
        _playerTeam = std::make_unique<Team>();
        _enemyTeam = std::make_unique<Team>();
        _battleManager = std::make_unique<BattleManager>();
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 screenCenter = { visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y };

    //init tilemap
    {
        auto map = TMXTiledMap::create("Tilemap/BattleBackground.tmx");
        map->setAnchorPoint({ 0.5f , 0.5f });
        map->setPosition(screenCenter);
        addChild(map, LAYER::BACKGROUND);
    }

    //init knight
    {
        Knight* entity = Knight::create();

        Vec2 pos = { visibleSize.width * 0.34f + origin.x, visibleSize.height * 0.5f + origin.y };
        entity->setPosition(pos);

        _playerTeam->add(ENTITY_TYPE::KNIGHT , entity);
    }

    //init archer
    {
        Archer* entity = Archer::create();

        Vec2 pos = { visibleSize.width * 0.21f + origin.x, visibleSize.height * 0.3f + origin.y };
        entity->setPosition(pos);

        _playerTeam->add(ENTITY_TYPE::ARCHER, entity);
    }

    //init pawn
    {
        Pawn* entity = Pawn::create();

        Vec2 pos = { visibleSize.width * 0.21f + origin.x, visibleSize.height * 0.7f + origin.y };
        entity->setPosition(pos);

        _playerTeam->add(ENTITY_TYPE::PAWN, entity);
    }
    
    for (const auto& entity : _playerTeam->getAllEntities())
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

        addChild(entity, LAYER::PLAYER);
    }
    
    //enemyInit
    {
        Goblin* entity = Goblin::create();

        Vec2 pos = { visibleSize.width * 0.7f + origin.x, visibleSize.height * 0.5f + origin.y };
        entity->setPosition(pos);
        
        _enemyTeam->add(ENTITY_TYPE::KNIGHT, entity);
    }


    for (const auto& entity : _enemyTeam->getAllEntities())
    {
#if true
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

        addChild(entity, LAYER::PLAYER);
    }

    //mouse Event
    {
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(BattleScene::mouseDownEvent , this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
    
    _battleManager->setTeam(_playerTeam.get() , _enemyTeam.get());
    //_enemyTeam->activeTeam(false);

    scheduleUpdate();

    return true;
}

void BattleScene::update(float dt)
{
    _battleManager->update(dt);
}

void BattleScene::mouseDownEvent(EventMouse* event)
{
    bool isplayerTurn = _battleManager->canPlayerInput();
    if (!isplayerTurn)return;

    Vec2 worldClick = event->getLocationInView();

    Entity* enemy = _battleManager->selectEnemyEntity(worldClick);
    if (enemy == nullptr)return;

    _battleManager->playPlayerTurn(enemy);
}



