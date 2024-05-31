#include "Button.h"
#include "SDL_image.h"
#include <iostream>


Button::Button
(
	int buttonNum,int scaffoldNum,
	std::vector<SDL_Rect> buttonP,
	std::vector<SDL_Rect> startP,
	std::vector<SDL_Rect> endP,
	std::vector<SDL_Rect> scaffold
)
{
	buttonPos = buttonP;
	startPos = startP;
	endPos = endP;
	scaffold_= scaffold;
	buttonNum_ = buttonNum;
	scaffoldNum_ = scaffoldNum;

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
	
	wait = 0;
	isPressed = false;
	isStop = false;
}


void Button::petOverlap(const SDL_Rect &obj) 
{
	isStop = false;

	/*
	if (SDL_HasIntersection(&obj, &scaffold_[0]))//이거 고쳐야함
	{

		//아 왜 이게 안되냐!!!!!!!!!!!!!!!!!!!1
	}
	*/

	for (int i = 0; i < scaffold_.size(); i++)
	{
		if (obj.x <= scaffold_[i].x + scaffold_[i].w && obj.x + obj.w >= scaffold_[i].x)
		{
			if (obj.y + obj.h >= scaffold_[i].y + 5)
			{
				
				//벽의 아래에 있음
				if (std::abs(obj.y - (scaffold_[i].y + scaffold_[i].h)) <= 5 && v_y>=1)
				{
					std::cout << "vy=" << v_y << " distance=" << std::abs(obj.y - (scaffold_[i].y + scaffold_[i].h)) << "\n";
					isStop = true;
					break;
				}

			}
			else if (obj.y + obj.h <= scaffold_[i].y + 5)
			{
				//벽 위에 있음
				if (std::abs(obj.y + obj.h - (scaffold_[i].y)) <= 1)
				{
					//std::cout << "danger!\n";  //isStop = true;
					//break;
				}
			}
		}
		
	}
	
	
}
void
Button::Update()
{
	
	//아직 제약이 많음. 무조건 위로 올라갔다 내려오는거, 두개의 발판 동시에 움직이는 경우에는 발판이 이동하는 거리가 똑같아야함
	if (isPressed == true)
	{
		if (Distance(scaffold_[0], endPos[0]) >= 2)
		{
			//std::cout << "move to end!!" << "\n";


			if (wait != 3) { wait++; }
			else 
			{ 
				for (int i = 0; i < scaffold_.size(); i++)
				{
					Move(scaffold_[i], endPos[i], scaffold_[i]);
				}
				wait = 0; 
			}
		}
	}
	else
	{
		if (Distance(scaffold_[0], startPos[0]) >= 2)
		{
			//std::cout << "move to start!" << "\n";
			if (wait != 3) { wait++; }
			else 
			{ 
				for (int i = 0; i < scaffold_.size(); i++)
				{
					Move(scaffold_[i], startPos[i], scaffold_[i]);
				}
				wait = 0; 
			}
		}
	}


	//std::cout << Distance(scaffold_, startPos)<<" " << Distance(scaffold_, endPos)<<"\n";
}

double Button::Distance(SDL_Rect& rect1, SDL_Rect& rect2)
{
	double distance = std::sqrt((rect2.x - rect1.x) * (rect2.x - rect1.x) + (rect2.y - rect1.y) * (rect2.y - rect1.y));
	return distance;
}

void Button::Move(SDL_Rect& start, SDL_Rect& end, SDL_Rect& obj)
{
	//vector
	v_x = end.x - start.x;
	v_y = end.y - start.y;

	double distance = Distance(start, end);
	
	if (isStop == false)
	{
		obj.x += (v_x / distance) * 2;
		obj.y += (v_y / distance) * 2;
	}
	
}


void Button::SetPress(bool b)
{
	isPressed = b;
}