#pragma once
#include <vector>
#include "Terrain.h"
#include "SDL.h"

class Button
{
public:
	std::vector<SDL_Rect> scaffold_;
	bool isPressed;
	bool isStop;
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
	void Move(SDL_Rect& start, SDL_Rect& end, SDL_Rect& obj);

	void Reset();
	virtual void Update();
	void petOverlap(const SDL_Rect& obj);

protected:

	double moveSpeed_=0.05;
	bool blockingX;
	bool blockingY;
	

	double v_x;
	double v_y;
	std::vector<SDL_Rect> startPos;
	std::vector<SDL_Rect> endPos;

};