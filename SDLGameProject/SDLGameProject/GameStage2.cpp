#include "Game.h"
#include "GameStage2.h"
//add
#include <vector>
#include <windows.h>
#include "SDL_image.h"
#include "G2W.h"



extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern float g_timestep_s;


//InitGame
Stage2::Stage2()
{


	g_flag_running = true;


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

	//Button
	SDL_Surface* surface_button = IMG_Load("../Resources/ball.png");
	buttonTexture = SDL_CreateTextureFromSurface(g_renderer, surface_button);
	SDL_FreeSurface(surface_button);
	buttonRect = { 0,0,61,31 };


	//moust input
	mouse_win_x_ = 0;
	mouse_win_y_ = 0;

}

Stage2::~Stage2()
{
	SDL_DestroyTexture(dogTexture);
	SDL_DestroyTexture(catTexture);
}

void Stage2::Update()
{
	dog->Update(g_timestep_s, walls, buttons, blindTexture, liquidWalls, liquidAisles);
	cat->Update(g_timestep_s, walls, buttons, blindTexture, liquidWalls, liquidAisles);


}


void Stage2::Render()
{
	//Background
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color


	//Dog and Cat
	SDL_RenderCopy(g_renderer, catTexture, &catRect, &cat->pos);
	SDL_RenderCopy(g_renderer, dogTexture, &dogRect, &dog->pos);


	//Wall
	for (Terrain wall : walls)
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wall.pos);
	}


	//Button
	/*
	for (Button btn : buttons)
	{
		for (int i = 0; i < btn.buttonPos.size(); i++)
		{
			//btn
			SDL_RenderCopy(g_renderer, buttonTexture, &buttonRect, &btn.buttonPos[i]);
			//Button connected wall
			SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &btn.scaffold_[i]);
		}

	}
	*/





	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Stage2::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		dog->HandleEvent(event);
		cat->HandleEvent(event);


		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;


		case SDL_KEYDOWN:
			break;


		case SDL_KEYUP:
			break;


		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Get the cursor's x position.
				mouse_win_x_ = event.button.x;
				mouse_win_y_ = event.button.y;


				double mouse_game_x = W2G_X(mouse_win_x_);
				double mouse_game_y = W2G_Y(mouse_win_y_);


				g_current_game_phase = PHASE_STAGE3;
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
