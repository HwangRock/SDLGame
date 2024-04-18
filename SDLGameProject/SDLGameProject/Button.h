#pragma once
#include <vector>
#include "Terrain.h"
#include "SDL.h"

class Button
{
public:
	SDL_Rect buttonPos;

	SDL_Rect nowPos;
	SDL_Rect startPos;
	SDL_Rect endPos;
	bool isPressed;


	Button(double w, double h, double btnX, double btnY, double startX, double startY, double endX, double endY);
	double Distance(SDL_Rect& rect1, SDL_Rect& rect2);
	void Move(SDL_Rect& from, SDL_Rect& to);
	void SetPress(bool b);

	void Reset();
	virtual void Update(double timestep_s);


protected:

	double moveSpeed_=0.1;
	double progress_;

};