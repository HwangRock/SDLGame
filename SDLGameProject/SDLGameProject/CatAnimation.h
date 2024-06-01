#pragma once
#include <vector>
#include "SDL.h"
#include "Pet.h"
#include "Cat.h"

class CatAnimation
{
public:
	int cat_move_type;
	int pre_move_type;

	std::vector<int>cat_move;
	
	void AddTexture();
};