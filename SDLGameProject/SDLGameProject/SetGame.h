#pragma once
#include "SDL.h"
#include<vector>

class SetGame
{
public:

	SetGame(int chapterNum);
	std::vector<int> SetTerrains();
protected:

	int chapterNum_;

};