#pragma once
#include "SDL.h"
#include "Game.h"

class Over : public PhaseInterface
{
public:
	Over() 
	{
		//TEXTURE////////////////////////////////////////////////
		//IMG, TEXT
		SDL_Surface* temp_surface = IMG_Load("../Resources/gameOverImg.jpg");
		imgTexture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		imgRect = { 0,0,1488,704 };


		SDL_Surface* txt_surface = IMG_Load("../Resources/gameOverTxt.jpg");
		txtTexture = SDL_CreateTextureFromSurface(g_renderer, txt_surface);
		SDL_FreeSurface(txt_surface);
		txtRect = { 0,0,666,182 };


		imgPos = { 300,50,500,200 };
		txtPos = { 300,450,500,50 };

	};
	~Over() 
	{
		SDL_DestroyTexture(imgTexture);
	};
	virtual void HandleEvents()
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				g_flag_running = false;
				break;

			case SDL_MOUSEBUTTONDOWN:

				if (event.button.button == SDL_BUTTON_LEFT)
				{
					switch (chapterNum)
					{
					case 0:
						g_current_game_phase = PHASE_STAGE1;
						break;
					case 1:
						g_current_game_phase = PHASE_STAGE2;
						break;
					case 2:
						g_current_game_phase = PHASE_STAGE3;
						break;
					case 3:
						g_current_game_phase = PHASE_STAGE4;
						break;
					default:
						break;
					}
				}
				break;

			default:
				break;
			}
		}
	};
	virtual void Update() {};
	virtual void Render() 
	{
		//RENDER/////////////////////////////////////////////////
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderClear(g_renderer);

		//IMG
		SDL_RenderCopy(g_renderer, imgTexture, &imgRect, &imgPos);
		//Text
		SDL_RenderCopy(g_renderer, txtTexture, &txtRect, &txtPos);


		SDL_RenderPresent(g_renderer);
	};

private:

	//img ㅡ "game clear!"
	SDL_Texture* imgTexture;
	SDL_Rect imgRect;
	SDL_Rect imgPos;

	//text img ㅡ "아무키를 눌러 다음 게임을 시작하세요"
	SDL_Texture* txtTexture;
	SDL_Rect txtRect;
	SDL_Rect txtPos;


};


