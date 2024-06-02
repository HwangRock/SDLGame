#include "Game.h"
#include "GameManual.h"


Manual::Manual()
{
	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/manual.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = 1280;
	destination_rectangle_.h = 700;
	///
}

Manual::~Manual()
{
	SDL_DestroyTexture(texture_);
}

void Manual::Update()
{
}


void Manual::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Manual::HandleEvents()
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
			g_current_game_phase = PHASE_STAGE1;
			g_pre_game_phase = PHASE_STAGE1;
			break;

		default:
			break;
		}
	}
}
