#include "Game.h"
#include "Stage.h"


//add
#include <vector>
#include <windows.h>

#include "SDL_image.h"



extern int g_current_game_phase;
extern int g_pre_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern float g_timestep_s;


//InitGame
StageInterface::StageInterface()
{
	g_flag_running = true;


	//Window
	SDL_GetWindowSize(g_window, &win_w, &win_h);



	//Drawing Texture//////////////////////////////////////////////////////////////////
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

	//Liquid Cat
	SDL_Surface* g_surface_liquidCat = IMG_Load("../Resources/liquidCat.png");
	liquidCatTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_liquidCat);
	SDL_FreeSurface(g_surface_liquidCat);


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
	
	//Blind
	SDL_Surface* surface_blind = IMG_Load("../Resources/star.png");
	SDL_SetSurfaceBlendMode(surface_blind, SDL_BLENDMODE_BLEND);
	blindTexture= SDL_CreateTextureFromSurface(g_renderer, surface_blind);
	SDL_FreeSurface(surface_blind);
	blindRect = { 0,0,269,269 };


	//Climb Wall
	SDL_Surface* surface_cwall = IMG_Load("../Resources/ending.png");
	cwallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_cwall);
	SDL_FreeSurface(surface_cwall);
	cwallRect = { 0,0,1017,1017};

	//Goal
	SDL_Surface* surface_goal = IMG_Load("../Resources/ending.png");
	goalTexture = SDL_CreateTextureFromSurface(g_renderer, surface_goal);
	SDL_FreeSurface(surface_goal);
	goalRect = { 0,0,1017,1017 };

	//etc
	SDL_Surface* surface_sca = IMG_Load("../Resources/intro.png");
	scaffoldTexture= SDL_CreateTextureFromSurface(g_renderer, surface_sca);
	SDL_FreeSurface(surface_sca);
	scaffoldRect = { 0,0,100,100 };

	////////////////////////////////////////////////////////////////////////////////////////

	mouse_win_x_ = 0;
	mouse_win_y_ = 0;

	isFirst = true;
}

StageInterface::~StageInterface()
{
	SDL_DestroyTexture(dogTexture);
	SDL_DestroyTexture(catTexture);
}

void StageInterface:: SetVar() 
{

}
void StageInterface::Reset()
{
	

	dog->pos.x = start.x;
	dog->pos.y = start.y;
	cat->pos.x = start.x;
	cat->pos.y = start.y;

}
void StageInterface::Update()
{
	if (isFirst == true)
	{
		SetVar();
		Reset();
		isFirst = false;
	} 

	dog->Update(g_timestep_s);
	cat->Update(g_timestep_s);


	//Reach the Goal//////////////////////////////////////////
	if (cat->isInGoal == true && dog->isInGoal == true)
	{
		//if all of them reach the goal, go to next chapter
		isFirst = true;
		dog->Reset();
		cat->Reset();
		g_current_game_phase = PHASE_CLEAR;

	}


	//PRESS BUTTON/////////////////////////////////////////////////////////////
	for (int i = 0; i < buttons.size(); i++)
	{
		for (int j = 0; j < buttons[i].buttonPos.size(); j++)
		{
			if (
				SDL_HasIntersection(&dog->pos, &buttons[i].buttonPos[j])||
				SDL_HasIntersection(&cat->pos, &buttons[i].buttonPos[j])
				)
			{
				//std::cout <<"press=" << i << "\n";
				//Pressing button
				buttons[i].SetPress(true);
				buttons[i].Update();
				break;
			}
			else 
			{
				//std::cout << "no press=" << i << "\n";
				//not pressing button 
				buttons[i].SetPress(false);
				buttons[i].Update();
			}
		}
	}


	
}


void StageInterface::Render()
{
	//Background
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color


	

	//Wall
	for (Terrain wall : walls)
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wall.pos);
	}
	//LiquidWall
	for (LiquidWall wall : liquidWalls)
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wall.pos_);
	}


	//Button
	for (Button btn : buttons)
	{
		for (int i = 0; i < btn.buttonPos.size(); i++)
		{
			//btn
			SDL_RenderCopy(g_renderer, buttonTexture, &buttonRect, &btn.buttonPos[i]);
		}
		for (int i = 0; i < btn.scaffold_.size(); i++)
		{
			//Button connected scaffolds
			SDL_RenderCopy(g_renderer, scaffoldTexture, &scaffoldRect, &btn.scaffold_[i]);
		}
		
	}

	//Goal,Start
	SDL_RenderCopy(g_renderer, goalTexture, &goalRect, &goal);
	SDL_RenderCopy(g_renderer, goalTexture, &goalRect, &start);


	//Dog and Cat
	if (cat->isLiquid == true)
	{
		SDL_RenderCopy(g_renderer, liquidCatTexture, &catRect, &cat->pos);
	}
	else
	{
		SDL_RenderCopy(g_renderer, catTexture, &catRect, &cat->pos);
	}
	SDL_RenderCopy(g_renderer, dogTexture, &dogRect, &dog->pos);



	//Blind
	for (SDL_Rect bln : blinds)
	{
		SDL_RenderCopy(g_renderer, blindTexture, &blindRect, &bln);

	}

	//climbWall
	for (ClimbWall wall : climbWalls)
	{
		SDL_RenderCopy(g_renderer, cwallTexture, &cwallRect, &wall.wall_pos);
	}

	


	SDL_RenderPresent(g_renderer); // draw to the screen
}

void StageInterface::NextChapter()
{
	isFirst = true;
	dog->Reset();
	cat->Reset();

	switch (chapterNum)
	{
	case 0:
		chapterNum = 1;
		g_current_game_phase = PHASE_STAGE2;
		g_pre_game_phase = PHASE_STAGE2;
		break;
	case 1:
		chapterNum = 2;
		g_current_game_phase = PHASE_STAGE3;
		g_pre_game_phase = PHASE_STAGE3;
		break;
	case 2:
		chapterNum = 3;
		g_current_game_phase = PHASE_STAGE4;
		g_pre_game_phase = PHASE_STAGE4;
		break;
	case 3:
		chapterNum = 0;
		g_current_game_phase = PHASE_ENDING;
		g_pre_game_phase = PHASE_STAGE1;
		break;
	default:
		break;
	}
}



void StageInterface::HandleEvents()
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
			if (event.key.keysym.sym == SDLK_g)
			{
				//Game Over 테스트용. 임의로 g키를 누르면 바로 gameOver된다.
				isFirst = true;
				dog->Reset(); 
				cat->Reset();
				g_current_game_phase = PHASE_OVER;
			}
			break;
			
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_current_game_phase = PHASE_ESC;
			}
			break;

		case SDL_KEYUP:
			break;


		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Get the cursor's x position.
				mouse_win_x_ = event.button.x;
				mouse_win_y_ = event.button.y;

				NextChapter();
				
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
