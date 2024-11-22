#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include "Torch.h"
#include "Stage.h"

Torch::Torch
(
	int torchNum, int darkNum,
    std::vector<SDL_Rect> dark, //어두운 부분
	std::vector<SDL_Rect> torchP,
	int op
) 
{
	dark_ = dark;
	torchPos = torchP;
	torchNum_ = torchNum;
	darkNum_ = darkNum;
	opacity = op;

	Reset();
}

void Torch::Reset() {
	isTouched = false;

	opacity = 255;
}

void Torch::Update() {
	if (isTouched == true) {

		if (opacity > 0)
			opacity--;
	}
}


void Torch::Touch(bool t) {
	isTouched = t;
}
