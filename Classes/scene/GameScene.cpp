#include "GameScene.h"
#include "../util/GameMediator.h"
#include "../util/AnimatePacker.h"

using namespace cocos2d;

cocos2d::CCScene* GameScene::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GameScene *layer = GameScene::node();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;

}

bool GameScene::init()
{
	bool bRet = false;
	do	{
		CC_BREAK_IF(! CCLayer::init());

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		//清理
		GameMediator::getInstance()->release();

		//瓦片地图
		map=Map::initMap();
		this->addChild(map,1);
		CCSize mapSize=map->getContentSize();

		//地图底色
		//GLfloat width=mapSize.width;
		//GLfloat height=mapSize.height;
		//CCLayerColor *layerColor=CCLayerColor::layerWithColorWidthHeight(ccc4f(0,151,0,255),width,height);
		//this->addChild(layerColor,0);

		//加载动画资源
		AnimatePacker::getInstance()->loadAnimate("three_kingdom_anime.xml");

		//生成精灵
		hero=Hero::hero();
		this->addChild(hero,2);
		hero->setPosition(ccp(0,0));

		//注册
		GameMediator::getInstance()->addHero(hero);
		//GameMediator::getInstance()->addMap(map);
		GameMediator::getInstance()->addGameScene(this);

		this->schedule(schedule_selector(GameScene::setSceneScrollPosition));
	//	this->schedule(schedule_selector(GameScene::checkHeroDead));

		//开启触摸
		this->setIsTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

//由于这不是触摸精灵的关系（而是触摸屏幕），所以我们通过转发把信息处理权交给hero
void GameScene::ccTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	hero->acceptTouchesBegan(pTouches,pEvent);
}

void GameScene::ccTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	hero->acceptTouchesMoved(pTouches,pEvent);
}

void GameScene::ccTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	hero->acceptTouchesEnded(pTouches,pEvent);
}

void GameScene::setSceneScrollPosition(cocos2d::ccTime dt)
{
	CCPoint position=hero->getPosition();
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	/*CCSize mapSizeInPixel = map->
	();

	if (mapSizeInPixel.width>screenSize.width)
	{
		float x=position.x-screenSize.width/2.0f;
		//limit(0.0f,x,mapSizeInPixel.width-screenSize.width);
		this->setPosition(ccp(-x,this->getPosition().y));
	}

	if (mapSizeInPixel.height>screenSize.height)
	{
		float y=position.y-screenSize.height/2.0f;
		//limit(0.0f,y,mapSizeInPixel.height-screenSize.height);
		this->setPosition(ccp(this->getPosition().x,-y));
	}*/
}

GameScene::~GameScene()
{
	this->unscheduleAllSelectors();
}

void GameScene::checkHeroDead( cocos2d::ccTime dt )
{
	//GameMediator::getInstance()->checkHeroDead();
}
