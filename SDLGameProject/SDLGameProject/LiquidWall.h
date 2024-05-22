#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


class LiquidWall
{
public:

	SDL_Rect pos_;
	SDL_Rect fakepos_;
	std::string dir_;//물렁한곳 위치
	
	LiquidWall(SDL_Rect pos, std::string dir);
	SDL_Rect returnWall();

protected:



};