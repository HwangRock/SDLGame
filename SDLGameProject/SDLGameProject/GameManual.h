#pragma once
#include "SDL.h"
#include "Game.h"

class Manual : public PhaseInterface
{
public:
	Manual();
	~Manual();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Texture* texture_2; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect button_rect_; //return button
};
