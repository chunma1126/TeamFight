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
    
    //init unique_ptr
    {
        _playerTeam = std::make_unique<Team>();
        _enemyTeam = std::make_unique<Team>();
        _battleManager = std::make_unique<BattleManager>();
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 screenCenter = { visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y };

    std::string defaultString = "";
    _mainLabel = Label::createWithTTF(defaultString.c_str(), "fonts/SunBatang/SunBatang-Bold.ttf", 35);

    _mainLabel->setPosition(screenCenter.x , visibleSize.height * 0.92f);
    addChild(_mainLabel);

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
        
        _enemyTeam->add(ENTITY_TYPE::KNIGHT, entity);
        addChild(entity);
    }

    //mouse Event
    {
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::mouseDownEvent , this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
    
    _battleManager->setTeam(_playerTeam.get() , _enemyTeam.get());

    scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt)
{
    _battleManager->update(dt);
}

void HelloWorld::mouseDownEvent(EventMouse* event)
{
    bool isplayerTurn = _battleManager->canPlayerInput();
    
    if (!isplayerTurn)return;

    Vec2 worldClick = event->getLocationInView();
    _currentEntity = selectPlayerEntity(worldClick);

    /*if (_currentEntity != nullptr)
    {
        auto sizeUpEvent = ScaleTo::create(0.1f, 1.1f);
        _currentEntity->runAction(sizeUpEvent);
    }*/
    
    for (const auto& entity : _enemyTeam->getAllEntities())
    {
        Rect entityRect = entity->getMainSprite()->getBoundingBox();
        Vec2 localPos = entity->convertToNodeSpace(worldClick);

        if (entityRect.containsPoint(localPos))
        {
            _battleManager->submitPlayerCommand(new BattleCommand(3.0f, [&]()
                {
                    _currentEntity->playAnimation(ANIMATION_STATE::ATTACK1,false);
                }));
            _battleManager->submitPlayerCommand(new BattleCommand(0.4f, [&]()
                {
                    _playerTeam->activeTeam(false);
                    _enemyTeam->activeTeam(true);
                }));
        }

    }

}



Entity* HelloWorld::selectPlayerEntity(cocos2d::Vec2& worldClick)
{
    //currentEntity = nullptr;


    for (const auto& entity : _playerTeam->getAllEntities())
    {
        Rect entityRect = entity->getMainSprite()->getBoundingBox();
        Vec2 localPos = entity->convertToNodeSpace(worldClick);

        if (entityRect.containsPoint(localPos))
        {
            _currentEntity = entity;
            _mainLabel->setString(_currentEntity->getSkill()->name.c_str());
        }
    }

    
    
    return _currentEntity;
}
