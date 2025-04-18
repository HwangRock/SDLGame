#include "Game.h"
#include "GameIntro.h"


Intro::Intro()
{
	// For Texture

	SDL_Surface* temp_surface = IMG_Load("../Resources/intro.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
	destination_rectangle_.x = source_rectangle_.x = 0;
	destination_rectangle_.y = source_rectangle_.y = 0;
	destination_rectangle_.w = source_rectangle_.w;
	destination_rectangle_.h = source_rectangle_.h;

	///txt texture
	SDL_Surface* temp_surface2 = IMG_Load("../Resources/introtxt.png");
	txt_texture_= SDL_CreateTextureFromSurface(g_renderer, temp_surface2);
	SDL_FreeSurface(temp_surface2);
	
	srect_txt = { 0, 0, 1294, 221 };
	drect_txt = { 465, 640, 350, 60 };

	lastBlinkingTime = SDL_GetTicks();
	txtBlinking = true;

}

Intro::~Intro()
{
	SDL_DestroyTexture(texture_);
	SDL_DestroyTexture(txt_texture_);
}

void Intro::Update()
{
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
}


void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

	if (txtBlinking == true) {
		SDL_RenderCopy(g_renderer, txt_texture_, &srect_txt, &drect_txt);
	}
	

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void Intro::HandleEvents()
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

			g_current_game_phase = PHASE_MANUAL;
			//g_pre_game_phase = PHASE_STAGE1; // 메뉴얼에서 플레이 버튼 누르면 스테이지 원으로 넘어가게 하기 위해 바꿨습니다!
			break;

		default:
			break;
		}
	}
}
