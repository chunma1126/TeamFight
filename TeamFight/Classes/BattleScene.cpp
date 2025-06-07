#include "BattleScene.h"
#include "Entities.h"
#include "TileMap.h"

#include "Enum.h"

USING_NS_CC;


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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 screenCenter = { visibleSize.width * 0.5f + origin.x , visibleSize.height * 0.5f + origin.y };

    //init unique_ptr
    {
        _battleManager = std::make_unique<BattleManager>();
    }

    //init positions
    {
        std::vector<Vec2> playerPositionList;
        
        playerPositionList.reserve(3);
        playerPositionList.push_back({ visibleSize.width * 0.34f + origin.x, visibleSize.height * 0.5f + origin.y });
        playerPositionList.push_back({ visibleSize.width * 0.21f + origin.x, visibleSize.height * 0.3f + origin.y });
        playerPositionList.push_back({ visibleSize.width * 0.21f + origin.x, visibleSize.height * 0.7f + origin.y });

        std::vector<Vec2> enemyPositionList;
        enemyPositionList.reserve(3);
        enemyPositionList.push_back({ visibleSize.width * 0.7f + origin.x, visibleSize.height * 0.5f + origin.y });
        enemyPositionList.push_back({ visibleSize.width * 0.85f + origin.x, visibleSize.height * 0.3f + origin.y });
        enemyPositionList.push_back({ visibleSize.width * 0.85f + origin.x, visibleSize.height * 0.7f + origin.y });

        _battleManager->setPositions(playerPositionList, enemyPositionList);
    }

    //init tilemap
    {
        auto timeMap = TileMap::create();
        _battleManager->onLevelClearEvent.add([=](float value)
            {
                timeMap->move(value);
            });
        addChild(timeMap, LAYER::BACKGROUND);
    }

    

//    //init EnemyEntity
//    for (const auto& entity : _enemyTeam->getAllEntities())
//    {
//#if IS_THIS_DEBUG
//        auto drawNode = DrawNode::create();
//        auto boundingBox = entity->getMainSprite()->getBoundingBox();
//
//        boundingBox.origin.x += boundingBox.size.width / 4;
//        boundingBox.origin.y += boundingBox.size.height / 4;
//        boundingBox.size.width /= 2;
//        boundingBox.size.height /= 2;
//
//
//        Vec2 bottomLeft(boundingBox.getMinX(), boundingBox.getMinY());
//        Vec2 bottomRight(boundingBox.getMaxX(), boundingBox.getMinY());
//        Vec2 topRight(boundingBox.getMaxX(), boundingBox.getMaxY());
//        Vec2 topLeft(boundingBox.getMinX(), boundingBox.getMaxY());
//
//        drawNode->drawPolygon(
//            std::vector<Vec2>{bottomLeft, bottomRight, topRight, topLeft}.data(),
//            4,
//            Color4F(0, 0, 0, 0),
//            1.0f,
//            Color4F::RED
//        );
//
//        entity->addChild(drawNode);
//#endif 
//
//        addChild(entity, LAYER::ENEMY);
//    }

    //mouse Event
    {
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(BattleScene::mouseDownEvent , this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    }
    
    scheduleUpdate();

    return true;
}

void BattleScene::onEnter()
{
    Scene::onEnter();
    _battleManager->init();
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
    int selectSkillIndex = _battleManager->getSelectSkillIndex();

    if (enemy == nullptr || selectSkillIndex == -1)return;

    _battleManager->playPlayerTurn(enemy,selectSkillIndex);
}



