#include "Game.h"
#include "Stage.h"

//
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

bool hit = false;

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
	blindTexture = SDL_CreateTextureFromSurface(g_renderer, surface_blind);
	SDL_FreeSurface(surface_blind);
	blindRect = { 0,0,269,269 };

	//Climb Wall
	SDL_Surface* surface_cwall = IMG_Load("../Resources/ending.png");
	cwallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_cwall);
	SDL_FreeSurface(surface_cwall);
	cwallRect = { 0,0,1017,1017 };

	//Goal
	SDL_Surface* surface_goal = IMG_Load("../Resources/ending.png");
	goalTexture = SDL_CreateTextureFromSurface(g_renderer, surface_goal);
	SDL_FreeSurface(surface_goal);
	goalRect = { 0,0,1017,1017 };

	//etc
	SDL_Surface* surface_sca = IMG_Load("../Resources/intro.png");
	scaffoldTexture = SDL_CreateTextureFromSurface(g_renderer, surface_sca);
	SDL_FreeSurface(surface_sca);
	scaffoldRect = { 0,0,100,100 };

	//water
	SDL_Surface* surface_water = IMG_Load("../Resources/water.png");
	waterTexture = SDL_CreateTextureFromSurface(g_renderer, surface_water);
	SDL_FreeSurface(surface_water);
	waterRect = { 0,0,300,50 };

	//milk
	SDL_Surface* surface_milk = IMG_Load("../Resources/milk.png");
	milkTexture = SDL_CreateTextureFromSurface(g_renderer, surface_milk);
	SDL_FreeSurface(surface_milk);
	milkRect = { 0,0,300,50 };

	//choco
	SDL_Surface* surface_choco = IMG_Load("../Resources/choco.png");
	chocoTexture = SDL_CreateTextureFromSurface(g_renderer, surface_choco);
	SDL_FreeSurface(surface_choco);
	chocoRect = { 0,0,300,50 };


	//Key
	SDL_Surface* surface_key = IMG_Load("../Resources/star.png");
	keyTexture = SDL_CreateTextureFromSurface(g_renderer, surface_key);
	SDL_FreeSurface(surface_key);
	keyRect = { 0,0,269,269 };

	//lock
	SDL_Surface* surface_lock = IMG_Load("../Resources/ball.png");
	lockTexture = SDL_CreateTextureFromSurface(g_renderer, surface_lock);
	SDL_FreeSurface(surface_lock);
	lockRect = { 0,0,61,61 };

	//Box
	SDL_Surface* box = IMG_Load("../Resources/many.png");
	boxTexture = SDL_CreateTextureFromSurface(g_renderer, box);
	SDL_FreeSurface(box);
	boxRect = { 156,3139, 139, 140 };
	cannonRect = { 147,2445, 179, 130 };
	lcannonRect = { 340,2436, 204, 143 };
	misileRect = { 606, 2465, 100, 53 };
	fishRect = { 171,2237,91,56 };
	boneRect = { 404,2226,86,67 };

	//restart
	SDL_Surface* rebox = IMG_Load("../Resources/restart.png");
	reTexture = SDL_CreateTextureFromSurface(g_renderer, rebox);
	SDL_FreeSurface(rebox);
	reRect = { 0,0,359,162 };
	reRect_des = { 60,30,50,50 };

	//Cushion
	SDL_Surface* surface_cushion = IMG_Load("../Resources/cushion.png");
	cushionTexture = SDL_CreateTextureFromSurface(g_renderer, surface_cushion);
	SDL_FreeSurface(surface_cushion);
	cushionRect = { 0,0,300,155 };

	//Fade floor
	SDL_Surface* surface_fwall = IMG_Load("../Resources/sky3.jpg");
	fadefloorTexture = SDL_CreateTextureFromSurface(g_renderer, surface_fwall);
	SDL_FreeSurface(surface_fwall);
	fadefloorRect = { 0,0,680,808 };

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

