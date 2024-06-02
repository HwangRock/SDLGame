#include "Game.h"
#include "GameManual.h"

int c = 0;

Manual::Manual()
{
	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/manual1.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_Surface* man_surface = IMG_Load("../Resources/manual2.png");
	texture_2 = SDL_CreateTextureFromSurface(g_renderer, man_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	SDL_QueryTexture(texture_2, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = 1280;
	destination_rectangle_.h = 700;

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
	if (!c) {
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderClear(g_renderer); // clear the renderer to the draw color

		SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);
	}
	else {
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderClear(g_renderer); // clear the renderer to the draw color

		SDL_RenderCopy(g_renderer, texture_2, &source_rectangle_, &destination_rectangle_);
	}

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
			if (!c) {
				c = 1;
			}
			else {
				c = 0;
				g_current_game_phase = PHASE_STAGE1;
			}
			break;

		default:
			break;
		}
	}
}