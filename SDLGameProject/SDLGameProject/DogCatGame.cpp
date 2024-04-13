#include <iostream>
#include<vector>
#include <windows.h>

#include "DogCatGame.h" 
#include "SDL_image.h"
#include "G2W.h"
#include "math.h"

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern float g_timestep_s;






Terrain wall1(300, 100, 20, 100);
Terrain wall2(50, 100, 20, 100);
Terrain wall3(400, 200, 20, 500);
Terrain wall4(100, 300, 600, 200);
std::vector<Terrain>walls = { wall1,wall2,wall3,wall4 };





//InitGame
DogCatGame::DogCatGame()
{
	g_flag_running = true;


	//Input
	catInput = 0;
	dogInput = 0;
	catKeyDown = 0;
	dogKeyDown = 0;
	catKeyUp = 0;
	dogKeyUp = 0;

	cat_input.push_back(0);
	dog_input.push_back(0);


	//Window
	SDL_GetWindowSize(g_window, &win_w, &win_h);



	//Drawing Texture//////////////////////////////
	//Dog
	SDL_Surface* g_surface_dog = IMG_Load("../Resources/dog_.png");
	dogTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_dog);
	SDL_FreeSurface(g_surface_dog);
	dogRect = { 0,0,141,141 };

	//Cat
	SDL_Surface* g_surface_cat = IMG_Load("../Resources/cat_.png");
	catTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_cat);
	SDL_FreeSurface(g_surface_cat);
	catRect = { 0,0,90,90 };

	//Wall
	SDL_Surface* surface_wall = IMG_Load("../Resources/sky.jpg");
	wallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_wall);
	SDL_FreeSurface(surface_wall);
	wallRect = { 0,0,680,808 };



	
	mouse_win_x_ = 0;
	mouse_win_y_ = 0;

}



//EndGame
DogCatGame::~DogCatGame()
{
	SDL_DestroyTexture(dogTexture);
	SDL_DestroyTexture(catTexture);
}



void
DogCatGame::Update()
{
	dog->v[1] += gravity;
	cat->v[1] += gravity;

	//DOG MOVING

	
	dogInput = dog_input[dog_input.size() - 1];
	//left
	if (dogInput == 1) { dog->pos.x -= 5; }
	//right
	else if (dogInput == 2) { dog->pos.x += 5; }
	//up
	//else if (dogInput == 3) { dog->pos.y -= 5; }
	
	dog->pos.y += dog->v[1];



	//CAT MOVING
	
	catInput = cat_input[cat_input.size() - 1];
	//left
	if (catInput == 1) { cat->pos.x -= 5; }
	//right
	else if (catInput == 2) { cat->pos.x += 5; }
	//up
	//else if (catInput == 3) { cat->pos.y -= 5; }
	cat->pos.y += cat->v[1];
	


	dog->Update(g_timestep_s,walls);
	cat->Update(g_timestep_s,walls);
}



void
DogCatGame::Render()
{
	//Background
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	
	//Dog and Cat
	SDL_RenderCopy(g_renderer, catTexture, &catRect, &cat->pos);
	SDL_RenderCopy(g_renderer, dogTexture, &dogRect, &dog->pos);


	//Wall
	for(Terrain wall : walls)
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wall.pos);
	}




	SDL_RenderPresent(g_renderer); // draw to the screen
}



void DogCatGame::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;




		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT)
			{	
				dogKeyDown = 1;
				dog->v[0] = -1.0f;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{ 
				dogKeyDown = 2;
				dog->v[0] = 1.0f;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{ 
				if (dog->jumping == false)
				{
					//dogKeyDown = 3;
					dog->v[1] = dog->jumpSpeed();
					dog->jumping = true;
				}
			}

			if (dogKeyDown != 0)
			{
				for (int i = dog_input.size() - 1; i >= 0; i--)
				{
					if (dog_input[i] != dogKeyDown && dogKeyDown != 0)
					{
						if (i == 0) { dog_input.push_back(dogKeyDown); }
					}
					else { break; }
				}
				dogKeyDown = 0;
			}

			if (event.key.keysym.sym == SDLK_a)
			{ cat->v[0] = -1.0f; catKeyDown = 1;	}
			else if (event.key.keysym.sym == SDLK_d)
			{ cat->v[0] = 1.0f; catKeyDown = 2;	}
			else if (event.key.keysym.sym == SDLK_w)
			{	
				if (cat->jumping == false)
				{
					//catKeyDown = 3;
					cat->v[1] = cat->jumpSpeed();
					cat->jumping = true;
				}
				catKeyDown = 3;	
			}

			if (catKeyDown != 0)
			{
				for (int i = cat_input.size() - 1; i >= 0; i--)
				{
					if (cat_input[i] != catKeyDown && catKeyDown != 0)
					{
						if (i == 0) { cat_input.push_back(catKeyDown); }
					}
					else { break; }
				}
				catKeyDown = 0;
			}
			break;








		case SDL_KEYUP:
			
			

			if (event.key.keysym.sym == SDLK_LEFT)
			{
				dogKeyUp = 1;	
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				dogKeyUp = 2;	
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{	
				//dogKeyUp = 3;	
			}

			if (dogKeyUp != 0)
			{
				for (int i = dog_input.size() - 1; i >= 0; i--)
				{
					if (dog_input[i] == dogKeyUp)
					{
						//dog->v[0] = 0.0f;
						dog_input.erase(dog_input.begin() + i);
						dogKeyUp = 0;
						break;
					}

				}
			}


			if (event.key.keysym.sym == SDLK_a)
			{ catKeyUp = 1;	}
			else if (event.key.keysym.sym == SDLK_d)
			{  catKeyUp = 2;	}
			else if (event.key.keysym.sym == SDLK_w)
			{ 
				//catKeyUp = 3;	
			}

			if (catKeyUp != 0)
			{
				for (int i = cat_input.size() - 1; i >= 0; i--)
				{
					if (cat_input[i] == catKeyUp)
					{
						//cat->v[0] = 0.0f;
						cat_input.erase(cat_input.begin() + i);
						catKeyUp = 0;
						break;
					}

				}
			}

			break;
		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Get the cursor's x position.
				mouse_win_x_ = event.button.x;
				mouse_win_y_ = event.button.y;


				double mouse_game_x = W2G_X(mouse_win_x_);
				double mouse_game_y = W2G_Y(mouse_win_y_);

			}



		case SDL_MOUSEMOTION:
		{
			// Get the cursor's x position.
			mouse_win_x_ = event.button.x;
			mouse_win_y_ = event.button.y;
		}
		break;

		default:
			break;
		}
	}
}

