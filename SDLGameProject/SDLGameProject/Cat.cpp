#include "Cat.h"


void Cat::Reset()
{
	Pet::Reset();
	isLiquid = false;
}

void Cat::Update(
	double timestep_s,
	std::vector<Terrain>& walls,
	std::vector<Button>& buttons,
	SDL_Texture* blindTexture,
	std::vector<LiquidWall>& liquidWalls,
	std::vector<SDL_Rect>& liquidAisle
)
{
	Pet::Update(timestep_s, walls, buttons, blindTexture, liquidWalls, liquidAisle);
	



	//CAT LIQUID SKILL/////////////////////////////////////////

	//sprite change

	//skill
	for (int j = 0; j < liquidWalls.size(); j++)
	{
		if (SDL_HasIntersection(&pos, &liquidWalls[j].pos_))
		{
			isLiquid = true;

			SDL_Rect newWall;
			newWall = liquidWalls[j].returnWall();
			BlockMoving(newWall);
		}
		else 
		{
			if (j == liquidWalls.size() - 1)
			{
				isLiquid = false;
			}
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
