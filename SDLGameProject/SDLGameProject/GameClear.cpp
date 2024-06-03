#pragma once
#include "SDL.h"
#include "Game.h"
#include "Stage.h"
#include "SDL_ttf.h"

class Clear : public PhaseInterface
{
public:

	Clear()
	{
		//TEXTURE////////////////////////////////////////////////
		//FONT
		font = TTF_OpenFont("../Resources/scorefont.ttf", 100);
		if (font == NULL) {
			std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
		}
		scorePos_cat = { 750,545,50,30 };
		scorePos_dog = { 560,545,50,30 };

		//Game Clear UI
		SDL_Surface* surface_nextBtn = IMG_Load("../Resources/nextStageBtn.png");
		clear_nextStageBtnTexture = SDL_CreateTextureFromSurface(g_renderer, surface_nextBtn);
		SDL_FreeSurface(surface_nextBtn);

		clear_nextRect = { 0,0,967,172 };
		nextBtnPos = { 1053,620,197,35 };

		SDL_Surface* surface_restartBtn = IMG_Load("../Resources/restartBtn.png");
		clear_restartBtnTexture = SDL_CreateTextureFromSurface(g_renderer, surface_restartBtn);
		SDL_FreeSurface(surface_restartBtn);

		clear_restartRect = { 0,0,967,172 };
		restartBtnPos = { 10,620,197,35 };


		//IMG, TEXT
		SDL_Surface* temp_surface = IMG_Load("../Resources/gameClearImg.png");
		imgTexture = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		imgRect = { 0,0,1280,720 };
		imgPos = { 0,0,1280,720 };

		//SDL_Surface* txt_surface = IMG_Load("../Resources/tapAnyKeyForNext.png");
		//txtTexture = SDL_CreateTextureFromSurface(g_renderer, txt_surface);
		//SDL_FreeSurface(txt_surface);
		//txtRect = { 0,0,715,58 };



		//txtPos = { 483,680,358,29 };

		//배경에 물고기와 뼈다귀가 모두 있는 관계로 주석 처리.
		//FISH __________________________________________________________________배경 내 위치 ={659, 539, 77, 53}
		//SDL_Surface* fish_surface = IMG_Load("../Resources/fish.png");
		//fishTexture = SDL_CreateTextureFromSurface(g_renderer, fish_surface);
		//SDL_FreeSurface(fish_surface);
		//fishRect = { 0,0,443,340 };
		//fishPos = { 400,300,100,50 };

		//BONE __________________________________________________________________배경 내 위치 ={473, 530, 73, 57}
		//SDL_Surface* bone_surface = IMG_Load("../Resources/bone.png");
		//boneTexture = SDL_CreateTextureFromSurface(g_renderer, bone_surface);
		//SDL_FreeSurface(bone_surface);
		//boneRect = { 0,0,325,196 };
		//bonePos = { 600,300,100,50 };




	};
	~Clear() {
		//SDL_DestroyTexture(fishTexture);
		//SDL_DestroyTexture(boneTexture);
		SDL_DestroyTexture(imgTexture);
		SDL_DestroyTexture(clear_nextStageBtnTexture);
		SDL_DestroyTexture(clear_restartBtnTexture);
		SDL_DestroyTexture(scoreTexture_dog);
		SDL_DestroyTexture(scoreTexture_cat);

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();

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
					int x, y;
					x = event.button.x;
					y = event.button.y;

					if (x >= restartBtnPos.x && x <= restartBtnPos.x + restartBtnPos.w &&
						y >= restartBtnPos.y && y <= restartBtnPos.y + restartBtnPos.h)
					{
						//RESTART
						switch (chapterNum)
						{
						case 0:
							chapterNum = 0;
							g_current_game_phase = PHASE_STAGE1;

							break;
						case 1:
							chapterNum = 1;
							g_current_game_phase = PHASE_STAGE2;

							break;
						case 2:
							chapterNum = 2;
							g_current_game_phase = PHASE_STAGE3;

							break;
						case 3:
							chapterNum = 3;
							g_current_game_phase = PHASE_STAGE4;
							break;
						case 4:
							chapterNum = 4;
							g_current_game_phase = PHASE_STAGE5;
							break;
						case 5:
							chapterNum = 5;
							g_current_game_phase = PHASE_STAGE6;
							break;
						default:
							std::cout << "restart error\n";
							break;
						}
					}

					else if
						(x >= nextBtnPos.x && x <= nextBtnPos.x + nextBtnPos.w &&
							y >= nextBtnPos.y && y <= nextBtnPos.y + nextBtnPos.h)
					{
						//NEXT
						switch (chapterNum)
						{
						case 0:
							chapterNum = 1;
							g_current_game_phase = PHASE_STAGE2;

							break;
						case 1:
							chapterNum = 2;
							g_current_game_phase = PHASE_STAGE3;

							break;
						case 2:
							chapterNum = 3;
							g_current_game_phase = PHASE_STAGE4;

							break;
						case 3:
							chapterNum = 4;
							g_current_game_phase = PHASE_STAGE5;

							break;
						case 4:
							chapterNum = 5;
							g_current_game_phase = PHASE_STAGE6;

							break;
						case 5:
							chapterNum = 0;
							g_current_game_phase = PHASE_FINISH;

							break;
						default:
							std::cout << "next chapter error\n";
							break;
						}
					}
				}
				break;

