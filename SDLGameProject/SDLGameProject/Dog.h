#pragma once
#include <vector>
#include "Terrain.h"
#include "Button.h"
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
	void Update(
		double timestep_s,
		std::vector<Terrain>& walls,
		std::vector<Button>& buttons,
		SDL_Texture* blindTexture,
		std::vector<SDL_Rect>& liquidWalls,
		std::vector<SDL_Rect>& liquidAisle
	);
	void HandleEvent(SDL_Event event);

protected:
	// dog skill variables
	bool beBlurry_;
	bool isSkill_;//skill��밡�� ����, dog�� ���
	int blindOpacity_;//0~255 ���� ����, -1�̸� ���� �ȸð� �ִ���

};