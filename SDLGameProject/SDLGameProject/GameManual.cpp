#include "Game.h"
#include "GameManual.h"



Manual::Manual()
{
	// For Texture

	pageNow = 0; //0이 메뉴얼 첫번째 장임.

	SDL_Surface* temp_surface = IMG_Load("../Resources/manual2.png");
	manualtexture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(manualtexture_, NULL, NULL, &source_rectangle_[pageNow].w, &source_rectangle_[pageNow].h);

	source_rectangle_[0] = { 0, 0, 1280, 720 };
	source_rectangle_[1] = { 0, 720, 1280, 720 };

	leftBtnRect = { 10, 316, 120, 92 };
	rightBtnRect = { 1145, 314, 120, 92 };



	destination_rectangle_ = { 0, 0, 1280, 720 };

}

Manual::~Manual()
{
	SDL_DestroyTexture(manualtexture_);
}

void Manual::Update()
{

}


void Manual::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, manualtexture_, &source_rectangle_[pageNow], &destination_rectangle_);

	SDL_RenderPresent(g_renderer); // draw to the screen


}



void Manual::HandleEvents()
{
	int x{}, y{};

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

				x = event.button.x;
				y = event.button.y;

				switch (pageNow) {
				case 0:
					if (x >= rightBtnRect.x && x <= rightBtnRect.x + rightBtnRect.w &&
						y >= rightBtnRect.y && y <= rightBtnRect.y + rightBtnRect.h)
					{
						pageNow = 1;
					}

					break;

				case 1:
					if (x >= leftBtnRect.x && x <= leftBtnRect.x + leftBtnRect.w &&
						y >= leftBtnRect.y && y <= leftBtnRect.y + leftBtnRect.h)
					{
						pageNow = 0;
					}
					else if (x >= rightBtnRect.x && x <= rightBtnRect.x + rightBtnRect.w &&
						y >= rightBtnRect.y && y <= rightBtnRect.y + rightBtnRect.h)
					{
						g_current_game_phase = g_pre_game_phase; ///ESC 누르기 전에 있던 맵으로 가도록
						pageNow = 0;
					}

					break;
				}


			}
			break;
			//case SDL_KEYDOWN:
				//g_current_game_phase = PHASE_STAGE1;
				//break;

			//default:
				//break;
		}
	}
}
