#pragma once
#include <vector>
#include "SDL.h"

class DogAnimation
{
public:
	int dog_move_type;
	int pre_move_type;

	std::vector<int>dog_move;

	void AddTexture();
};
