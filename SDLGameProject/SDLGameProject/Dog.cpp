#include "Dog.h"



void Dog::Reset()
{
	Pet::Reset();

	beBlurry_ = true;
	isSkill_ = true;
	blindOpacity_ = -1;
}

void Dog::Update(
	double timestep_s,
	std::vector<Terrain>& walls,
	std::vector<Button>& buttons,
	SDL_Texture* blindTexture,
	std::vector<LiquidWall>& liquidWalls,
	std::vector<SDL_Rect>& liquidAisle,
	std::vector<ClimbWall>& climbWalls
)
{

	v[1] += gravity;
	Pet::Update(timestep_s,walls,buttons,blindTexture,liquidWalls,liquidAisle,climbWalls);

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


	//LIQUID////////////////////////////////////////////////////////////
	//same with normal walls
	for (int j = 0; j < liquidWalls.size(); j++)
	{
		if (SDL_HasIntersection(&pos, &liquidWalls[j].pos_))
		{
			BlockMoving(liquidWalls[j].pos_);
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
