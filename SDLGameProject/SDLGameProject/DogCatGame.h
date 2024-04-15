#pragma once

#include <iostream>
#include <string>
#include "SDL.h"


#include "Pet.h"
#include "Terrain.h"

#include "SDL_ttf.h"
#include "SDL_mixer.h"


#define MAX_BALL_NUM 1000


class DogCatGame
{
public:
	DogCatGame();
	~DogCatGame();
	void Render();
	void Update();
	void HandleEvents();


protected:



	//Sprite
	SDL_Rect dogRect;
	SDL_Rect catRect;
	SDL_Texture* catTexture;
	SDL_Texture* dogTexture;
	SDL_Texture* wallTexture;
	SDL_Rect wallRect;

	//Pets
	Pet* dog=new Pet(200,200,50,true);
	Pet* cat=new Pet(100,100,50,false);

	// Mouse
	int mouse_win_x_;
	int mouse_win_y_;

	//Window size
	int win_w, win_h;


	// 중력 가속도
	float gravity = 0.098f;

};