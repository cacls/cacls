#ifndef _GAME_MEDIATOR_H_
#define _GAME_MEDIATOR_H_

#include "cocos2d.h"
#include "../util/Singleton.h"
#include "../game/Hero.h"
#include "../game/Map.h"
#include "../scene/GameScene.h"

#include <vector>

class GameMediator:public Singleton<GameMediator>
{
public:
	void addHero(Hero *hero);
	void addMap(Map* map);
	void addGameScene(GameScene *gameScene);

	cocos2d::CCPoint checkMoveable(cocos2d::CCPoint from, cocos2d::CCPoint to);
	bool deleteNode(cocos2d::CCNode *node);
private:
	//bool collisionWithBombs(cocos2d::CCPoint position);
	Map *map;
	Hero *hero;
	GameScene *gameScene;

	//std::vector<Bomb*> bombs;
	//std::vector<Monster*> monsters;
};

#endif //_GAME_MEDIATOR_H_


