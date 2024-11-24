#pragma once
#include "SDL.h"

class Intro : public PhaseInterface
{
public:
	Intro();
	~Intro();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Texture* txt_texture_;
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	SDL_Rect srect_txt;
	SDL_Rect drect_txt;

	int blinkingTime;
	int lastBlinkingTime;
	bool txtBlinking;
};


