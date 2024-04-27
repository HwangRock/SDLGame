#pragma once
#include <vector>
#include "Terrain.h"
#include "SDL.h"

class Button
{
public:
	SDL_Rect scaffold_;
	bool isPressed;
	int wait;
	SDL_Rect buttonPos;

	Button
	(
		SDL_Rect buttonP,
		SDL_Rect startP,
		SDL_Rect endP,
		SDL_Rect scaffold
	);

	double Distance(SDL_Rect& rect1, SDL_Rect& rect2);
	//void Move(SDL_Rect& from, SDL_Rect& to);
	void SetPress(bool b);

	void Reset();
	virtual void Update();


protected:

	double moveSpeed_=0.05;
	
	
	SDL_Rect startPos;
	SDL_Rect endPos;

};