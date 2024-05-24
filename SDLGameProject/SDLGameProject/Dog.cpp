#include "Dog.h"
#include "Stage.h"


void Dog::Reset()
{
	Pet::Reset();

	beBlurry_ = true;
	isSkill_ = true;
	blindOpacity_ = -1;
}

void Dog::Update(double timestep_s)
{

	v[1] += gravity;
	Pet::Update(timestep_s);

	//SNIFF////////////////////////////////////////////////////////////
	if (blindOpacity_ != -1)
	{
		SDL_SetTextureAlphaMod(blindTexture, blindOpacity_);
		if (blindOpacity_ == 0)
		{
			beBlurry_ = false;
		}


		if (beBlurry_ == true)
		{
			blindOpacity_--;
		}
		else
		{
			blindOpacity_++;
		}

		if (blindOpacity_ == 255)
		{
			blindOpacity_ = -1;
		}
	}

	for (auto& b : bone) {
	if (SDL_HasIntersection(&b.pos, &pos))
	{
		b.pos.x = -10000000000, b.pos.y = -10000000000000;
		score += 10;
		std::cout << "score : " << score << "\n";
		}
	}

	//CUSHION////////////////////////////////////////////////
	for (int k = 0; k < cushions.size(); k++)
	{
		if (SDL_HasIntersection(&pos, &cushions[k].cushion_pos))
		{
			BlockMoving(cushions[k].cushion_pos);
			jump_speed = -7.0f;
		}
		else
		{
			if (k == cushions.size() - 1)
			{
				jump_speed = -3.5f;
			}
		}
	}

	//LIQUID////////////////////////////////////////////////////////////
	//same with normal 

	for (int j = 0; j < liquidWalls.size(); j++)
	{
		if (SDL_HasIntersection(&pos, &liquidWalls[j].pos_))
		{
			BlockMoving(liquidWalls[j].pos_);
		}
	}
	for (int j = 0; j < liquidAisles.size(); j++)
	{
		if (SDL_HasIntersection(&pos, &liquidAisles[j]))
		{
			BlockMoving(liquidAisles[j]);
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
		if (SDL_HasIntersection(&pos, &goal[0]))
		{
			isInGoal = true;
		}
		else { isInGoal = false; }
	}
	
	//BOX MOVING
	for (const Box& b : boxs)
	{
		if (SDL_HasIntersection(&pos, &b.box_pos))
		{
			BoxMoving(b.box_pos);
		}
	}

}

void Dog::HandleEvent(SDL_Event event)
{
	Pet::HandleEvent(event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			keyDownNum = 1;
			v[0] = -1.0f;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			keyDownNum = 2;
			v[0] = 1.0f;
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			if (jumping == false)
			{
				v[1] = jumpSpeed();
				jumping = true;
			}
		}
		
		if (event.key.keysym.sym == SDLK_RSHIFT)
		{
			if (isSkill_ == true)
			{
				//Use Sniffing Skill
				blindOpacity_ = 254;
				isSkill_ = false;
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

		
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			keyUpNum = 1;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			keyUpNum = 2;
		}
		else if (event.key.keysym.sym == SDLK_UP)
		{
			//dogKeyUp = 3;	
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

void Dog::BoxMoving(SDL_Rect obst) {
	for (auto& b : boxs) {
		if (SDL_HasIntersection(&pos, &b.box_pos) and (pos.y + pos.h /2 >= b.box_pos.y + b.box_pos.h / 2)) {
			if (pos.x + pos.w / 2 < b.box_pos.x + b.box_pos.w / 2) {
				b.box_pos.x += 2.0f; // Move box to the right
			}
			else {
				b.box_pos.x -= 2.0f; // Move box to the left
			}
			if (pos.x > b.box_pos.x) {
				pos.x = b.box_pos.x + 90;
			}
			else if (pos.x < b.box_pos.x) {
				pos.x = b.box_pos.x - 50;
			}
			return;
		}
	}
	if (pos.y + pos.h <= obst.y + obst.h / 2) {
		pos.y = obst.y - 50;
		v[1] = 0;
		jumping = false;
	}
	else {
		if (pos.x > obst.x) {
			pos.x = obst.x + 90;
		}
		else if (pos.x < obst.x) {
			pos.x = obst.x - 50;
		}
	}
}
