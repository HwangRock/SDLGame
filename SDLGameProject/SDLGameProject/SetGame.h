#pragma once
#include "SDL.h"
#include "Terrain.h"
#include "Button.h"
#include<vector>

class SetGame
{
public:

	SetGame(int chapterNum);
	std::vector<Terrain> SetTerrains();
	std::vector<Button> SetButtons();
	std::vector<SDL_Rect> SetBlinds();
	std::vector<SDL_Rect> SetLiquidWalls();
	std::vector<SDL_Rect> SetLiquidAisles();

protected:

	int chapterNum_;
	std::vector<Terrain>terrains_;
	std::vector<Button>buttons_;
	std::vector <SDL_Rect>blinds_;
	std::vector<SDL_Rect>lwalls_;
	std::vector<SDL_Rect>laisles_;
};