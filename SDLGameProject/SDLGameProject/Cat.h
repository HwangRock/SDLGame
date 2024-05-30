#pragma once
#include <vector>
#include "Terrain.h"
#include "Button.h"
#include "LiquidWall.h"
#include "ClimbWall.cpp"
#include "Cushion.h"
#include "FadeFloor.h"


#include "SDL.h"
#include "Pet.h"

class Cat :public Pet
{
public:


	Cat(double x, double y) : Pet(x,y) 
	{
		Reset();
	}

	void Reset();
	void Update(double timestep_s);
	void HandleEvent(SDL_Event event);


	bool isLiquid;
	bool isClimbWall;

protected:
	

};
