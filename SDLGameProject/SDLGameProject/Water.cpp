#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Water
{
public:

	SDL_Rect water_pos;
	Water(SDL_Rect pos)
	{
		water_pos = pos;
	};

};