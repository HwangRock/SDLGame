#pragma once
#include <vector>
#include "Terrain.h"
#include "Button.h"
#include "LiquidWall.h"
#include "ClimbWall.cpp"

#include "Choco.cpp"
#include "Water.cpp"
#include "Milk.cpp"

#include "SDL.h"
#include "Pet.h"

class Dog:public Pet
{
public:

	Dog(double x, double y) : Pet(x, y)
	{
		Reset();
	}


	void Reset();
	void Update( double timestep_s	);
	void HandleEvent(SDL_Event event);

protected:
	// dog skill variables
	bool beBlurry_;
	bool isSkill_;//skill사용가능 여부, dog만 사용
	int blindOpacity_;//0~255 투명도 정도, -1이면 냄새 안맡고 있는중
        virtual void BMoving(SDL_Rect obst) override;
};
