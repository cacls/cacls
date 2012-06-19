#ifndef __NPC_H__
#define __NPC_H__
#include "cocos2d.h"

class npc: public cocos2d::CCNode
{
public:
	npc();
	~npc();
	initNpc(char *, char*);

};

#endif
