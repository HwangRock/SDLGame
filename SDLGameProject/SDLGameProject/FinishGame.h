#pragma once

#include "SDL.h"
#include "Game.h"

class Finish : public PhaseInterface
{
public:
	Finish();
	~Finish();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void UpdateSourceRectangle();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
};
