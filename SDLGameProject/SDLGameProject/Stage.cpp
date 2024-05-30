#include "Game.h"
#include "Stage.h"
#include <vector>
#include <windows.h>
#include "SDL_image.h"


extern int g_current_game_phase;
extern int g_pre_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern float g_timestep_s;


//변경법
bool hit = false;


//InitGame
StageInterface::StageInterface()
{
	g_flag_running = true;

	//Window
	SDL_GetWindowSize(g_window, &win_w, &win_h);


	//Drawing Texture//////////////////////////////////////////////////////////////////
	//Wall
	SDL_Surface* surface_wall = IMG_Load("../Resources/sky.jpg");
	wallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_wall);
	SDL_FreeSurface(surface_wall);
	wallRect = { 0,0,680,808 };

	//Liquid
	SDL_Surface* surface_l = IMG_Load("../Resources/liquid.png");
	liquidTexture = SDL_CreateTextureFromSurface(g_renderer, surface_l);
	SDL_FreeSurface(surface_l);
	milkR = { 0,0,200,200 };
	chocoR = { 200,0,200,200 };
	waterR = { 400,0,200,200 };

	

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

	//etc
	SDL_Surface* surface_sca = IMG_Load("../Resources/intro.png");
	scaffoldTexture = SDL_CreateTextureFromSurface(g_renderer, surface_sca);
	SDL_FreeSurface(surface_sca);
	scaffoldRect = { 0,0,100,100 };

	//Texture
	SDL_Surface* texture = IMG_Load("../Resources/many.png");
	manyTexture = SDL_CreateTextureFromSurface(g_renderer, texture);
	SDL_FreeSurface(texture);
	boxRect = { 156,3139, 139, 140 };
	cannonRect = { 147,2445, 179, 130 };
	lcannonRect = { 340,2436, 204, 143 };
	misileRect = { 606, 2465, 100, 53 };
	fishRect = { 171,2237,91,56 };
	boneRect = { 404,2226,86,67 };
	buttonRect = { 632,2267,103,109 };
	goalRect = { 152,2850,154,207 };

	keyRect = { 1532,2213,83,110};
	lockRect = { 1774,2222,60,80 };
	cushionRect = { 1049,2301,160,76 };
	fadefloorRect = { 1923,2222,215,90 };
	dogRect = { 150,1010,153,193 };
	catRect = { 145,75,167,215 };
	PushbuttonRect = { 855,2305,112,69 };
	PushcushionRect = { 1277,2314,156,68 };
	dogPushRect = { 119,1941,132,179 };
	catDieRect = { 580,770,187,222 };
	dogDieRect = { 342,1537,218,144 };

	//restart
	SDL_Surface* rebox = IMG_Load("../Resources/restart.png");
	reTexture = SDL_CreateTextureFromSurface(g_renderer, rebox);
	SDL_FreeSurface(rebox);
	reRect = { 0,0,359,162 };
	reRect_des = { 60,30,50,50 };


	////////////////////////////////////////////////////////////////////////////////////////

	mouse_win_x_ = 0;
	mouse_win_y_ = 0;

	isFirst = true;
}

StageInterface::~StageInterface()
{

	SDL_DestroyTexture(cwallTexture);
	SDL_DestroyTexture(goalTexture);
	SDL_DestroyTexture(scaffoldTexture);
	SDL_DestroyTexture(manyTexture);
	SDL_DestroyTexture(liquidTexture);

	SDL_DestroyTexture(reTexture);

	

}

