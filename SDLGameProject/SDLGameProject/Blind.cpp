#pragma once
#include "SDL.h"

class Blind
{
public:
	SDL_Rect pos;
	int pictureNum;

	Blind(SDL_Rect p,int pictureIndex) 
	{
		pos = p;
		pictureNum = pictureIndex;
	}
	

protected:

	

};