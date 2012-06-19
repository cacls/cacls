#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "../game/Hero.h"
#include "../game/Map.h"

class GameScene : public cocos2d::CCLayer
{
public:
	~GameScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(GameScene);

	void setSceneScrollPosition(cocos2d::ccTime dt);
	void checkHeroDead(cocos2d::ccTime dt);
private:
	Hero 	*hero;
	Map 	*map;
};

#endif

