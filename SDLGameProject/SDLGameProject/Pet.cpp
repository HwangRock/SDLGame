#include "Pet.h"
#include "SDL_image.h"
#include <math.h>
#include <iostream>
#include "Stage.h"




Pet::Pet(double x, double y)
{
	size_ = 30;

	mass_ = 2; // 2kg
	coeff_of_restitution_ = 0.7;

	pos_[0] = x;
	pos_[1] = y;

	pos.x = x;
	pos.y = y;
	pos.w = 50;
	pos.h = 50;


	Reset();
}

void
Pet::Reset()
{
	v[0] = 0;
	v[1] = 0;

	nowInput = 0;
	keyDownNum = 0;
	keyUpNum = 0;
	inputs.push_back(0);
	jumping = false;
	isDead = false;
	isInGoal = false;
	haveKey = false;
	isPressing = -1;
}


void
Pet::Update(double timestep_s)
{
	double dt = timestep_s;	// seconds


	//MOVING/////////////////////////////////////////////////


	nowInput = inputs[inputs.size() - 1];
	//left
	if (nowInput == 1) { pos.x -= 2; }
	//right
	else if (nowInput == 2) { pos.x += 2; }
	//up
	pos.y += v[1];



	//MOVING LIMIT//////////////////////////////////////////////////
	for (int i = 0; i < walls.size(); i++)
	{
		if (SDL_HasIntersection(&pos, &walls[i].pos))
		{
			BlockMoving(walls[i].pos);
			//break;
		}
	}



	for (auto& missile : mis) {
		if (SDL_HasIntersection(&mis[0].misile_pos, &pos))
		{
			pos.x = 1000000, pos.y = 10000000;
			over++;
		}
	}

	//PRESS BUTTON/////////////////////////////////////////////////////////////
	for (int i = 0; i < buttons.size(); i++)
	{

		for (int j = 0; j < buttons[i].scaffold_.size(); j++)
		{
			if (SDL_HasIntersection(&pos, &buttons[i].scaffold_[j]))
			{
				BlockMoving(buttons[i].scaffold_[j]);
				//break;
			}
		}

		/*
		for (int j = 0; j < buttons[i].buttonNum; j++)
		{
			if (SDL_HasIntersection(&pos, &buttons[i].buttonPos[j]))
			{
				//Pressing button
				isPressing = i;
				break;
			}
			else
			{
				//if (isPressing == i)
				//{ isPressing = -1; }
			}
		}
		*/

		//FADE FLOOR///////////////////////////////////////////////////////
		for (int j = 0; j < fadefloors.size(); j++)
		{
			if (SDL_HasIntersection(&pos, &fadefloors[j].floor_pos))
			{
				BlockMoving(fadefloors[j].floor_pos);
				isCollide = 1;
				break;
			}
		}
	}

	//KEY///////////////////////////////////
	for (int i = 0; i < keys.size(); i++)
	{
		if (SDL_HasIntersection(&pos, &keys[i].keyPos)&&keys[i].isCollected==false&&haveKey==false)
		{
			keys[i].isCollected = true;
			haveKey = true;
			std::cout << "we have key\n";
		}
		if (SDL_HasIntersection(&pos, &keys[i].lockPos))
		{
			if (keys[i].isCollected == true&&haveKey==true) 
			{ 
				keys[i].isLocked = false; 
				haveKey = false;
			}
			else if (keys[i].isLocked == true) { BlockMoving(keys[i].lockPos); }
		}

	}

	if (v[1] > 1) {
		jumping = true;
	}

	/*
	double a[2];
	a[0] = 0;
	a[1] = room_->gravitational_acc_y();// Gravity

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];

	//속도 = 이전속도 + 시간(dt) * 가속도;
	v_[0] = v_[0] + dt * a[0];
	v_[1] = v_[1] + dt * a[1];
	*/
}

void Pet::BlockMoving(SDL_Rect obst)
{
	if (pos.y + pos.h >= obst.y + 7 &&
		pos.y <= obst.y + obst.h - 7)
	{

		if (pos.x < obst.x + obst.w / 2)
		{
			//std::cout << "left\n";
			//pos.x = min(pos.x, obst.x - pos.w);
			pos.x = obst.x - pos.w;
			//jumping = true;
		}

		else if (pos.x + pos.w > obst.x)
		{
			//std::cout << "right\n";
			//pos.x = max(pos.x, obst.x + obst.w);
			pos.x = obst.x + obst.w;
			//jumping = true;
		}

	}
	else
	{
		if (pos.y + pos.h <= obst.y + obst.h / 2)
		{
			//std::cout << "up\n";

			//pos.y = obst.y - pos.h;
			pos.y = obst.y - pos.h < pos.y ? obst.y - pos.h : pos.y;
			//pos.y = std::min(obst.y - pos.h,pos.y);
			v[1] = 0;
			jumping = false;
		}
		else
		{
			//std::cout << "down\n";

			//pos.y = obst.y + obst.h;
			pos.y = obst.y + obst.h > pos.y ? obst.y + obst.h : pos.y;
			//pos.y = std::max(obst.y + obst.h, pos.y);
			v[1] = 0;
			//jumping = true;
		}
	}
}


void
Pet::HandleEvent(SDL_Event event)
{




}
