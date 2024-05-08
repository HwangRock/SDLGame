#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"


#include "math.h"

#include "Dog.h"
#include "Cat.h"
#include "Pet.h"

#include "Terrain.h"
#include "Button.h"
#include "LiquidWall.h"
#include "ClimbWall.cpp"

#include "Game.h"


extern std::vector<Terrain> walls;
extern std::vector<Button> buttons;
extern std::vector<SDL_Rect> blinds;
extern std::vector<LiquidWall>liquidWalls;
extern std::vector<SDL_Rect>liquidAisles;
extern std::vector<ClimbWall>climbWalls;
extern SDL_Rect goal;
extern SDL_Rect start;
extern int chapterNum;
extern int win_w, win_h;     

class StageInterface : public PhaseInterface
{
public:
	StageInterface();
	~StageInterface();

	virtual void SetVar();
	virtual void Reset();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	
	void NextChapter();

private:
	//Sprite
	SDL_Rect dogRect;
	SDL_Rect catRect;
	SDL_Texture* catTexture;
	SDL_Texture* dogTexture;
	SDL_Texture* liquidCatTexture;
	SDL_Texture* wallTexture;
	SDL_Texture* buttonTexture;
	SDL_Texture* blindTexture;
	SDL_Texture* cwallTexture;
	SDL_Texture* goalTexture;
	SDL_Rect goalRect;
	SDL_Rect cwallRect; 
	SDL_Rect wallRect;
	SDL_Rect buttonRect;
	SDL_Rect blindRect;

	//Pets
	//Pet* dog = new Pet(700, 100, true);
	//Pet* cat = new Pet(600, 100, false);
	Dog* dog = new Dog(700, 100);
	Cat* cat = new Cat(600, 100);

	// Mouse
	int mouse_win_x_;
	int mouse_win_y_;



	// gravity
	float gravity = 0.098f;

	bool isFirst;

};




