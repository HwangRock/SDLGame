#pragma once
#include "SDL.h"
#include "GameManual.h"

Manual::Manual()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/control_window.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w;
	destination_rectangle_.h = source_rectangle_.h;

	button_rect_.x = 1010;
	button_rect_.y = 600;
	button_rect_.w = 215;
	button_rect_.h = 66;
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

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				//return button
				if (mouse_x > button_rect_.x &&
					mouse_y > button_rect_.y &&
					mouse_x < button_rect_.x + button_rect_.w &&
					mouse_y < button_rect_.y + button_rect_.h)
				{
					g_current_game_phase = PHASE_ESC;
				}
			}

			break;

		default:
			break;
		}
	}
}