			default:
				break;
			}
		}
	};
	virtual void Update() { UpdateScore(); };
	virtual void Render() {

		//RENDER/////////////////////////////////////////////////
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderClear(g_renderer);

		//IMG
		SDL_RenderCopy(g_renderer, imgTexture, &imgRect, &imgPos);
		//Text
		SDL_RenderCopy(g_renderer, txtTexture, &txtRect, &txtPos);
		//Fish
		//SDL_RenderCopy(g_renderer, fishTexture, &fishRect, &fishPos);
		//Bone
		//SDL_RenderCopy(g_renderer, boneTexture, &boneRect, &bonePos);

		//Button UI
		SDL_RenderCopy(g_renderer, clear_restartBtnTexture, &clear_restartRect, &restartBtnPos);
		SDL_RenderCopy(g_renderer, clear_nextStageBtnTexture, &clear_nextRect, &nextBtnPos);


		//score
		SDL_RenderCopy(g_renderer, scoreTexture_cat, &scoreRect_cat, &scorePos_cat);
		SDL_RenderCopy(g_renderer, scoreTexture_dog, &scoreRect_dog, &scorePos_dog);

		SDL_RenderPresent(g_renderer);
	};

	void UpdateScore()
	{
		//destroy from memory
		if (scoreTexture_dog != 0)
		{
			SDL_DestroyTexture(scoreTexture_dog);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
			scoreTexture_dog = 0;
		}
		if (scoreTexture_cat != 0)
		{
			SDL_DestroyTexture(scoreTexture_cat);
			scoreTexture_cat = 0;
		}


		std::string scoreResult_cat = std::to_string(score_fish) + "/" + std::to_string(fish.size());
		std::string scoreResult_dog = std::to_string(score_bone) + "/" + std::to_string(bone.size());


		SDL_Color black = { 0, 0, 0, 0 };

		SDL_Surface* tmp_surface1 = TTF_RenderText_Blended(font, scoreResult_cat.c_str(), black);
		scoreRect_cat = { 0,0,tmp_surface1->w,tmp_surface1->h };
		scoreTexture_cat = SDL_CreateTextureFromSurface(g_renderer, tmp_surface1);
		SDL_FreeSurface(tmp_surface1);

		SDL_Surface* tmp_surface2 = TTF_RenderText_Blended(font, scoreResult_dog.c_str(), black);
		scoreRect_dog = { 0,0,tmp_surface2->w,tmp_surface2->h };
		scoreTexture_dog = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);
		SDL_FreeSurface(tmp_surface2);


	}

private:


	//img ㅡ "game clear!"
	SDL_Texture* imgTexture;
	SDL_Rect imgRect;
	SDL_Rect imgPos;

	//text img ㅡ "아무키를 눌러 다음 게임을 시작하세요"
	SDL_Texture* txtTexture;
	SDL_Rect txtRect;
	SDL_Rect txtPos;

	//button ㅡ restart this chapter
	//.........

	//score
	SDL_Texture* fishTexture;
	SDL_Texture* boneTexture;
	SDL_Rect fishRect;
	SDL_Rect boneRect;
	SDL_Rect fishPos;
	SDL_Rect bonePos;


	//Game Clear UI
	SDL_Texture* clear_nextStageBtnTexture;
	SDL_Texture* clear_restartBtnTexture;

	SDL_Rect clear_nextRect;
	SDL_Rect clear_restartRect;

	SDL_Rect nextBtnPos;
	SDL_Rect restartBtnPos;


	//text texture
	TTF_Font* font;
	SDL_Texture* scoreTexture_dog;
	SDL_Rect scoreRect_dog;
	SDL_Rect scorePos_dog;
	SDL_Texture* scoreTexture_cat;
	SDL_Rect scoreRect_cat;
	SDL_Rect scorePos_cat;
};


