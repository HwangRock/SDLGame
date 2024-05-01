#pragma once
#include "SDL.h"
#include "GameStage1.h"
#include "Terrain.h"
#include "Button.h"
#include<vector>

class Map1 : public Stage1
{
public:
	Map1();
	

protected:

	int chapterNum_;
	std::vector<Terrain>terrains_;
	std::vector<Button>buttons_;
	std::vector <SDL_Rect>blinds_;
	std::vector<SDL_Rect>lwalls_;
	std::vector<SDL_Rect>laisles_;
};