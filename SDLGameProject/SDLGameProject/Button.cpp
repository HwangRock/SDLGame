#include "Button.h"
#include "SDL_image.h"
#include <iostream>


Button::Button
(
	int btnNum, int scaffoldNum,
	std::vector<std::vector<int>>buttonP,
	std::vector<std::vector<int>>startP,
	std::vector<std::vector<int>>endP,
	std::vector<SDL_Rect> scaffold
)
{

	for (int i = 0; i < btnNum; i++)
	{
		buttonPos.push_back({ buttonP[i][0],buttonP[i][1],20,20 });
	}
	
	for (int i = 0; i < scaffoldNum; i++)
	{
		startPos.push_back({ startP[i][0],startP[i][1],scaffold[i].w,scaffold[i].h });
		endPos.push_back({ endP[i][0],endP[i][1],scaffold[i].w,scaffold[i].h });
	}

	scaffold_= scaffold;

	Reset();
}

void
Button::Reset()
{
	for (int i = 0; i < scaffold_.size(); i++)
	{
		scaffold_[i].x = startPos[i].x;
		scaffold_[i].y = startPos[i].y;
		
	}	
	isPressed = false;
}


void
Button::Update()
{
	//double dt = timestep_s;	// seconds

	for (int i = 0; i < scaffold_.size(); i++)
	{
		if (isPressed == true)
		{
			if (Distance(scaffold_[i], endPos[i]) > 0.05)
			{
				//moving to endPos
				Move(scaffold_[i], endPos[i],i);
			}
		}
		else
		{
			if (Distance(scaffold_[i], startPos[i]) > 0.05)
			{
				//moving back to startPos
				Move(scaffold_[i], startPos[i],i);
			}
		}
	}
	

	
}

double Button::Distance(SDL_Rect& rect1, SDL_Rect& rect2)
{
	double distance = std::sqrt((rect2.x - rect1.x) * (rect2.x - rect1.x) + (rect2.y - rect1.y) * (rect2.y - rect1.y));
	return distance;
}

void Button::Move(SDL_Rect& from, SDL_Rect& to,int index)
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
	scaffold_[index].x = from.x + static_cast<int>(moveDistance * unitX);
	scaffold_[index].y = from.y + static_cast<int>(moveDistance * unitY);
}

void Button::SetPress(bool b)
{
	isPressed = b;
}