void StageInterface::SetVar()
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

	for (Box& b : boxs) {
		b.Update(g_timestep_s);
	}

	// 미사일 위치 업데이트
	for (auto& missile : mis) {
		missile.misile_pos.x -= 7.0f;
		for (const Terrain& wall : walls)
		{
			if (SDL_HasIntersection(&mis[0].misile_pos, &wall.pos))
			{
				missile.misile_pos = missile.initial_pos;
				hit = true;
			}
		}
	}

	if (over == 2) {
		isFirst = true;
		dog->Reset();
		cat->Reset();
		g_current_game_phase = PHASE_OVER;
	}

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
				SDL_HasIntersection(&dog->pos, &buttons[i].buttonPos[j]) ||
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

	//FADE FLOOR///////////////////////////////////////////////////////////
	for (int i = 0; i < fadefloors.size(); i++)
	{
		if (cat->isCollide == 1 || dog->isCollide == 1)
		{
			fadefloors[i].CollideFloor(true);
			fadefloors[i].Update();
		}
		else
		{
			fadefloors[i].CollideFloor(false);
			fadefloors[i].Update();
		}
	}

}


void StageInterface::Render()
{
	//Background
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	for (misile m : mis) {
		SDL_RenderCopy(g_renderer, boxTexture, &misileRect, &m.misile_pos);
	}

	for (Box b : boxs)
	{
		SDL_RenderCopy(g_renderer, boxTexture, &boxRect, &b.box_pos);
	}

	for (Terrain c : cannon)
	{
		if (hit) {
			SDL_RenderCopy(g_renderer, boxTexture, &lcannonRect, &c.pos);
			Uint32 currentTime = SDL_GetTicks();
			if (currentTime % 8 == 0) {
				hit = false;
			}
		}

		else {
			SDL_RenderCopy(g_renderer, boxTexture, &cannonRect, &c.pos);
		}
	}

	//fish
	for (Terrain f : fish) {
		SDL_RenderCopy(g_renderer, boxTexture, &fishRect, &f.pos);
	}

	//bone
	for (Terrain b : bone) {
		SDL_RenderCopy(g_renderer, boxTexture, &boneRect, &b.pos);
	}

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
	for (SDL_Rect g : goal)
	{
		SDL_RenderCopy(g_renderer, goalTexture, &goalRect, &g);
	}
	SDL_RenderCopy(g_renderer, goalTexture, &goalRect, &start);

	//Key and Lock
	for (Key key : keys)
	{
		if (key.isLocked == true)
		{
			SDL_RenderCopy(g_renderer, lockTexture, &lockRect, &key.lockPos);
		}
		if (key.isCollected == false)
		{
			SDL_RenderCopy(g_renderer, keyTexture, &keyRect, &key.keyPos);
		}
	}

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

	//fadefloor
	for (FadeFloor fwall : fadefloors)
	{
		SDL_RenderCopy(g_renderer, fadefloorTexture, &fadefloorRect, &fwall.floor_pos);
	}

	//climbWall
	for (ClimbWall wall : climbWalls)
	{
		SDL_RenderCopy(g_renderer, cwallTexture, &cwallRect, &wall.wall_pos);
	}

	//cushion
	for (Cushion cushion : cushions)
	{
		SDL_RenderCopy(g_renderer, cushionTexture, &cushionRect, &cushion.cushion_pos);
	}

	//water
	for (Water water : water)
	{
		SDL_RenderCopy(g_renderer, waterTexture, &waterRect, &water.water_pos);
	}
	//milk
	for (Milk milk : milk)
	{
		SDL_RenderCopy(g_renderer, milkTexture, &milkRect, &milk.milk_pos);
	}
	//water
	for (Choco choco : choco)
	{
		SDL_RenderCopy(g_renderer, chocoTexture, &chocoRect, &choco.choco_pos);
	}

	//restart
	SDL_RenderCopy(g_renderer, reTexture, &reRect, &reRect_des);

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
		g_current_game_phase = PHASE_FINISH;
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
				//game over test
				isFirst = true;
				dog->Reset();
				cat->Reset();
				g_current_game_phase = PHASE_OVER;
			}

			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				dog->resetInputs();
				cat->resetInputs();
				g_current_game_phase = PHASE_ESC;
			}
			break;

		case SDL_KEYUP:
			break;


		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (g_current_game_phase == PHASE_CLEAR) {
					// Get the cursor's x position.
					mouse_win_x_ = event.button.x;
					mouse_win_y_ = event.button.y;
					//NextChapter(); <-- 원래 여기에 있던 것을
				}
				else {//재시작버

					NextChapter(); //<-- 여기로 임시로 옮겨서 오브젝트 배치가 잘되었는지 확인했어요

				}

			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				int x, y;
				x = event.button.x;
				y = event.button.y;
				if (x >= 60 and x <= 110 and y >= 30 and y <= 80) {
					isFirst = true;
					dog->Reset();
					cat->Reset();
				}
			}

			break;

		default:
			break;
		}
	}
}
