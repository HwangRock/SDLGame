#pragma once
#include "SDL.h"
#include "Game.h"


class GameFinish : public PhaseInterface
{
public:
	GameFinish()
	{
		//IMG
		SDL_Surface* temp_surface = IMG_Load("../Resources/intro.png");
		imgTexture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		imgRect = { 0,0,1020,1020 };

		
		//TEXT
		TTF_Font* font1 = TTF_OpenFont("../Resources/arose.ttf", 20);
		SDL_Color black = { 0,0,0,0 };
		SDL_Surface* tmp_surface= TTF_RenderText_Blended(font1, "Game Finish", black);
		text1Rect = { 0,0,tmp_surface->w,tmp_surface->h };
		text2Rect = { 0,0,tmp_surface->w,tmp_surface->h };
		fontTexture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
		SDL_FreeSurface(tmp_surface);
		TTF_CloseFont(font1);



		text1Pos = { 100,100,text1Rect.w,text1Rect.h };
		text2Pos = { 100,400,text1Rect.w,text1Rect.h };
		//RENDER/////////////////////////////////////////////////
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderClear(g_renderer);

		//IMG
		SDL_RenderCopy(g_renderer, imgTexture, &imgRect, &imgPos);
		//Text1
		SDL_RenderCopy(g_renderer, fontTexture, &text1Rect, &text1Pos);
		//Text2
		SDL_RenderCopy(g_renderer, fontTexture, &text2Rect, &text2Pos);


		SDL_RenderPresent(g_renderer);
	
	};
	~GameFinish()
	{
		SDL_DestroyTexture(fontTexture);
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

				// If the mouse left button is pressed. 
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					g_current_game_phase = PHASE_STAGE1;
				}
				break;

			default:
				break;
			}
		}
	};
	virtual void Update();
	virtual void Render()
	{	
	};

	
protected:
	
	SDL_Texture* fontTexture;
	SDL_Texture* imgTexture;

	SDL_Rect text1Pos;
	SDL_Rect text2Pos;
	SDL_Rect imgPos;

	SDL_Rect text1Rect;
	SDL_Rect text2Rect;
	SDL_Rect imgRect;


};


