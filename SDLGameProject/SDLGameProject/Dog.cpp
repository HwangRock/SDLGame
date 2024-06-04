#include "Dog.h"
#include "Stage.h"


void Dog::Reset()
{
	Pet::Reset();

	isDog = true;
	beBlurry_ = true;
	isSkill_ = true;
	box_collide = false;
	blindOpacity_ = -1;
	moving = true;
}

void Dog::Update(double timestep_s)
{

	if (v[1] <= 6.5) { v[1] += gravity; }

	Pet::Update(timestep_s);

	//MILK////////////////////////////
	for (Liquid l : liquid)
	{
		if (SDL_HasIntersection(&l.liquidPos, &pos))
		{
			if(nowInput == 1 || nowInput == 2){Mix_PlayChannel(-1, liquidSound, 0);	}

			if (l.liquidClass == "milk") 
			{
				//std::cout << "touch milk->die\n"; //종성: 게임 오버 화면 보기 위해 일부러 켜뒀습니다! 불편하신 분은 끄셔도 돼요!
				isDead = true;
			}
		}
	}
	//swelling liquid
	for (int i = 0; i < s_liquid.size(); i++)
	{
		if (SDL_HasIntersection(&s_liquid[i].nowPos, &pos))
		{
			if (nowInput == 1 || nowInput == 2) { Mix_PlayChannel(-1, liquidSound, 0); }

			if (s_liquid[i].liquidClass == "milk") 
			{
				//std::cout << "touch milk->die\n"; //종성: 게임 오버 화면 보기 위해 일부러 켜뒀습니다! 불편하신 분은 끄셔도 돼요!
				isDead = true;
			}
		}
	}


	//CLIMB WALL///////////////////////////////////////////////////////
	for (int i = 0; i < climbWalls.size(); i++)
	{
		if (SDL_HasIntersection(&climbWalls[i].wall_pos, &pos))
		{
			BlockMoving(climbWalls[i].wall_pos);
		}
	}

	//SNIFF////////////////////////////////////////////////////////////
	if (blindOpacity_ != -1)
	{
		if (blindOpacity_ == 0)
		{
			beBlurry_ = false;
		}


		if (beBlurry_ == true)
		{
			//���������
			blindOpacity_--;
			moving = false;
		}
		else
		{
			//�Ƿ���������
			blindOpacity_++;
			moving = false;
		}

		//end skill
		if (blindOpacity_ == 255)
		{
			blindOpacity_ = -1;
			moving = true;
		}
	}

	//BONE////////////////////////////////////////////////////
	for (auto& b : bone) {
		if (SDL_HasIntersection(&b.pos, &pos))
		{
			b.pos.x = -10000000000, b.pos.y = -10000000000000;
			Mix_PlayChannel(3, eatingSound, 0);
			score_bone++;
			
		}
	}

	

	//LIQUID WALL////////////////////////////////////////////////////////////
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
	isInGoal = false;
	if (SDL_HasIntersection(&pos, &goal[0]))
	{
		isInGoal = true;
	}
	

	//BOX//////////////////////////////////
	for (const Box& b : boxs)
	{
		if (SDL_HasIntersection(&pos, &b.box_pos))
		{
			BoxMoving();
			//box_collide = true;
		}

		if (pos.x + pos.w < b.box_pos.x || pos.x > b.box_pos.x + b.box_pos.w ||
			pos.y + pos.h < b.box_pos.y || b.box_pos.y + b.box_pos.h < pos.y||
			pos.y + pos.h == b.box_pos.y)
		{
			box_collide = false;
		}
		else
		{
			box_collide = true;
		}
	}
}

void Dog::HandleEvent(SDL_Event event)
{
	Pet::HandleEvent(event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (moving)
		{
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
					Mix_PlayChannel(1, bark, 0);
					jumping = true;
				}
			}

			if (event.key.keysym.sym == SDLK_RSHIFT)
			{
				if (isSkill_ == true)
				{
					//Use Sniffing Skill
					std::cout << "sniff skill\n";
					Mix_PlayChannel(-1, sniff, 0);
					blindOpacity_ = 254;
					isSkill_ = false;
				}
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

void Dog::BoxMoving() 
{
	for (Box& b : boxs) 
	{
		if (SDL_HasIntersection(&pos, &b.box_pos)) 
		{
			if (pos.y + pos.h <= b.box_pos.y + 5 && pos.y + pos.h >= b.box_pos.y - 5) 
			{ 
				// Dog is on top of the box
				pos.y = b.box_pos.y - pos.h; // Position the dog on top of the box
				v[1] = 0; // Reset the vertical velocity to 0 so the dog stays on the box
				jumping = false; // Allow the dog to jump again
			}
			else
			{
				if (pos.x + pos.w / 2 < b.box_pos.x + b.box_pos.w / 2) {
					b.box_pos.x += 2.0f; // Move box to the right
				}
				else {
					b.box_pos.x -= 2.0f; // Move box to the left
				}
				if (pos.x > b.box_pos.x) {
					pos.x = b.box_pos.x + 50;
				}
				else if (pos.x < b.box_pos.x) {
					pos.x = b.box_pos.x - 50;
				}
			}
		}
	}
}
