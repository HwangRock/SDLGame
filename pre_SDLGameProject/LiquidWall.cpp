#include "LiquidWall.h"


LiquidWall::LiquidWall(SDL_Rect pos, std::string dir)
{

	pos_ = pos;
	dir_ = dir;
}

SDL_Rect LiquidWall::returnWall() 
{
	std::cout << dir_ << "\n";
	SDL_Rect newWall;
	if (dir_ == "up") 
	{
		newWall.x = pos_.x;
		newWall.y = pos_.y + 20;
		newWall.w = pos_.w;
		newWall.h = pos_.h-20;
	}
	else if (dir_ == "down") 
	{
		newWall.x = pos_.x;
		newWall.y = pos_.y;
		newWall.w = pos_.w;
		newWall.h = pos_.h -20;
	
	}
	else if (dir_ == "left") 
	{
		newWall = { 0,0,0,0 };
		//wall
		newWall.x = pos_.x + 20;
		newWall.y = pos_.y;
		newWall.w = pos_.w-20;
		newWall.h = pos_.h;
	}
	else if (dir_ == "right") 
	{
		//wall
		newWall.x = pos_.x;
		newWall.y = pos_.y;
		newWall.w = pos_.w-20;
		newWall.h = pos_.h;

	}

	return newWall;


}