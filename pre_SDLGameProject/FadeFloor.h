#pragma once

#include "Terrain.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


class FadeFloor
{
public:
	bool isCollide;
	SDL_Rect floor_pos;
	int alpha;

	FadeFloor(SDL_Rect pos);

	void Reset();
	void Update();
	void CollideFloor(bool a);

	double fadeSpeed = 5;
};