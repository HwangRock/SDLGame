#include "Terrain.h"
#include "SDL_image.h"
#include <iostream>

Terrain::Terrain(double x, double y, double w, double h)
{
	

	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;


	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
}