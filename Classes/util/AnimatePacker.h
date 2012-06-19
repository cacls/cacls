#ifndef _ANIMATE_PACKER_H_
#define _ANIMATE_PACKER_H_

#include "cocos2d.h"
#include "Singleton.h"

class AnimatePacker:public Singleton<AnimatePacker>
{
public:
	void loadAnimate(char *path);
	cocos2d::CCAnimate* getAnimate(char *name);
};

#endif//_ANIMATE_PACKER_H_

