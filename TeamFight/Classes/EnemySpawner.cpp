#include "EnemySpawner.h"
#include "Enum.h"

#define SPAWN_DURATION 0.25f

EnemySpawner::EnemySpawner()
{
}

EnemySpawner::~EnemySpawner()
{
}

Entity* EnemySpawner::EnemySpawn(Vec2 pos)
{
	Entity* entity = Goblin::create();
	entity->setScale(0.5f);
	entity->setPosition(pos);

#if IS_THIS_DEBUG
        auto drawNode = DrawNode::create();
        auto boundingBox = entity->getMainSprite()->getBoundingBox();

        boundingBox.origin.x += boundingBox.size.width / 4;
        boundingBox.origin.y += boundingBox.size.height / 4;
        boundingBox.size.width /= 2;
        boundingBox.size.height /= 2;

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
    
	auto sclaeAction = ScaleTo::create(SPAWN_DURATION, 1);
	entity->runAction(sclaeAction);

	cocos2d::Director::getInstance()->getRunningScene()->addChild(entity);

	return entity;
}
