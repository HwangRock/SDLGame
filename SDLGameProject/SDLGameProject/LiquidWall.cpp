#include "LiquidWall.h"


LiquidWall::LiquidWall(SDL_Rect pos, std::string dir)
{

	pos_ = pos;
	dir_ = dir;
}

SDL_Rect LiquidWall::returnWall() 
{

	SDL_Rect newWall;
	if (dir_ == "up") 
	{
		newWall.x = pos_.x;
		newWall.y = pos_.y + 15;
		newWall.w = pos_.w;
		newWall.h = pos_.h-15;
	}
	else if (dir_ == "down") 
	{
		newWall.x = pos_.x;
		newWall.y = pos_.y;
		newWall.w = pos_.w;
		newWall.h = pos_.h -15;
	
	}
	else if (dir_ == "left") 
	{
		//wall
		newWall.x = pos_.x + 15;
		newWall.y = pos_.y;
		newWall.w = pos_.w-15;
		newWall.h = pos_.h;
	}
	else if (dir_ == "right") 
	{
		//wall
		newWall.x = pos_.x;
		newWall.y = pos_.y;
		newWall.w = pos_.w-15;
		newWall.h = pos_.h;
	
	}

	return newWall;


}