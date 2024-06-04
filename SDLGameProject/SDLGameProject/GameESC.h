#pragma once
#include "SDL.h"
#include "Game.h"

extern bool isFirst;

class ESC : public PhaseInterface
{
public:
	ESC();
	~ESC();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	
	SDL_Rect button1_rect_; //resume button
	SDL_Rect button2_rect_; //go to intro button
	SDL_Rect button3_rect_; //control button
	SDL_Rect button4_rect_; //exit button
};