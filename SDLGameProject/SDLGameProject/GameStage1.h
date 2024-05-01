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
#include "SetGame.h"


class Stage1 : public PhaseInterface
{
public:
	Stage1();
	~Stage1();

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
	SDL_Rect blindRect;

	//Pets
	Pet* dog = new Pet(700, 100, true);
	Pet* cat = new Pet(600, 100, false);

	// Mouse
	int mouse_win_x_;
	int mouse_win_y_;

	//Window size
	int win_w, win_h;


	// 중력 가속도
	float gravity = 0.098f;


	//STAGE1/////////////////////////////////////////////////////////

	//Button
	Button* btn1 = new Button(2, 2, 
		{ {500, 480,20,20},{900,650,20,20} },
		{ { 700,600,150,25 },{100,400,150,25} },
		{ { 700, 500,150,25 },{100,300,150,25} },
		{ { 700, 600,150, 25 },{100,400,150,25} });
	std::vector<Button>buttons ={ *btn1 };



	//Terrain
	Terrain* floorUp = new Terrain(200, 200, 800, 25);
	Terrain* floorDown = new Terrain(0, 500, 600, 25);

	Terrain* Wall = new Terrain(400 - 25, 150, 25, 50);
	//Terrain* Scaffolding1 = new Terrain(200, 150, 200, 25);
	Terrain* Scaffolding2 = new Terrain(600, 100, 100, 25);
	Terrain* Scaffolding3 = new Terrain(500, 600, 100, 25);

	Terrain* default1 = new Terrain(0, 680, 1000, 20);
	Terrain* default2 = new Terrain(0, 0, 1000, 20);
	Terrain* default3 = new Terrain(0, 0, 20, 700);
	Terrain* default4 = new Terrain(980, 0, 20, 700);

	std::vector<Terrain> walls =
	{
		*floorUp,*floorDown,*Wall,
		*Scaffolding2,*Scaffolding3,
		*default1,*default2,*default3,*default4,
	};

	//Blind(sniff, dog skill)
	SDL_Rect blind1 = { 100,650,30,30 };
	SDL_Rect blind2 = { 200,650,30,30 };
	std::vector<SDL_Rect> blinds = { blind1,blind2 };


	//Liquid wall(cat skill)
	SDL_Rect lwall1 = { 200, 150, 200, 25 };
	std::vector<SDL_Rect>liquidWalls = { lwall1 };

	SDL_Rect laisle1 = { 200,175,200,30 };
	std::vector<SDL_Rect>liquidAisles = { laisle1 };


	//TEST
	SetGame *setGame = new SetGame(0);
	std::vector<int> hello;
};




