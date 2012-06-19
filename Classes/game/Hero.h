#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "../util/type.h"

class Hero : public cocos2d::CCNode
{
public:
	Hero();
	~Hero();
	static Hero *hero();
	bool init();

	void acceptTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void acceptTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void acceptTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	cocos2d::CCRect getRect();
private:
	cocos2d::CCAnimate *getAnimate();
	void moveDoneCallback();
	void deadDoneCallback();

	cocos2d::CCSprite *sprite;
	Behaviour behaviour;
	Direction direction;	

	cocos2d::CCPoint touchPoint;
};

#endif //__HERO_H__