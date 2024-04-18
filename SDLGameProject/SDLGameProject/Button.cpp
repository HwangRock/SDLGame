#include "Button.h"
#include "SDL_image.h"
#include <iostream>


Button::Button(
	double w, double h, 
	double btnX,double btnY, 
	double startX,double startY,
	double endX,double endY)
{
	buttonPos.x = btnX;
	buttonPos.y = btnY;
	buttonPos.w =20;
	buttonPos.h = 20;

	startPos.x = startX;
	startPos.y = startY;
	startPos.w = w;
	startPos.h = h;


	endPos.x = endX;
	endPos.y = endY;
	endPos.w = w;
	endPos.h = h;


	Reset();
}

void
Button::Reset()
{
	nowPos.x = startPos.x;
	nowPos.y = startPos.y;
	nowPos.w = startPos.w;
	nowPos.h = startPos.h;

	isPressed = false;
	progress_ = 1/16;
}


void
Button::Update(double timestep_s)
{
	double dt = timestep_s;	// seconds

	//std::cout << isPressed << "\n";

	if (isPressed == true)
	{
		//std::cout << "pressed" << "\n";
		if (Distance(nowPos,endPos)>2)
		{
			//moving to endPos
			Move(nowPos, endPos);
		}
	}
	else
	{
		//std::cout << "not pressed" << "\n";
		if (Distance(nowPos, startPos) > 2)
		{
			//moving back to startPos
			Move(nowPos, startPos);
		}
	}

	
}

double Button::Distance(SDL_Rect& rect1, SDL_Rect& rect2)
{
	double distance = std::sqrt((rect2.x - rect1.x) * (rect2.x - rect1.x) + (rect2.y - rect1.y) * (rect2.y - rect1.y));
	return distance;
}

void Button::Move(SDL_Rect& from, SDL_Rect& to)
{
	// 현재 위치에서 목표 위치까지의 벡터
	double dx = to.x - from.x;
	double dy = to.y - from.y;

	// 벡터의 크기 계산
	double distance = std::sqrt(dx * dx + dy * dy);

	// 이동 거리 계산
	double moveDistance = moveSpeed_ * distance;

	// 이동 방향 단위 벡터 계산
	double unitX = dx / distance;
	double unitY = dy / distance;

	// 새로운 위치 계산
	nowPos.x = from.x + static_cast<int>(moveDistance * unitX);
	nowPos.y = from.y + static_cast<int>(moveDistance * unitY);
}

void Button::SetPress(bool b)
{
	isPressed = b;
}