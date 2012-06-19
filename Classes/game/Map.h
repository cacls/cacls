#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"
#include "../util/type.h"

class Map : public cocos2d::CCNode
{
public:
	Map(void);
	~Map(void);
	static Map* initMap();
	cocos2d::CCPoint checkMovePoint(cocos2d::CCPoint from, cocos2d::CCPoint to);
};

#endif 