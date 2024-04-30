#pragma once

#include <iostream>
#include <string>
#include "SDL.h"


#include "Pet.h"
#include "Terrain.h"
#include "Button.h"

#include "SDL_ttf.h"
#include "SDL_mixer.h"


#include <vector>
#include <windows.h>

#include "SDL_image.h"
#include "math.h"


class Stage3 : public PhaseInterface
{
public:
	Stage3();
	~Stage3();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	//Sprite
	SDL_Rect dogRect;
	SDL_Rect catRect;
	SDL_Texture* catTexture;
	SDL_Texture* dogTexture;
	SDL_Texture* wallTexture;
	SDL_Texture* buttonTexture;
	SDL_Texture* blindTexture;
	SDL_Rect wallRect;
	SDL_Rect buttonRect;

	//Pets
	Pet* dog = new Pet(200, 200,true);
	Pet* cat = new Pet(100, 100, false);

	// Mouse
	int mouse_win_x_;
	int mouse_win_y_;

	//Window size
	int win_w, win_h;


	// 중력 가속도
	float gravity = 0.098f;

	//Terrain
	Terrain* floorUp = new Terrain(200, 200, 800, 25);
	Terrain* floorDown = new Terrain(0, 500, 600, 25);

	

	Terrain* default1 = new Terrain(0, 680, 1000, 20);
	Terrain* default2 = new Terrain(0, 0, 1000, 20);
	Terrain* default3 = new Terrain(0, 0, 20, 700);
	Terrain* default4 = new Terrain(980, 0, 20, 700);

	std::vector<Terrain> walls =
	{
		*floorUp,*floorDown,
		*default1,*default2,*default3,*default4
	};

	std::vector<Button>buttons =
	{ };

	std::vector<SDL_Rect> blinds = {  };

};


