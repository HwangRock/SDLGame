#pragma once
#include <vector>
#include "Terrain.h"
#include "SDL.h"

class Button
{
public:
	std::vector<SDL_Rect> scaffold_;
	bool isPressed;
	int wait;
	std::vector<SDL_Rect> buttonPos;
	int buttonNum_;
	int scaffoldNum_;

	Button
	(
		int buttonNum, int scaffoldNum,
		std::vector<SDL_Rect> buttonP,
		std::vector<SDL_Rect> startP,
		std::vector<SDL_Rect> endP,
		std::vector<SDL_Rect> scaffold
	);

	double Distance(SDL_Rect& rect1, SDL_Rect& rect2);
	//void Move(SDL_Rect& from, SDL_Rect& to);
	void SetPress(bool b);


	void Reset();
	virtual void Update();


protected:

	double moveSpeed_=0.05;
	
	
	std::vector<SDL_Rect> startPos;
	std::vector<SDL_Rect> endPos;

};