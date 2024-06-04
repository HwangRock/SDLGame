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


int g_elapsed_time;
int cat_v = -1; // left : -1 , right : 1
int dog_v = -1;

//InitGame
StageInterface::StageInterface()
{
	g_flag_running = true;

	//Window
	SDL_GetWindowSize(g_window, &win_w, &win_h);


	//Drawing Texture//////////////////////////////////////////////////////////////////
	 
	//bg image
	SDL_Surface* surface_bg = IMG_Load("../Resources/mapbg.png");
	mapbg = SDL_CreateTextureFromSurface(g_renderer, surface_bg);
	SDL_FreeSurface(surface_bg);

	mapSrect[0] = {0, 0, 2944, 1632};
	mapSrect[1] = {0, 1632, 2944, 1632};
	mapSrect[2] = { 0, 3264, 2944, 1632 };

	mapDrect = {0, 0, 1280, 720};
	
	//Wall
	SDL_Surface* surface_wall = IMG_Load("../Resources/many.png");
	wallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_wall);
	SDL_FreeSurface(surface_wall); 
	//wallRect = { 0,0,680,808 }; sky.jpg일 때
	wallRect = {1028, 3313, 200, 197};

	//Liquid
	SDL_Surface* surface_l = IMG_Load("../Resources/liquid.png");
	liquidTexture = SDL_CreateTextureFromSurface(g_renderer, surface_l);
	SDL_FreeSurface(surface_l);
	milkR = { 0,0,200,200 };
	chocoR = { 200,0,200,200 };
	waterR = { 400,0,200,200 };

	//Pictures
	SDL_Surface* surface_pic = IMG_Load("../Resources/pictures.png");
	SDL_SetSurfaceBlendMode(surface_pic, SDL_BLENDMODE_BLEND);
	picturesTexture = SDL_CreateTextureFromSurface(g_renderer, surface_pic);
	SDL_FreeSurface(surface_pic);
	picturesRect.push_back({ 0,3,147,94 });
	picturesRect.push_back({ 176,0,249-176,104 });
	picturesRect.push_back({ 268,0,455-268,108 });
	picturesRect.push_back({ 0,138,169,212-138 });
	picturesRect.push_back({ 188,139,263-188,211-139 });
	picturesRect.push_back({ 289,124,401-289,210-124 });
	
	SDL_Surface* surface_curtain = IMG_Load("../Resources/curtain.png");
	curtainTexture = SDL_CreateTextureFromSurface(g_renderer, surface_curtain);
	SDL_FreeSurface(surface_curtain);
	picturesRect.push_back({ 0,0,250,240 });
	picturesRect.push_back({ 287,76,603-287,240-76 });



	//Climb Wall
	SDL_Surface* surface_cwall = IMG_Load("../Resources/scratch.jpg");
	cwallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_cwall);
	SDL_FreeSurface(surface_cwall);
	cwallRect = { 279,398,204, 909 };

	//Goal
	SDL_Surface* surface_goal = IMG_Load("../Resources/ending.png");
	goalTexture = SDL_CreateTextureFromSurface(g_renderer, surface_goal);
	SDL_FreeSurface(surface_goal);

	//etc
	SDL_Surface* surface_sca = IMG_Load("../Resources/many_2.png");
	scaffoldTexture = SDL_CreateTextureFromSurface(g_renderer, surface_sca);
	SDL_FreeSurface(surface_sca);
	scaffoldRect = {126, 4235, 427, 61};


	//Texture
	SDL_Surface* texture = IMG_Load("../Resources/many_new.png");
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
	cushionRect = { 1049,2301,160,76 };
	fadefloorRect = { 1923,2222,215,90 };
	dogRect = { 150,1010,153,193 };
	catRect = { 145,75,167,215 };
	PushbuttonRect = { 855,2305,112,69 };
	PushcushionRect = { 1277,2314,156,68 };
	dogPushRect = { 119,1941,132,179 };
	catDieRect = { 580,770,187,222 };
	dogDieRect = { 342,1537,218,144 };

	SDL_Surface* texture2 = IMG_Load("../Resources/many_2.png");
	many2Texture = SDL_CreateTextureFromSurface(g_renderer, texture2);
	SDL_FreeSurface(texture2);

	lockRect = { 1766,2155,80,214 };


	//restart
	SDL_Surface* rebox = IMG_Load("../Resources/many.png");
	reTexture = SDL_CreateTextureFromSurface(g_renderer, rebox);
	SDL_FreeSurface(rebox);
	reRect = { 2181,108,149,156 };
	reRect_des = { 5,5,50,50 };

	//Sound
	bark = Mix_LoadWAV("../Resources/bark.wav");
	Mix_VolumeChunk(bark, 90);

	meow = Mix_LoadWAV("../Resources/meow.wav");
	Mix_VolumeChunk(meow, 90);

	sniff = Mix_LoadWAV("../Resources/sniff.wav");
	Mix_VolumeChunk(sniff, 50);

	eatingSound = Mix_LoadWAV("../Resources/eatingSound3.wav");
	Mix_VolumeChunk(eatingSound, 20);

	liquidSound = Mix_LoadWAV("../Resources/liquidSound3.wav");
	Mix_VolumeChunk(liquidSound, 10);

	keySound = Mix_LoadWAV("../Resources/keySound.wav");
	Mix_VolumeChunk(liquidSound, 30);

	unlocked = Mix_LoadWAV("../Resources/unlocked.wav");
	Mix_VolumeChunk(liquidSound, 30);


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
	SDL_DestroyTexture(many2Texture);
	SDL_DestroyTexture(liquidTexture);

	SDL_DestroyTexture(reTexture);

	SDL_DestroyTexture(mapbg);
	SDL_DestroyTexture(wallTexture);
	SDL_DestroyTexture(curtainTexture);
	SDL_DestroyTexture(picturesTexture);

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

	if (start.size() == 1) {
	dog->pos.x = start[0].x;
	dog->pos.y = start[0].y;
	cat->pos.x = start[0].x;
	cat->pos.y = start[0].y;
}
else {
	dog->pos.x = start[0].x;
	dog->pos.y = start[0].y;
	cat->pos.x = start[1].x;
	cat->pos.y = start[1].y;
}

	for (int i = 0; i < fadefloors.size(); i++)
	{
		fadefloors[i].Reset();
	}

	for (int i = 0; i < s_liquid.size(); i++)
	{
		s_liquid[i].Reset();
	}

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
		for (misile& missile : mis)
		{
			if (missile.dir == "left") { missile.misile_pos.x -= 7.0f; }
			else if(missile.dir=="right") { missile.misile_pos.x += 7.0f; }
			else { std::cout << "there is no such missile direction "<<missile.dir<<"\n"; }


			for (const Terrain& wall : walls)
			{
				if (SDL_HasIntersection(&missile.misile_pos, &wall.pos))
				{
					missile.misile_pos = missile.initial_pos;
					missile.isHit = true;
					break;
				}
			}
			for (ClimbWall &cw : climbWalls)
			{
				if (SDL_HasIntersection(&missile.misile_pos, &cw.wall_pos))
				{
					missile.misile_pos = missile.initial_pos;
					missile.isHit = true;
					break;
				}
			}
			/*
			for (const Box& b : boxs)
			{
				if (SDL_HasIntersection(&missile.misile_pos, &b.box_pos))
				{
					missile.misile_pos = missile.initial_pos;
					missile.isHit = true;
					break;
				}
			}
			for (const Button& btn : buttons)
			{
				for (int k = 0; k < btn.scaffold_.size(); k++)
				{
					if (SDL_HasIntersection(&missile.misile_pos, &btn.scaffold_[k]))
					{
						missile.misile_pos = missile.initial_pos;
						missile.isHit = true;
						break;
					}
				}
			}
			*/
		}




		


		//PRESS BUTTON/////////////////////////////////////////////////////////////
		for (int i = 0; i < buttons.size(); i++)
		{
			
			//버튼 누르는지 검사
			for (int j = 0; j < buttons[i].buttonPos.size(); j++)
			{
				bool isBoxPressBtn = false;
				
				for (int k = 0; k < boxs.size(); k++)
				{
					if (SDL_HasIntersection(&boxs[k].box_pos, &buttons[i].buttonPos[j]))
					{	isBoxPressBtn=true;	}
				}

				//튕기는거 방지
				buttons[i].petOverlap(dog->pos);
				if (buttons[i].isStop == false) { buttons[i].petOverlap(cat->pos); }
				

				if (SDL_HasIntersection(&dog->pos, &buttons[i].buttonPos[j]) ||
					SDL_HasIntersection(&cat->pos, &buttons[i].buttonPos[j]) || 
					isBoxPressBtn==true)
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
		for (int i = 0; i < fadefloors.size(); i++)
		{
			fadefloors[i].Update();
		}
		//SWELLING LIQUID/////////////////////////////////////////////////////
		for (int i = 0; i < s_liquid.size(); i++)
		{
			s_liquid[i].Update();
		}


	}

	// Cat
	if (cat->nowInput == 0 && cat_v == -1)
	{
		catAnim.cat_move_type = 11;
	} // left idle
	else if (cat->nowInput == 0 && cat_v == 1)
	{
		catAnim.cat_move_type = 12;
	} // right idle
	else if (cat->nowInput == 1)
	{
		catAnim.cat_move_type = 1;
		cat_v = -1;
	} // left walk
	else if (cat->nowInput == 2)
	{
		catAnim.cat_move_type = 2;
		cat_v = 1;
	} // right walk

	if (cat->jumping == true && cat_v == -1)
	{
		catAnim.cat_move_type = 3;
	} // left jump
	else if (cat->jumping == true && cat_v == 1)
	{
		catAnim.cat_move_type = 4;
	} // right jump

	if (cat->isDead == true && cat_v == -1)
	{
		catAnim.cat_move_type = 5;
	} // death left
	else if (cat->isDead == true && cat_v == 1)
	{
		catAnim.cat_move_type = 6;
	} // death right

	if (cat->isLiquid == true && cat_v == -1)
	{
		catAnim.cat_move_type = 7;
	} // skill left
	else if (cat->isLiquid == true && cat_v == 1)
	{
		catAnim.cat_move_type = 8;
	} // skill right

	if (cat->isClimbWall == true && cat_v == -1)
	{
		catAnim.cat_move_type = 9;
	} // left climb
	else if (cat->isClimbWall == true && cat_v == 1)
	{
		catAnim.cat_move_type = 10;
	} // right climb


	//std::cout << dog->box_collide << "\n";

	// Dog
	if (dog->nowInput == 0 && dog_v == -1)
	{
		dogAnim.dog_move_type = 11;
	} // left idle
	else if (dog->nowInput == 0 && dog_v == 1)
	{
		dogAnim.dog_move_type = 12;
	} // right idle
	else if (dog->nowInput == 1)
	{
		dogAnim.dog_move_type = 1;
		dog_v = -1;
	} // left walk
	else if (dog->nowInput == 2)
	{
		dogAnim.dog_move_type = 2;
		dog_v = 1;
	} // right walk

	if (dog->jumping == true && dog_v == -1)
	{
		dogAnim.dog_move_type = 3;
	} // left jump
	else if (dog->jumping == true && dog_v == 1)
	{
		dogAnim.dog_move_type = 4;
	} // right jump

	if (dog->isDead == true && dog_v == -1)
	{
		dogAnim.dog_move_type = 5;
	} // death left
	else if (dog->isDead == true && dog_v == 1)
	{
		dogAnim.dog_move_type = 6;
	} // death right

	if (dog->blindOpacity_ == 0 && dog_v == -1)
	{
		dogAnim.dog_move_type = 7;
	} // skill left(sniff)
	else if (dog->blindOpacity_ > 0 && dog_v == 1)
	{
		dogAnim.dog_move_type = 8;
	} // skill right

	if (dog->box_collide == true && dog_v == -1)
	{
		dogAnim.dog_move_type = 9;
	} // left climb
	else if (dog->box_collide == true && dog_v == 1)
	{
		dogAnim.dog_move_type = 10;
	} // right climb

	catAnim.AddTexture();
	dogAnim.AddTexture();

	g_elapsed_time += 33;
}




