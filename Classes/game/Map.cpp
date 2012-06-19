#include "map.h"

using namespace cocos2d;

Map::Map(void)
{
}

Map::~Map(void)
{
}

CCPoint Map::checkMovePoint(CCPoint from, CCPoint to)
{
	return to;
}

Map* Map::initMap()
{
	Map *map = new Map;

	CCSprite * sprite = CCSprite::SpriteWithFile("backgroud.jpg");
	this->addChild(sprite, 1)
	return map;
}
