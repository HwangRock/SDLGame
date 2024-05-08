
#include "Game.h"
#include "GameIntro.h"
#include "GameEnding.h"
#include "Stage.h"
#include "Map1.cpp"
#include "Map2.cpp"
#include "Map3.cpp"
#include "Map4.cpp"


/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

// Game Phases
int g_current_game_phase;

// 초단위 timestep (1/60초). Frame time과 시뮬레이션의 timestep으로 사용된다.
float g_timestep_s = 1.0f / 60.0f;



//Game Variables//////////////////////////////////////
std::vector<Terrain> walls = {};
std::vector<Button>buttons = {};
//Blind(sniff, dog skill)
std::vector<SDL_Rect> blinds = {};
//Liquid wall(cat skill)
std::vector<LiquidWall>liquidWalls = {};
std::vector<SDL_Rect>liquidAisles = {};
int chapterNum;
int win_w, win_h;




int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	g_window = SDL_CreateWindow("thisWindow", 100, 100, 1280, 720, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);



	g_last_time_ms = SDL_GetTicks();

	InitGame(); 

	PhaseInterface* game_phases[6];
	game_phases[0] = new Intro;
	game_phases[1] = new Map1;
	game_phases[2] = new Map2;
	game_phases[3] = new Map3;
	game_phases[4] = new Map4;
	game_phases[5] = new Ending;

	g_current_game_phase = PHASE_INTRO;


	//REPEAT//////////////////////////////////////////
	while (g_flag_running)
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < (1000 * g_timestep_s)) // 밀리세턴드 단위로 변환하기 위해 1000 곱함
			continue;

		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		g_last_time_ms = cur_time_ms;
	}


	//END////////////////////////////////////////////
	

	for (int i = 0; i < 6; i++)
	{
		delete game_phases[i];
	}

	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();

	Mix_CloseAudio();
	TTF_Quit();

	return 0;
}