void StageInterface::Render()
{
	static int d_index = 0;
	static int c_index = 0;
	static int last_update_time = 0;
	const int update_interval = 100; // 100ms 간격

	// Background
	SDL_SetRenderDrawColor(g_renderer, 229, 221, 192, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, mapbg, &mapSrect[(g_pre_game_phase - 1)%3], &mapDrect);

	// LiquidWall
	for (LiquidWall wall : liquidWalls)
	{

		//SDL_SetRenderDrawColor(g_renderer, 39, 27, 18, 255);
		SDL_SetRenderDrawColor(g_renderer, 112, 87, 37, 255);
		SDL_RenderFillRect(g_renderer, &wall.pos_);
		//SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wall.pos_);
	}

	// Goal,Start
	for (SDL_Rect g : goal)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &goalRect, &g);
	}
	for (SDL_Rect s : start)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &goalRect, &s);
	}


	// cat
	if (catAnim.cat_move_type == 2 || catAnim.cat_move_type == 4 || catAnim.cat_move_type == 6 ||
		catAnim.cat_move_type == 8 || catAnim.cat_move_type == 10 || catAnim.cat_move_type == 12) // right
	{
		SDL_RenderCopyEx(g_renderer, manyTexture, &cat_animation[c_index], &cat->pos, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else // left
	{
		SDL_RenderCopy(g_renderer, manyTexture, &cat_animation[c_index], &cat->pos);
	}

	// dog
	if (dogAnim.dog_move_type == 2 || dogAnim.dog_move_type == 4 || dogAnim.dog_move_type == 6 ||
		dogAnim.dog_move_type == 8 || dogAnim.dog_move_type == 10 || dogAnim.dog_move_type == 12) // right
	{
		SDL_RenderCopyEx(g_renderer, manyTexture, &dog_animation[d_index], &dog->pos, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else // left
	{
		SDL_RenderCopy(g_renderer, manyTexture, &dog_animation[d_index], &dog->pos);
	}

	//fadefloor
	SDL_SetTextureBlendMode(manyTexture, SDL_BLENDMODE_BLEND);
	for (FadeFloor fwall : fadefloors)
	{
		SDL_SetTextureAlphaMod(manyTexture, 255);
		if (fwall.isCollide == true)
		{
			SDL_SetTextureAlphaMod(manyTexture, fwall.alpha);
		}
		SDL_RenderCopy(g_renderer, manyTexture, &fadefloorRect, &fwall.floor_pos);
	}
	SDL_SetTextureAlphaMod(manyTexture, 255);

	// MISSILE
	for (misile m : mis)
	{
		if (m.dir == "right")
		{
			SDL_RenderCopyEx(g_renderer, manyTexture, &misileRect, &m.misile_pos, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(g_renderer, manyTexture, &misileRect, &m.misile_pos);
		}
	}

	// BOX
	for (Box b : boxs)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &boxRect, &b.box_pos);
	}

	// CANNON
	for (int i = 0; i < cannon.size(); i++)
	{
		if (mis[i].isHit) {
			if (mis[i].dir == "left") { SDL_RenderCopy(g_renderer, manyTexture, &lcannonRect, &cannon[i].pos); }
			else { SDL_RenderCopyEx(g_renderer, manyTexture, &lcannonRect, &cannon[i].pos, 0, NULL, SDL_FLIP_HORIZONTAL); }

			Uint32 currentTime = SDL_GetTicks();
			if (currentTime % 8 == 0)
			{
				mis[i].isHit = false;
			}
		}
		else
		{
			if (mis[i].dir == "left") { SDL_RenderCopy(g_renderer, manyTexture, &cannonRect, &cannon[i].pos); }
			else { SDL_RenderCopyEx(g_renderer, manyTexture, &cannonRect, &cannon[i].pos, 0, NULL, SDL_FLIP_HORIZONTAL); }
			
		}
	}

	// fish
	for (Terrain f : fish)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &fishRect, &f.pos);
	}

	// bone
	for (Terrain b : bone)
	{
		SDL_RenderCopy(g_renderer, manyTexture, &boneRect, &b.pos);
	}

	// Button
	for (Button btn : buttons)
	{


		for (int i = 0; i < btn.buttonPos.size(); i++)
		{
			if (btn.isPressed)
			{
				SDL_RenderCopy(g_renderer, manyTexture, &PushbuttonRect, &btn.buttonPos[i]);
			}
			else
			{
				SDL_RenderCopy(g_renderer, manyTexture, &buttonRect, &btn.buttonPos[i]);
			}
		}
		//yellow
		//SDL_SetRenderDrawColor(g_renderer, 225, 154, 17, 255);

		//orange
		SDL_SetRenderDrawColor(g_renderer, 225, 114, 1, 255);
		for (int i = 0; i < btn.scaffold_.size(); i++)
		{
			// Button connected scaffolds
			SDL_RenderFillRect(g_renderer, &btn.scaffold_[i]);
			//SDL_RenderCopy(g_renderer, scaffoldTexture, &scaffoldRect, &btn.scaffold_[i]);
		}
	}



	// liquid
	for (Liquid l : liquid)
	{
		//wall//////////////
		//SDL_SetRenderDrawColor(g_renderer, 39, 27, 18, 255);
		SDL_SetRenderDrawColor(g_renderer, 112, 87, 37, 255);
		SDL_RenderFillRect(g_renderer, &l.wallPos);
		//SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &l.wallPos);

		//liquid///////////
		if (l.liquidClass == "water")
		{
			SDL_RenderCopy(g_renderer, liquidTexture, &waterR, &l.liquidPos);
		}
		else if (l.liquidClass == "choco")
		{
			SDL_SetRenderDrawColor(g_renderer, 50, 29, 14, 255);
			SDL_RenderFillRect(g_renderer, &l.liquidPos);
			//SDL_RenderCopy(g_renderer, liquidTexture, &chocoR, &l.liquidPos);
		}

		else if (l.liquidClass == "milk")
		{
			SDL_RenderCopy(g_renderer, liquidTexture, &milkR, &l.liquidPos);
		}
		else
		{
			std::cout << "there is no such liquid class\n";
		}
	}

	//swelling liquid
	for (SwellingLiquid sl : s_liquid)
	{
		if (sl.liquidClass == "water")
		{
			SDL_RenderCopy(g_renderer, liquidTexture, &waterR, &sl.nowPos);
		}
		else if (sl.liquidClass == "choco")
		{
			SDL_RenderCopy(g_renderer, liquidTexture, &chocoR, &sl.nowPos);
		}
		else if (sl.liquidClass == "milk")
		{
			SDL_RenderCopy(g_renderer, liquidTexture, &milkR, &sl.nowPos);
		}
		else
		{
			std::cout << "there is no such liquid class\n";
		}
	}

	


	// Wall
	for (Terrain wall : walls)
	{
		//SDL_SetRenderDrawColor(g_renderer, 39, 27, 18, 255);
		SDL_SetRenderDrawColor(g_renderer, 112, 87, 37, 255);
		SDL_RenderFillRect(g_renderer, &wall.pos);
		//SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wall.pos);
	}

	

	

	

	// Key and Lock
	for (Key key : keys)
	{
		if (key.isLocked == true)
		{
			SDL_RenderCopy(g_renderer, many2Texture, &lockRect, &key.lockPos);
		}
		if (key.isCollected == false)
		{
			SDL_RenderCopy(g_renderer, manyTexture, &keyRect, &key.keyPos);
		}
	}

	// climbWall
	for (ClimbWall wall : climbWalls)
	{
		SDL_RenderCopy(g_renderer, cwallTexture, &cwallRect, &wall.wall_pos);
	}

	// cushion
	// std::cout << dog->isPressCushion << " cat-" << cat->isPressCushion << "\n";
	for (int i = 0; i < cushions.size(); i++)
	{
		if (dog->isPressCushion == i || cat->isPressCushion == i)
		{
			// std::cout << "pressing cushion\n";
			SDL_RenderCopy(g_renderer, manyTexture, &PushcushionRect, &cushions[i].cushion_pos);
		}
		else
		{
			// std::cout << "not pressing cushion\n";
			SDL_RenderCopy(g_renderer, manyTexture, &cushionRect, &cushions[i].cushion_pos);
		}
	}

	

	// Blind
	SDL_SetTextureBlendMode(picturesTexture, SDL_BLENDMODE_BLEND);
	for (Blind bln : blinds)
	{
		if (dog->isDead == true || cat->isDead == true)
		{
			if (SDL_HasIntersection(&bln.pos, &dog->pos) ||
				SDL_HasIntersection(&bln.pos, &cat->pos))
			{
				SDL_SetTextureAlphaMod(picturesTexture, 70);
				SDL_SetTextureAlphaMod(curtainTexture, 70);
			}
		}
		else
		{
			SDL_SetTextureAlphaMod(picturesTexture, dog->blindOpacity_);
			SDL_SetTextureAlphaMod(curtainTexture, dog->blindOpacity_);
		}
		if (bln.pictureNum <= 5)
		{
			SDL_RenderCopy(g_renderer, picturesTexture, &picturesRect[bln.pictureNum], &bln.pos);
		}
		else
		{
			SDL_RenderCopy(g_renderer, curtainTexture, &picturesRect[bln.pictureNum%8], &bln.pos);
		}
		SDL_SetTextureAlphaMod(picturesTexture, 255);
		SDL_SetTextureAlphaMod(curtainTexture, 255);
	}


	// restart
	SDL_RenderCopy(g_renderer, reTexture, &reRect, &reRect_des);

	SDL_RenderPresent(g_renderer); // draw to the screen

	if (g_elapsed_time - last_update_time >= update_interval)
	{
		c_index++;
		d_index++;

		if (c_index >= cat_animation.size())
		{
			c_index = 0;
		}
		if (d_index >= dog_animation.size())
		{
			d_index = 0;
		}

		last_update_time = g_elapsed_time;
	}
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
		chapterNum = 4;
		g_current_game_phase = PHASE_STAGE5;
		g_pre_game_phase = PHASE_STAGE5;
		break;
	case 4:
		chapterNum = 5;
		g_current_game_phase = PHASE_STAGE6;
		g_pre_game_phase = PHASE_STAGE6;
		break;
	case 5:
		chapterNum = 0;
		g_current_game_phase = PHASE_FINISH;
		g_pre_game_phase = PHASE_STAGE1;
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

				if (x >= reRect_des.x && x <= reRect_des.x + reRect_des.w && y >= reRect_des.y && y <= reRect_des.y + reRect_des.h)
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
