#pragma once
#include "SDL.h"
#include "GameESC.h"


ESC::ESC()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/esc_window.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w;
	destination_rectangle_.h = source_rectangle_.h;
 
	button1_rect_.x = 495;
	button1_rect_.y = 201;
	button1_rect_.w = 291;
	button1_rect_.h= 85;

	button2_rect_.x = 437;
	button2_rect_.y = 309;
	button2_rect_.w = 403;
	button2_rect_.h = 85;

	button3_rect_.x = 495;
	button3_rect_.y = 420;
	button3_rect_.w = 286;
	button3_rect_.h = 81;

	button4_rect_.x = 553;
	button4_rect_.y = 527;
	button4_rect_.w = 174;
	button4_rect_.h = 82;

}

ESC::~ESC()
{
	SDL_DestroyTexture(texture_);
}

void ESC::Update()
{
}


void ESC::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void ESC::HandleEvents()
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

				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				//resume button
				if (mouse_x > button1_rect_.x &&
					mouse_y > button1_rect_.y &&
					mouse_x < button1_rect_.x + button1_rect_.w &&
					mouse_y < button1_rect_.y + button1_rect_.h)
				{
					g_current_game_phase = g_pre_game_phase;
				}


				//go to intro button
				else if (mouse_x > button2_rect_.x &&
					mouse_y > button2_rect_.y &&
					mouse_x < button2_rect_.x + button2_rect_.w &&
					mouse_y < button2_rect_.y + button2_rect_.h)
				{
					g_current_game_phase = PHASE_INTRO;
					g_pre_game_phase = PHASE_STAGE1;
					chapterNum = 0;
				}


				//control button
				else if (mouse_x > button3_rect_.x &&
					mouse_y > button3_rect_.y &&
					mouse_x < button3_rect_.x + button3_rect_.w &&
					mouse_y < button3_rect_.y + button3_rect_.h)
				{
					g_current_game_phase = PHASE_MANUAL;
				}


				//exit button
				else if (mouse_x > button4_rect_.x &&
					mouse_y > button4_rect_.y &&
					mouse_x < button4_rect_.x + button4_rect_.w &&
					mouse_y < button4_rect_.y + button4_rect_.h)
				{
					g_flag_running = false;
				}

				//g_current_game_phase = PHASE_STAGE1;
			}
			break;

		default:
			break;
		}
	}
}


