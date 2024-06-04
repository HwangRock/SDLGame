#include "Cat.h"
#include "Stage.h"

void Cat::Reset()
{
	Pet::Reset();
	isDog = false;
	isLiquid = false;
	isClimbWall = false;
}

void Cat::Update(double timestep_s)
{
	std::cout << isLiquid << "\n";
	//CLIMB WALL////////////////////////////////////////////
	isClimbWall = false;
	for (int k = 0; k < climbWalls.size(); k++)
	{
		
		if (SDL_HasIntersection(&pos, &climbWalls[k].wall_pos))
		{
			BlockMoving(climbWalls[k].wall_pos);
			if (pos.y <= climbWalls[k].wall_pos.y + climbWalls[k].wall_pos.h - 1&&
				pos.y+pos.h>= climbWalls[k].wall_pos.y+1)
			{
				isClimbWall = true;
			}
			else
			{
				std::cout << "climb wall out of boundary\n";
			}
		}
		/*
		if (pos.x + pos.w < climbWalls[k].wall_pos.x || pos.x > climbWalls[k].wall_pos.x + climbWalls[k].wall_pos.w ||
			pos.y + pos.h < climbWalls[k].wall_pos.y || pos.y > climbWalls[k].wall_pos.y + climbWalls[k].wall_pos.h) {
			isClimbWall == false;
		}
		else if (pos.y + pos.h == climbWalls[k].wall_pos.y) { isClimbWall == false; }
		else { isClimbWall = true; }
		*/
	}

	if (isClimbWall == true) { v[1] = -1.5f; } //0.098f
	else if(v[1] <= 6.5) { v[1] += gravity; }

	//UPDATE///////////////////////////////////////////////////
	Pet::Update(timestep_s);
	 

	//WATER///////////////////////////////////////////////////
	for (Liquid l : liquid)
	{
		if (SDL_HasIntersection(&l.liquidPos, &pos))
		{
			
			if (nowInput == 1 || nowInput == 2) {Mix_PlayChannel(-1, liquidSound, 0);}

			if (l.liquidClass == "water") 
			{
				std::cout << "touch water->die\n";
				isDead = true;
			}

		}
	}
	for (int i = 0; i < s_liquid.size(); i++)
	{
		if (SDL_HasIntersection(&s_liquid[i].nowPos, &pos))
		{
			if (nowInput == 1 || nowInput == 2) { Mix_PlayChannel(-1, liquidSound, 0); }

			if (s_liquid[i].liquidClass == "water")
			{
				std::cout << "touch water->die\n";
				isDead = true;
			}
		}
	}




	//EAT FISH////////////////////////////////////////////////
	for (auto& f : fish) {
		if (SDL_HasIntersection(&f.pos, &pos))
		{
			f.pos.x = -10000000000, f.pos.y = -10000000000000;
			Mix_PlayChannel(4, eatingSound, 0);
			score_fish++;
		}
	}
	

	


	//CAT LIQUID SKILL/////////////////////////////////////////
	isLiquid = false;
	for (int j = 0; j < liquidWalls.size(); j++)
	{
		if (SDL_HasIntersection(&pos, &liquidWalls[j].pos_))
		{
			isLiquid = true;
		}	
	}


	//GOAL//////////////////////////////////
	isInGoal = false;
	if (goal.size() == 1)
	{
		if (SDL_HasIntersection(&pos, &goal[0]))
		{
			isInGoal = true;
		}
	}
	else
	{
		if (SDL_HasIntersection(&pos, &goal[1]))
		{
			isInGoal = true;
		}
	}

	//BOX//////////////////////////////////
	for (const Box& b : boxs)
	{
		if (SDL_HasIntersection(&pos, &b.box_pos))
		{
			BlockMoving(b.box_pos);
		}
	}

}

void Cat::HandleEvent(SDL_Event event)
{
	Pet::HandleEvent(event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		
		if (event.key.keysym.sym == SDLK_a)
		{
			v[0] = -1.0f; keyDownNum = 1;
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			v[0] = 1.0f; keyDownNum = 2;
		}
		else if (event.key.keysym.sym == SDLK_w)
		{
			if (jumping == false)
			{
				v[1] = jumpSpeed();
				Mix_PlayChannel(2, meow, 0);
				jumping = true;
			}
		}
		

		if (keyDownNum != 0)
		{
			for (int i = inputs.size() - 1; i >= 0; i--)
			{
				if (inputs[i] != keyDownNum && keyDownNum != 0)
				{
					if (i == 0) { inputs.push_back(keyDownNum); }
				}
				else { break; }
			}
			keyDownNum = 0;
		}
		break;


	case SDL_KEYUP:

		
		if (event.key.keysym.sym == SDLK_a)
		{
			keyUpNum = 1;
		}
		else if (event.key.keysym.sym == SDLK_d)
		{
			keyUpNum = 2;
		}
		else if (event.key.keysym.sym == SDLK_w)
		{
			//catKeyUp = 3;	
		}
		
		

		if (keyUpNum != 0)
		{
			for (int i = inputs.size() - 1; i >= 0; i--)
			{
				if (inputs[i] == keyUpNum)
				{
					//dog->v[0] = 0.0f;
					inputs.erase(inputs.begin() + i);
					keyUpNum = 0;
					break;
				}

			}
		}


		break;
	}
}
