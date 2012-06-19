#include "Hero.h"
#include "../util/type.h"
#include "tools.h"
//#include "../util/constant.h"
#include "../util/AnimatePacker.h"
#include "../util/GameMediator.h"

using namespace cocos2d;

Hero::Hero()
{
}

Hero::~Hero()
{
}

Hero * Hero::hero()
{
	Hero *hero = new Hero();

	if (hero && hero->init())
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return NULL;
}

bool Hero::init()
{
	bool bRet = false;
	do{
		this->setAnchorPoint(CCPointZero);

		//创建动画

		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("role_breathe0001.png");
		sprite=CCSprite::spriteWithSpriteFrame(frame);//指定一张初始图片
		//CCPoint *p =cc(sprite->getCcontentSize());
		sprite->setAnchorPoint(CCPointZero);
		this->addChild(sprite);

		//设置状态
		behaviour=STAND;
		direction=DOWN;

		sprite->runAction(CCRepeatForever::actionWithAction(getAnimate()));

		bRet=true;
	}while(0);

	return bRet;
}

//注意，不同精灵，这个函数写法不同，主要区别都是OVERLOOK上，有些精灵是没有四方向的
CCAnimate * Hero::getAnimate()
{
	CCAnimate* animate;
	if (behaviour==STAND)
	{
		animate = AnimatePacker::getInstance()->getAnimate("role_breathe");
	}else
	{
		animate = AnimatePacker::getInstance()->getAnimate("role_run");
	}
	return animate;
}

//双击埋雷
void Hero::acceptTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	if (behaviour==DEAD)
		return;

	static long touchTime=millisecondNow();

	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	touchPoint=touch->locationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);//转换坐标系，很重要

	long time=millisecondNow();

	if (time-touchTime<250)
	{
		//float x=(int)this->getPosition().x/TILE_SIZE*TILE_SIZE;
		//float y=(int)this->getPosition().y/TILE_SIZE*TILE_SIZE;
		//GameMediator::getInstance()->mineBomb(ccp(x,y));
	}

	touchTime=time;
}

//滑动移动
void Hero::acceptTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	//if (behaviour==MOVE||behaviour==DEAD)
		//return;
	//int TILE_SIZE = 10;
	CCPoint r = this->getPosition();
	CCTouch *touch2=(CCTouch*)pTouches->anyObject();
	CCPoint touchPoint2=touch2->locationInView();
	touchPoint2 = CCDirector::sharedDirector()->convertToGL(touchPoint2);//转换坐标系，很重要
	float deltaX=touchPoint2.x-r.x;
	float deltaY=touchPoint2.y-r.y;

	CCPoint targetPosition;
	targetPosition = touchPoint2;//ccpAdd(this->getPosition(), ccp(deltaX,deltaY));
	CCFiniteTimeAction *moveByAction;
	behaviour=MOVE;
	//float d
	float float_x = abs(deltaX)/10*0.2f;
	moveByAction=CCMoveBy::actionWithDuration(float_x,ccp(deltaX, deltaY));
	sprite->stopAllActions();
	CCAction *sequneceAction = CCSequence::actions(moveByAction,CCCallFunc::actionWithTarget(this, callfunc_selector(Hero::moveDoneCallback)),NULL);
	this->runAction(sequneceAction);
	sprite->runAction(CCRepeatForever::actionWithAction(getAnimate()));
}

void Hero::acceptTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{

}

void Hero::moveDoneCallback()
{
	behaviour=STAND;
	sprite->stopAllActions();
	sprite->runAction(CCRepeatForever::actionWithAction(getAnimate()));
}


cocos2d::CCRect Hero::getRect()
{
	return CCRectMake(this->getPosition().x,this->getPosition().y,60,100);
}
