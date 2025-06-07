#pragma once
#include "cocos2d.h"

USING_NS_CC;

class TileMap : public Node
{
public:
	virtual bool init();
	void move(float duration);

	CREATE_FUNC(TileMap);
private:
	TMXTiledMap* _timeMapList[3] = {};
	float _tileWidth = 0.0f;
};