void StageInterface::SetVar()
{

}
void StageInterface::Reset()
{
	dog->Reset();
	cat->Reset();

	score_bone = 0;
	score_fish = 0;
	gameOverDelay = 150;

	dog->pos.x = start.x;
	dog->pos.y = start.y;
	cat->pos.x = start.x;
	cat->pos.y = start.y;

}
void StageInterface::Update()
{
	//재시작시 실행. reset.
	if (isFirst == true)
	{
		SetVar();
		Reset();
		isFirst = false;
	}


	
	//Reach the Goal//////////////////////////////////////////
	if (cat->isInGoal == true && dog->isInGoal == true)
	{
		isFirst = true;
		dog->Reset();
		cat->Reset();
		g_current_game_phase = PHASE_CLEAR;
	}
	//GameOver////////////////////////////////////////////////한마리라도 죽으면 게임 끝
	if (dog->isDead == true || cat->isDead == true)
	{
		gameOverDelay--;
		if (gameOverDelay <= 0)
		{
			isFirst = true;
			dog->Reset();
			cat->Reset();
			g_current_game_phase = PHASE_OVER;
		}
	}
	else
	{

		//dog, cat
		dog->Update(g_timestep_s);
		cat->Update(g_timestep_s);

		//box
		for (Box& b : boxs) {
			b.Update(g_timestep_s);
		}

		// 미사일 위치 업데이트
		for (auto& missile : mis)
		{
			missile.misile_pos.x -= 7.0f;

			//이거 함수로 줄일 수 없을까--------------------------------------------------------
			for (const Terrain& wall : walls)
			{
				if (SDL_HasIntersection(&mis[0].misile_pos, &wall.pos))
				{
					missile.misile_pos = missile.initial_pos;
					hit = true;
					break;
				}
			}
			for (const Box& b : boxs)
			{
				if (SDL_HasIntersection(&mis[0].misile_pos, &b.box_pos))
				{
					missile.misile_pos = missile.initial_pos;
					hit = true;
					break;
				}
			}
			for (const Button& btn : buttons)
			{
				for (int k = 0; k < btn.scaffold_.size(); k++)
				{
					if (SDL_HasIntersection(&mis[0].misile_pos, &btn.scaffold_[k]))
					{
						missile.misile_pos = missile.initial_pos;
						hit = true;
						break;
					}
				}
			}
		}




		


		//PRESS BUTTON/////////////////////////////////////////////////////////////
		for (int i = 0; i < buttons.size(); i++)
		{
			//튕기는거 방지
			buttons[i].petOverlap(dog->pos);
			buttons[i].petOverlap(cat->pos);


			//버튼 누르는지 검사
			for (int j = 0; j < buttons[i].buttonPos.size(); j++)
			{
				if (SDL_HasIntersection(&dog->pos, &buttons[i].buttonPos[j]) ||
					SDL_HasIntersection(&cat->pos, &buttons[i].buttonPos[j]))
				{
					//Pressing button
					//buttons[i].isStop = false;
					buttons[i].SetPress(true);
					buttons[i].Update();
					break;
				}
				else if (j == buttons[i].buttonPos.size() - 1)
				{
					//not pressing button 
					buttons[i].SetPress(false);
					buttons[i].Update();
				}

			}
		}

		//FADE FLOOR///////////////////////////////////////////////////////////
		//---------------------------------------------------------------------------------------------------------------------------
		if (!fadefloors.empty())
		{
			if (cat->isCollide == 1 || dog->isCollide == 1)
			{
				switch (fadefloorNum)
				{
				case 0:
					fadefloors[0].CollideFloor(true);
					fadefloors[0].Update();
					break;
				case 1:
					fadefloors[1].CollideFloor(true);
					fadefloors[1].Update();
					break;
				case 2:
					fadefloors[2].CollideFloor(true);
					fadefloors[2].Update();
					break;
				case 3:
					fadefloors[3].CollideFloor(true);
					fadefloors[3].Update();
					break;
				case 4:
					fadefloors[4].CollideFloor(true);
					fadefloors[4].Update();
					break;
				case 5:
					fadefloors[5].CollideFloor(true);
					fadefloors[5].Update();
					break;
				default:
					break;
				}

			}
		}
	}

}




