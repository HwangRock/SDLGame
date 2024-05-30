#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Key
{
public:

	SDL_Rect keyPos;
	SDL_Rect lockPos;
	bool isCollected;
	bool isLocked;

	Key(SDL_Rect keyPos_, SDL_Rect lockPos_)
	{
		isCollected = false;
		isLocked = true;
		keyPos = keyPos_;
		lockPos = lockPos_;
	};
	

protected:



};