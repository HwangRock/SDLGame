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
		SDL_Surface* temp_surface = IMG_Load("../Resources/gameOverImg.png");
		imgTexture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);

		imgRect = { 0,0,1920,1080 };
		imgPos = { 0,0,1280,720 };

		SDL_Surface* txt_surface = IMG_Load("../Resources/tapAnyKeyTxt.png");
		txtTexture = SDL_CreateTextureFromSurface(g_renderer, txt_surface);
		SDL_FreeSurface(txt_surface);

		txtRect = { 0,0,628,58 };
		txtPos = { 478,660,314,29 };

		lastBlinkingTime = SDL_GetTicks();
		txtBlinking = true;






	};
	~Over()
	{
		SDL_DestroyTexture(imgTexture);
		SDL_DestroyTexture(txtTexture);
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
			case SDL_KEYDOWN:

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
				case 4:
					g_current_game_phase = PHASE_STAGE5;
					break;
				case 5:
					g_current_game_phase = PHASE_STAGE6;
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	};
	virtual void Update() {

		blinkingTime = SDL_GetTicks();

		if (blinkingTime - lastBlinkingTime >= 450) {
			if (txtBlinking == false) {
				txtBlinking = true;
			}
			else
			{
				txtBlinking = false;
			}
			lastBlinkingTime = blinkingTime;
		}
	};
	virtual void Render()
	{
		//RENDER/////////////////////////////////////////////////
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderClear(g_renderer);

		//IMG
		SDL_RenderCopy(g_renderer, imgTexture, &imgRect, &imgPos);
		//Text

		if (txtBlinking == true) {
			SDL_RenderCopy(g_renderer, txtTexture, &txtRect, &txtPos);
		}


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

	int blinkingTime;
	int lastBlinkingTime;
	bool txtBlinking;

};


