#include "tools.h"
#include "cocos2d.h"
#include "platform.h"
#include <cstring>

using namespace cocos2d;

bool strcmpex( const char *str1, const char *str2 )
{
	return !strcmp(str1,str2);
}

long millisecondNow() {	struct cc_timeval now;	CCTime::gettimeofdayCocos2d(&now, NULL);	return (now.tv_sec * 1000 + now.tv_usec / 1000);}

float heronsformula(float x1,float y1,float x2,float y2,float x3,float y3)
{
	float a=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	float b=sqrt(pow(x2-x3,2)+pow(y2-y3,2));
	float c=sqrt(pow(x3-x1,2)+pow(y3-y1,2));
	float s=(a+b+c)/2;

	return sqrt(s*(s-a)*(s-b)*(s-c));
}

bool triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py)
{
	float s1=heronsformula(x1,y1,x2,y2,px,py);
	float s2=heronsformula(x2,y2,x3,y3,px,py);
	float s3=heronsformula(x3,y3,x1,y1,px,py);
	float s=heronsformula(x1,y1,x2,y2,x3,y3);

	return abs(s-(s1+s2+s3))<0.001f;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//字符转换，使cocos2d-x在win32平台支持中文显示
#endif