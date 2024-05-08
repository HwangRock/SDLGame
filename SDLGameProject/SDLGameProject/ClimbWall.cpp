#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class ClimbWall
{
public:

	SDL_Rect wall_pos;
	ClimbWall(SDL_Rect pos)
	{
		wall_pos = pos;
	};

};