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


extern std::vector<Terrain> walls;
extern std::vector<Button> buttons;
extern std::vector<SDL_Rect> blinds;
extern std::vector<SDL_Rect>liquidWalls;
extern std::vector<SDL_Rect>liquidAisles;


class Stage1 : public PhaseInterface
{
public:
	Stage1();
	~Stage1();

	void Start();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();




	
	SetGame* setGame = new SetGame(0);

	


	

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


	// gravity
	float gravity = 0.098f;



	


};




