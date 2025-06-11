#include "TileMap.h"
#include "Enum.h"

#define TILE_MAP_PATH "Tilemap/BattleBackground.tmx"

bool TileMap::init()
{
	if (!Node::init())
	{
		return false;
	}

    for (int i = 0; i < 3; i++)
    {
        _timeMapList[i] = TMXTiledMap::create(TILE_MAP_PATH);

        auto& layers = _timeMapList[i]->getChildren();
        for (auto& child : layers)
        {
            auto layer = dynamic_cast<SpriteBatchNode*>(child);
            if (layer)
            {
                layer->getTexture()->setAliasTexParameters();
            }
        }

        float offsetX = _timeMapList[i]->getContentSize().width * i;
        _timeMapList[i]->setPosition(Vec2(static_cast<int>(offsetX + 0.5f), 0));

        addChild(_timeMapList[i], LAYER::BACKGROUND);
    }


    _tileWidth = _timeMapList[0]->getContentSize().width;

	return true;
}

void TileMap::move(float duration)
{
    float halfWidth = _tileWidth / 2.0f;

    for (int i = 0; i < 3; i++)
    {
        auto tile = _timeMapList[i];
        auto move = MoveBy::create(duration, Vec2(-halfWidth, 0));

        auto check = CallFunc::create([this, tile]() {
            float rightEdgeX = tile->getPositionX() + _tileWidth;
            if (rightEdgeX < 0)
            {
                float maxRight = 0;
                for (int j = 0; j < 3; j++)
                {
                    if (_timeMapList[j] == tile) continue;

                    float right = _timeMapList[j]->getPositionX() + _tileWidth;
                    if (right > maxRight)
                        maxRight = right;
                }

                tile->setPositionX(maxRight);
            }
            });

        auto seq = Sequence::create(move, check, nullptr);
        tile->runAction(seq);
    }
}




