#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Milk
{
public:

	SDL_Rect milk_pos;
	Milk(SDL_Rect pos)
	{
		milk_pos = pos;
	};

};