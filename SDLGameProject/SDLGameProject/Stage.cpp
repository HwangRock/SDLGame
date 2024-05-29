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
	//Wall
	SDL_Surface* surface_wall = IMG_Load("../Resources/sky.jpg");
	wallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_wall);
	SDL_FreeSurface(surface_wall);
	wallRect = { 0,0,680,808 };

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
	waterRect = { 113,3534,449,217 };
	milkRect = { 111,3293,453,225 };
	chocoRect = { 111,3760,449,223 };
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
	//std::cout<< "Current : "<<g_current_game_phase << "\n";
	//std::cout << "pre : " << g_pre_game_phase << "\n";
	//std::cout << "chapter : " << chapterNum << "\n";

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
		buttons[i].petOverlap(dog->pos);
		//buttons[i].petOverlap(cat->pos);

		for (int j = 0; j < buttons[i].buttonPos.size(); j++)
		{
			//std::cout << press << "\n";
			if (
				SDL_HasIntersection(&dog->pos, &buttons[i].buttonPos[j]) ||
				SDL_HasIntersection(&cat->pos, &buttons[i].buttonPos[j])
				)
			{
				//Pressing button
				//buttons[i].isStop = false;
				buttons[i].SetPress(true);
				buttons[i].Update();
				press = 1;
				break;
			}
			else if(j== buttons[i].buttonPos.size()-1)
			{
				//std::cout << "no press=" << i << "\n";
				//not pressing button 
				buttons[i].SetPress(false);
				buttons[i].Update();
			}
			else
			{
				press = 0;
			}
		}
	} 

	//FADE FLOOR///////////////////////////////////////////////////////////
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

bool StageInterface::checkOverlap(SDL_Rect a, SDL_Rect b, int depth) 
{
	if (a.x <= b.x + b.w && a.x + a.w >= b.x)
	{
		if (a.y + a.h <= b.y + b.h / 2 && a.y + a.h >= b.y + depth)
		{
			return true; // A의 아래 변이 B의 위쪽에 깊이만큼 겹침
		}
		if (a.y >= b.y + b.h / 2 && a.y <= b.y + b.h - depth)
		{
			return true; // A의 위 변이 B의 아래쪽에 깊이만큼 겹침
		}
	}
	return false;
}


void StageInterface::Render()
{
	//Background
	SDL_SetRenderDrawColor(g_renderer, 229, 221, 192, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	for (misile m : mis) {
		SDL_RenderCopy(g_renderer, manyTexture, &misileRect, &m.misile_pos);
	}

	for (Box b : boxs)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &boxRect, &b.box_pos);
	}

	for (Terrain c : cannon)
	{
		if (hit) {
			SDL_RenderCopy(g_renderer, manyTexture, &lcannonRect, &c.pos);
			Uint32 currentTime = SDL_GetTicks();
			if (currentTime % 8 == 0) {
				hit = false;
			}
		}

		else {
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
			if(press)
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

	//Dog and Cat
	if (cat->isLiquid == true)
	{
		SDL_RenderCopy(g_renderer, liquidCatTexture, &catRect, &cat->pos);
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

	//water
	for (Water water : water)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &waterRect, &water.water_pos);
	}
	//milk
	for (Milk milk : milk)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &milkRect, &milk.milk_pos);
	}
	//water
	for (Choco choco : choco)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &chocoRect, &choco.choco_pos);
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
				}
				else {//재시작버

					NextChapter(); 

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
