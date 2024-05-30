#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Choco
{
public:

	SDL_Rect choco_pos;
	Choco(SDL_Rect pos)
	{
		choco_pos = pos;
	};

};