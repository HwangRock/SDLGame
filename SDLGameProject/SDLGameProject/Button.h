#pragma once
#include <vector>
#include "Terrain.h"
#include "SDL.h"

class Button
{
public:
	std::vector<SDL_Rect>scaffold_;
	bool isPressed;

	std::vector<SDL_Rect> buttonPos;

	Button
	(
		int btnNum, int scaffoldNum,
		std::vector<std::vector<int>>buttonP,
		std::vector<std::vector<int>>startP,
		std::vector<std::vector<int>>endP,
		std::vector<SDL_Rect> scaffold
	);

	double Distance(SDL_Rect& rect1, SDL_Rect& rect2);
	void Move(SDL_Rect& from, SDL_Rect& to,int index);
	void SetPress(bool b);

	void Reset();
	virtual void Update();


protected:

	double moveSpeed_=0.02;

	
	std::vector<SDL_Rect> startPos;
	std::vector<SDL_Rect> endPos;

};