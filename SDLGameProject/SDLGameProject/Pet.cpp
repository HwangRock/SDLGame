#include "Pet.h"
#include "SDL_image.h"
#include <iostream>


Pet::Pet(double x, double y,bool isDog)
{
	size_ = 30;

	isDog_ = isDog;

	mass_ = 2; // 2kg
	coeff_of_restitution_ = 0.7;

	pos_[0] = x;
	pos_[1] = y;

	pos.x = x;
	pos.y = y;
	pos.w = 30;
	pos.h = 30;


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
	
	beBlurry_ = true;
	isSkill_ = true;
	blindOpacity_ = -1;
	
	isPressing = -1;
}


void
Pet::Update(
	double timestep_s, 
	std::vector<Terrain>& walls,
	std::vector<Button>&buttons,
	SDL_Texture *blindTexture,
	std::vector<SDL_Rect>&liquidWalls,
	std::vector<SDL_Rect>& liquidAisle
)
{
	double dt = timestep_s;	// seconds


	//MOVING/////////////////////////////////////////////////

	v[1] += gravity;

	nowInput = inputs[inputs.size() - 1];
	//left
	if (nowInput == 1) { pos.x -= 2; }
	//right
	else if (nowInput == 2) { pos.x += 2; }
	//up
	pos.y += v[1];




	//MOVING LIMIT//////////////////////////////////////////////////
	// 벽 감지
	for (const Terrain& wall : walls)
	{
		if (SDL_HasIntersection(&pos, &wall.pos))
		{
			//주의) 벽의 height가 너무 작으면 제대로 작동하지 않을 것 같습니다..
			BlockMoving(wall.pos);

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
			}
		}
		

		for (int j = 0; j < buttons[i].buttonPos.size(); j++)
		{
			if (SDL_HasIntersection(&pos, &buttons[i].buttonPos[j]))
			{
				//Pressing button
				std::cout << "press\n";
				isPressing = i;
				break;
			}
			else
			{
				//Not pressing button
				isPressing = -1;
			}
		}


	}
	
		
	//SNIFF////////////////////////////////////////////////////////////
	if (isDog_ == true && blindOpacity_ != -1)
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
		
	//LIQUID////////////////////////////////////////////////////////////
	if (isDog_ == true)
	{
		//same with normal walls
		for (int j = 0; j < liquidWalls.size(); j++)
		{
			if (SDL_HasIntersection(&pos, &liquidWalls[j]))
			{
				BlockMoving(liquidWalls[j]);
			}
		}
		for (int j = 0; j < liquidAisle.size(); j++)
		{
			if (SDL_HasIntersection(&pos, &liquidAisle[j]))
			{
				BlockMoving(liquidAisle[j]);
			}
		}
	}
	else
	{
		//CAT LIQUID SKILL

		//sprite change

		//skill
		for (int j = 0; j < liquidWalls.size(); j++)
		{
			if (SDL_HasIntersection(&pos, &liquidWalls[j]))
			{
				SDL_Rect newWall;

				if (liquidWalls[j].w > liquidWalls[j].h)
				{
					//floor
					newWall.x = liquidWalls[j].x;
					newWall.y = liquidWalls[j].y + liquidWalls[j].h / 4;
					newWall.w = liquidWalls[j].w;
					newWall.h = liquidWalls[j].h / 2;

				}
				else
				{
					//wall
					newWall.x = liquidWalls[j].x+ liquidWalls[j].w/4;
					newWall.y = liquidWalls[j].y;
					newWall.w = liquidWalls[j].w/2;
					newWall.h = liquidWalls[j].h;
				}
				BlockMoving(newWall);
			}
		}

	}





	/*
	// 가속도
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
	if (pos.y + pos.h > obst.y + 6 &&
		pos.y < obst.y + obst.h - 6)
	{
		//벽왼쪽에 있음
		if (pos.x < obst.x + obst.w / 2)
		{
			//pos.x = min(pos.x, obst.x - pos.w);
			pos.x = obst.x - pos.w;
		}
		//벽 오른쪽에 있음
		else if (pos.x + pos.w > obst.x)
		{
			//pos.x = max(pos.x, obst.x + obst.w);
			pos.x = obst.x + obst.w;
		}

	}
	else
	{
		if (pos.y + pos.h <= obst.y + obst.h / 2)
		{
			// 벽 위에 있음
			pos.y = std::min(obst.y - pos.h,pos.y);
			v[1] = 0;
			jumping = false;
		}
		else
		{
			// 벽 아래에 있음
			//pos.y = obst.y + obst.h;
			pos.y = std::max(obst.y + obst.h, pos.y);
		}
	}
}

void
Pet::HandleEvent(SDL_Event event) 
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (isDog_)
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
					jumping = true;
				}
			}
			else if (event.key.keysym.sym == SDLK_RSHIFT)
			{
				if (isSkill_ == true)
				{
					//Use Sniffing Skill
					blindOpacity_ = 254;
					isSkill_ = false;
				}
			}
		}
		else
		{
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
				keyDownNum = 3;
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

		if (isDog_)
		{
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
		}
		else
		{
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
