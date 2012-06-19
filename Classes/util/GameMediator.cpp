#include "GameMediator.h"

#include <typeinfo>
#include <algorithm>
#include "tools.h"

using namespace cocos2d;
using namespace std;

void GameMediator::addHero( Hero *hero)
{
	this->hero=hero;
}

CCPoint GameMediator::checkMoveable( CCPoint from, CCPoint to )
{
	return map->checkMovePoint(from, to);	
}

void GameMediator::addMap( Map *map )
{
	this->map=map;
}

void GameMediator::addGameScene( GameScene *gameScene )
{
	this->gameScene=gameScene;
}


bool GameMediator::deleteNode( cocos2d::CCNode *node )
{
	
	if (strcmpex(typeid(*node).name(),"class Hero"))
	{
	}
	else if (strcmpex(typeid(*node).name(),"class Npc"))
	{
	}
	else if (strcmpex(typeid(*node).name(),"class Player"))
	{	
	}

	gameScene->removeChild(node,true);

	return true;
}

