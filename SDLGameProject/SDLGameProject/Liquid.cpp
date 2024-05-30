#include "SDL.h"
#include <string>

class Liquid
{
public:
	SDL_Rect pos;
	SDL_Rect wallPos;
	SDL_Rect liquidPos;
	int wallDepth;
	int liquidDepth=10;
	std::string liquidClass;

	Liquid(SDL_Rect p,std::string liquidName)
		:pos(p),liquidClass(liquidName)
	{
		liquidPos = { pos.x,pos.y,pos.w,liquidDepth };
		wallPos = { pos.x,pos.y + liquidDepth,pos.w,pos.h-liquidDepth };
	}

};