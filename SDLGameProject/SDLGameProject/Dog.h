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


class Dog:public Pet
{
public:

	bool box_collide;
	int blindOpacity_;//

	Dog(double x, double y) : Pet(x, y)
	{
		Reset();
	}

	void Reset();
	void Update( double timestep_s	);
	void HandleEvent(SDL_Event event);


	void BoxMoving();
protected:
	// dog skill variables
	bool beBlurry_;
	bool isSkill_;//
	bool moving;
	
};