void StageInterface::Render()
{
	//Background
	SDL_SetRenderDrawColor(g_renderer, 229, 221, 192, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color


	//MISSILE
	for (misile m : mis) {
		SDL_RenderCopy(g_renderer, manyTexture, &misileRect, &m.misile_pos);
	}

	//BOX
	for (Box b : boxs)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &boxRect, &b.box_pos);
	}

	//CANNON
	for (Terrain c : cannon)
	{
		if (hit) {
			SDL_RenderCopy(g_renderer, manyTexture, &lcannonRect, &c.pos);
			Uint32 currentTime = SDL_GetTicks();
			if (currentTime % 8 == 0) {	hit = false;}
		}
		else 
		{
			SDL_RenderCopy(g_renderer, manyTexture, &cannonRect, &c.pos);
		}
	}


	//fish
	for (Terrain f : fish) {
		SDL_RenderCopy(g_renderer, manyTexture, &fishRect, &f.pos);
	}

	//bone
	for (Terrain b : bone) {
		SDL_RenderCopy(g_renderer, manyTexture, &boneRect, &b.pos);
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
			if(btn.isPressed)
			{
				SDL_RenderCopy(g_renderer, manyTexture, &PushbuttonRect, &btn.buttonPos[i]);
			}
			else
			{
				SDL_RenderCopy(g_renderer, manyTexture, &buttonRect, &btn.buttonPos[i]);
			}

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
		SDL_RenderCopy(g_renderer, manyTexture, &goalRect, &g);
	}
	SDL_RenderCopy(g_renderer, manyTexture, &goalRect, &start);


	//Key and Lock
	for (Key key : keys)
	{
		if (key.isLocked == true)
		{
			SDL_RenderCopy(g_renderer, manyTexture, &lockRect, &key.lockPos);
		}
		if (key.isCollected == false)
		{
			SDL_RenderCopy(g_renderer, manyTexture, &keyRect, &key.keyPos);
		}
	}

	//Cat
	if (cat->isDead == true)
	{
		SDL_RenderCopy(g_renderer, liquidTexture, &waterR, &cat->pos);//일단 임시로 물로 해놓음
	}
	else
	{
		if (cat->isLiquid == true)
		{
			SDL_RenderCopy(g_renderer, manyTexture, &catRect, &cat->pos);//--------------------------------------------------------------------------
		}
		else
		{
			// left
			if (cat->nowInput == 1 || cat->nowInput == 0)
			{
				SDL_RenderCopy(g_renderer, manyTexture, &catRect, &cat->pos);
			}
			// right
			else if (cat->nowInput == 2)
			{
				SDL_RenderCopyEx(g_renderer, manyTexture, &catRect, &cat->pos, 0, NULL, SDL_FLIP_HORIZONTAL);
			}
		}
	}

	//Dog
	if (dog->isDead == true)
	{
		SDL_RenderCopy(g_renderer, liquidTexture, &milkR, &dog->pos);//일단 임시로 우유로 해놓음
	}
	else
	{
		if (dog->box_collide == true)
		{
			SDL_RenderCopy(g_renderer, manyTexture, &dogPushRect, &dog->pos);
		}
		else
		{
			// left
			if (dog->nowInput == 1 || dog->nowInput == 0)
			{
				SDL_RenderCopy(g_renderer, manyTexture, &dogRect, &dog->pos);
			}
			// right
			else if (dog->nowInput == 2)
			{
				SDL_RenderCopyEx(g_renderer, manyTexture, &dogRect, &dog->pos, 0, NULL, SDL_FLIP_HORIZONTAL);
			}
		}
	}







	//Blind
	for (SDL_Rect bln : blinds)
	{
		SDL_SetTextureBlendMode(blindTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(blindTexture, dog->blindOpacity_);
		SDL_RenderCopy(g_renderer, blindTexture, &blindRect, &bln);

	}

	//climbWall
	for (ClimbWall wall : climbWalls)
	{
		SDL_RenderCopy(g_renderer, cwallTexture, &cwallRect, &wall.wall_pos);
	}

	//cushion
	for (Cushion cushion : cushions)
	{
		if(c_collide)
		{
			SDL_RenderCopy(g_renderer, manyTexture, &PushcushionRect, &cushion.cushion_pos);
		}
		else
		{
			SDL_RenderCopy(g_renderer, manyTexture, &cushionRect, &cushion.cushion_pos);
		}
	}

	

	//liquid
	for (Liquid l : liquid)
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &l.wallPos);
		if (l.liquidClass == "water") { SDL_RenderCopy(g_renderer, liquidTexture, &waterR, &l.liquidPos); }
		else if (l.liquidClass == "choco") { SDL_RenderCopy(g_renderer, liquidTexture, &chocoR, &l.liquidPos); }
		else if (l.liquidClass == "milk") { SDL_RenderCopy(g_renderer, liquidTexture, &milkR, &l.liquidPos); }
		else { std::cout << "there is no such liquid class\n"; }
	}


	//fadefloor
	for (FadeFloor fwall : fadefloors)
	{
		SDL_SetTextureBlendMode(manyTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(manyTexture, fwall.alpha);
		SDL_RenderCopy(g_renderer, manyTexture, &fadefloorRect, &fwall.floor_pos);
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
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				dog->resetInputs();
				cat->resetInputs();
				g_current_game_phase = PHASE_ESC;
			}
			else if (event.key.keysym.sym == SDLK_0)
			{
				NextChapter();
			}
			break;

		case SDL_KEYUP:
			break;


		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (g_current_game_phase == PHASE_CLEAR) {
					mouse_win_x_ = event.button.x;
					mouse_win_y_ = event.button.y;
				}
			}
			else if (event.button.button == SDL_BUTTON_LEFT) {
				//RESTART BUTTON
				int x, y;
				x = event.button.x;
				y = event.button.y;

				if (x >= 60 and x <= 110 and y >= 30 and y <= 80) 
				{
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
