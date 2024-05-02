#pragma once
#include "SDL.h"
#include "Game.h"
#include "GameFinish.cpp"

class Clear : public GameFinish
{
public:
	Clear();
	~Clear();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* fishTexture;
	SDL_Texture* boneTexture;
	SDL_Rect fishRect;
	SDL_Rect boneRect;
	SDL_Rect fishScore;
	SDL_Rect boneScore;

};


