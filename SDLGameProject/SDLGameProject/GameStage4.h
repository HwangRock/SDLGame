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


class Stage4 : public PhaseInterface
{
public:
	Stage4();
	~Stage4();

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
	SDL_Rect blindRect;
	SDL_Rect wallRect;
	SDL_Rect buttonRect;

	//Pets
	Pet* dog = new Pet(200, 200, true);
	Pet* cat = new Pet(100, 100, false);

	// Mouse
	int mouse_win_x_;
	int mouse_win_y_;

	//Window size
	int win_w, win_h;


	// 중력 가속도
	float gravity = 0.098f;


	Terrain* floor1 = new Terrain(200,125,1000-200,25);
	Terrain* floor2 = new Terrain(900, 100, 100, 25);

	Terrain* floor3 = new Terrain(0, 300, 100, 25);
	Terrain* floor4 = new Terrain(100, 370, 100, 25);
	Terrain* floor5 = new Terrain(0, 440, 100, 25);
	Terrain* floor6 = new Terrain(100, 510, 100, 25);

	Terrain* floor7 = new Terrain(200+100,250, 400, 25);
	Terrain* floor8 = new Terrain(200, 380, 400, 25);
	Terrain* floor9 = new Terrain(200 + 100, 525, 100, 25);
	Terrain* floor10 = new Terrain(200+300, 525, 200, 25);

	Terrain* floor11 = new Terrain(700, 300, 150, 25);
	Terrain* floor12 = new Terrain(950, 300, 100, 25);
	Terrain* floor13 = new Terrain(700, 400, 100, 25);
	Terrain* floor14 = new Terrain(870, 400, 130, 25);
	Terrain* floor15 = new Terrain(700, 525, 130, 25);
	Terrain* floor16 = new Terrain(900, 525, 100, 25);

	Terrain* wall1 = new Terrain(200, 250, 25, 700-200);
	Terrain* wall2 = new Terrain(700, 250, 25, 300);
	Terrain* wall3 = new Terrain(700, 610, 25, 700-610);

	//Terrain
	Terrain* default1 = new Terrain(0, 680, 1000, 20);
	Terrain* default2 = new Terrain(0, 0, 1000, 20);
	Terrain* default3 = new Terrain(0, 0, 20, 700);
	Terrain* default4 = new Terrain(980, 0, 20, 700);

	std::vector<Terrain> walls =
	{
		*floor1,*floor2,
		*floor3,*floor4,*floor5,*floor6,
		*floor7,* floor8,* floor9,* floor10,
		* floor11,* floor12,* floor13,* floor14,*floor15,*floor16,
		*wall1,*wall2,*wall3,
		*default1,*default2,*default3,*default4
	};

	std::vector<Button>buttons =
	{ };

	std::vector<SDL_Rect> blinds = {  };
	std::vector<SDL_Rect>liquidWalls = { };
	std::vector<SDL_Rect>liquidAisles = { };
};


