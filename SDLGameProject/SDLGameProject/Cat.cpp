#include "Cat.h"
#include "Stage.h"

void Cat::Reset()
{
	Pet::Reset();
	isLiquid = false;
	isClimbWall = false;
}

void Cat::Update(double timestep_s)
{

	//CLIMB WALL//////////////////////////////
	for (int k = 0; k < climbWalls.size(); k++)
	{
		if (SDL_HasIntersection(&pos, &climbWalls[k].wall_pos))
		{
			BlockMoving(climbWalls[k].wall_pos);
			isClimbWall = true;
		}
		else
		{
			if (k == climbWalls.size() - 1)
			{
				isClimbWall = false;
			}
		}
	}

	if (isClimbWall == false) { v[1] += gravity; }

	for (auto& f : fish) {
		if (SDL_HasIntersection(&f.pos, &pos))
		{
		f.pos.x = -10000000000, f.pos.y = -10000000000000;
		score += 10;
		std::cout << "score : " << score << "\n";
		}
	}
	


	//UPDATE///////////////////////////////////////////////////
	Pet::Update(timestep_s);
	



	//CAT LIQUID SKILL/////////////////////////////////////////

	//sprite change

	isLiquid = false;
	//skill
	for (int j = 0; j < liquidWalls.size(); j++)
	{
		if (SDL_HasIntersection(&pos, &liquidWalls[j].pos_))
		{
			
			isLiquid = true;

			SDL_Rect newWall;
			newWall = liquidWalls[j].returnWall();
			std::cout << "liquidWall "<<j<<"=" << newWall.x << ", " << newWall.y << ", " << newWall.w << ", " << newWall.h << "\n";
			
			if (liquidWalls[j].dir_ != "right"&& liquidWalls[j].dir_ != "left") 
			{
				BlockMoving(newWall);
			}			
		}	

	}

	//GOAL//////////////////////////////////
	if (goal.size() == 1)
	{
		if (SDL_HasIntersection(&pos, &goal[0]))
		{
			isInGoal = true;
		}
		else { isInGoal = false; }
	}
	else
	{
		if (SDL_HasIntersection(&pos, &goal[1]))
		{
			isInGoal = true;
		}
		else { isInGoal = false; }
	}

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
