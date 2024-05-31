#include "FadeFloor.h"

FadeFloor::FadeFloor(SDL_Rect pos)
{
	floor_pos = pos;
	isCollide = false;
	alpha = 255;
}

void FadeFloor::Reset()
{
	isCollide = false;
	alpha = 255;
}

void FadeFloor::Update()
{
	if (isCollide == true && alpha > 0)
	{
		//투명도를 점점 줄인후에 바닥 rect를 아예 화면 밖으로 이동
		alpha-=fadeSpeed;

		if (alpha == 0)
		{ 
			floor_pos.y = 100000;
			isCollide = false;
		}
	}
}

void FadeFloor::CollideFloor(bool a)
{
	isCollide = a;
}
