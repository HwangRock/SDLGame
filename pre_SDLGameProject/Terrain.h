#pragma once
#include "SDL.h"


class Terrain
{
public:

	SDL_Rect pos;
	Terrain(double x, double y, double w, double h);
	
protected:

	double x_;
	double y_;
	double w_;
	double h_;

};