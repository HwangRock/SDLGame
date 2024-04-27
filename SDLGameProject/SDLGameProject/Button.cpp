#include "Button.h"
#include "SDL_image.h"
#include <iostream>


Button::Button
(
	SDL_Rect buttonP,
	SDL_Rect startP,
	SDL_Rect endP,
	SDL_Rect scaffold
)
{
	buttonPos = buttonP;
	startPos = startP;
	endPos = endP;
	scaffold_= scaffold;

	Reset();
}

void
Button::Reset()
{
	scaffold_.x = startPos.x;
	scaffold_.y = startPos.y;
	wait = 0;
	isPressed = false;
}


void
Button::Update()
{
	//double dt = timestep_s;	// seconds

	
	if (isPressed == true)
	{
		if (Distance(scaffold_, endPos) >=1)
		{
			std::cout << "move to end!!"<<"\n";

			
			if (wait != 3) { wait++; }
			else { scaffold_.y -= 2; wait = 0; }
		}
	}
	else
	{
		if (Distance(scaffold_, startPos) >=1)
		{
			std::cout << "move to start!" << "\n";
			if (wait != 3) { wait++; }
			else { scaffold_.y += 2; wait = 0; }
		}
	}
	

	std::cout << Distance(scaffold_, startPos)<<" " << Distance(scaffold_, endPos)<<"\n";
}

double Button::Distance(SDL_Rect& rect1, SDL_Rect& rect2)
{
	double distance = std::sqrt((rect2.x - rect1.x) * (rect2.x - rect1.x) + (rect2.y - rect1.y) * (rect2.y - rect1.y));
	return distance;
}

/*
void Button::Move(SDL_Rect& from, SDL_Rect& to)
{
	// 현재 위치에서 목표 위치까지의 벡터
	double dx = to.x - from.x;
	double dy = to.y - from.y;

	// 벡터의 크기 계산
	double distance = Distance(from,to);

	// 이동 거리 계산
	double moveDistance = moveSpeed_ * distance;

	// 이동 방향 단위 벡터 계산
	double unitX = dx / distance;
	double unitY = dy / distance;

	// 새로운 위치 계산
	scaffold_.x = from.x + static_cast<int>(moveDistance * unitX);
	scaffold_.y = from.y + static_cast<int>(moveDistance * unitY);
}
*/


void Button::SetPress(bool b)
{
	isPressed = b;
}