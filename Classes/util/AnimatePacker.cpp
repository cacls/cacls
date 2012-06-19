#include "AnimatePacker.h"
#include "CCSAXParser.h"

using namespace std;
using namespace cocos2d;

struct Animate{
	string name;
	float delay;
	vector<string> spriteFrames;
};

class AnimateSaxDelegator : public CCSAXDelegator
{
public:
	enum{STATE_NONE,STATE_PLIST,STATE_ANIMATION,STATE_NAME,STATE_DELAY,STATE_SPRITEFRAME}state;
	void startElement(void *ctx, const char *name, const char **atts) ;
	void endElement(void *ctx, const char *name) ;
	void textHandler(void *ctx, const char *s, int len) ;

	vector<string> plists;//所有plist名称
	vector<Animate> animates;//所有animate数据
};

void AnimateSaxDelegator::startElement( void *ctx, const char *name, const char **atts )
{
	string tag((char*)name);

	if (tag=="plist")
	{
		state=STATE_PLIST;
	} 
	else if (tag=="animation")
	{
		state=STATE_ANIMATION;
		animates.push_back(Animate());
	}
	else if (tag=="name")
	{
		state=STATE_NAME;
	}
	else if (tag=="delay")
	{
		state=STATE_DELAY;
	}
	else if (tag=="spriteFrame")
	{
		state=STATE_SPRITEFRAME;
	}
	else
	{
		state=STATE_NONE;
	}
}

void AnimateSaxDelegator::endElement( void *ctx, const char *name )
{
	string tag((char*)name);

	if (tag=="plist")
	{
	} 
	else if (tag=="animation")
	{
	}
	else if (tag=="name")
	{
	}
	else if (tag=="delay")
	{
	}
	else if (tag=="spriteFrame")
	{
	}
	else
	{
		
	}

	state = STATE_NONE;
}

void AnimateSaxDelegator::textHandler( void *ctx, const char *ch, int len )
{
	if (state == STATE_NONE)
	{
		return;
	}

	string text((char*)ch,0,len);//文本节点的文本
	int index;
	float delay;

	switch (state)
	{
	case STATE_PLIST:
		plists.push_back(text);
		break;
	case STATE_ANIMATION:
		break;
	case STATE_NAME:
		index=animates.size()-1;
		animates[index].name=text;
		break;
	case STATE_DELAY:
		index=animates.size()-1;
		delay=atof(text.c_str());
		animates[index].delay=delay;
		break;
	case STATE_SPRITEFRAME:
		index=animates.size()-1;
		animates[index].spriteFrames.push_back(text);
		break;
	default:
		break;
	}

}

void AnimatePacker::loadAnimate( char *path )
{
	//解析xml////////////////////////////////////
	const char *pszPath = CCFileUtils::fullPathFromRelativePath(path);//从相对路径得到绝对全路径

	CCSAXParser parser;
	AnimateSaxDelegator delegator;

	if (false == parser.init("UTF-8"))
	{
		//TODO
		return;
	}
	parser.setDelegator(&delegator);
	parser.parse(pszPath);

	//加载plist////////////////////////////////////
	vector<string> plists=delegator.plists;
	for (int i=0;i<plists.size();i++)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plists[i].c_str());
	}

	//缓冲animate////////////////////////////////////
	vector<Animate> animates=delegator.animates;
	CCMutableArray<CCSpriteFrame*> *spriteFramesArray = new CCMutableArray<CCSpriteFrame*>();

	for (int i=0;i<animates.size();i++)
	{
		Animate animate=animates[i];
		vector<string> spriteFrames=animate.spriteFrames;

		for (int j=0;j<spriteFrames.size();j++)
		{
			CCSpriteFrame *spriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrames[j].c_str());
			spriteFramesArray->addObject(spriteFrame);
		}

		CCAnimation *animation=CCAnimation::animationWithFrames(spriteFramesArray,animate.delay);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,animate.name.c_str());

		spriteFramesArray->removeAllObjects();
	}
	
}

cocos2d::CCAnimate* AnimatePacker::getAnimate( char *name )
{
	CCAnimation* animation=CCAnimationCache::sharedAnimationCache()->animationByName(name);

	if(animation)
	{
		return cocos2d::CCAnimate::actionWithAnimation(animation);
	}
	return NULL;
}
