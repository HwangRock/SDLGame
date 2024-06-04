
#include "Game.h"
#include "Stage.h"

#include "GameIntro.h"
#include "GameEnding.h"
#include "GameManual.h"
#include "GameESC.h"
#include "FinishGame.h"

#include "GameOver.cpp"
#include "GameClear.cpp"

#include "Map1.cpp" 
#include "Map2.cpp"
#include "Map3.cpp"
#include "Map4.cpp"
#include "Map5.cpp"
#include "Map6.cpp"


/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

// Game Phases
int g_current_game_phase;
int g_pre_game_phase;

float g_timestep_s = 1.0f / 60.0f;



//Game Variables//////////////////////////////////////
std::vector<Terrain> walls = {};
std::vector<Button>buttons = {};
//Blind(sniff, dog skill)
std::vector<Blind> blinds = {};
//Liquid wall(cat skill)
std::vector<LiquidWall>liquidWalls = {};
std::vector<SDL_Rect>liquidAisles = {};
std::vector<ClimbWall>climbWalls = {};
std::vector<Cushion>cushions = {};
std::vector<FadeFloor>fadefloors = {};

std::vector<SDL_Rect> cat_animation = {{141, 75, 172, 219}, {141, 75, 172, 219}, {141, 75, 172, 219}, {818, 75, 172, 219}, {1047, 75, 172, 219}, {1274, 75, 172, 219}, {1495, 75, 172, 219}, {1714, 75, 172, 219}, {1947, 75, 172, 219}};
std::vector<SDL_Rect> dog_animation = {{142, 1011, 165, 198}, {142, 1011, 165, 198}, {142, 1011, 165, 198}, {142, 1011, 165, 198}, {142, 1011, 165, 198}, {1264, 1011, 162, 186}, {1264, 1011, 162, 186}, {1264, 1011, 162, 186}, {1264, 1011, 162, 186}, {1264, 1011, 162, 186}};

//liquid
std::vector<Liquid>liquid = {};
std::vector<SwellingLiquid>s_liquid = {};

std::vector<Box> boxs = {};
std::vector<Terrain> cannon = {};
std::vector<Terrain> fish = {};
std::vector<Terrain> bone = {};
std::vector<misile>mis = {};


//Item
std::vector<Key>keys = {};


SDL_Texture *manyTexture;
SDL_Texture* many2Texture;

std::vector <SDL_Rect> goal = {};
std::vector <SDL_Rect> start = {};
int chapterNum;
int win_w, win_h;
bool isFirst;


//map bg image
SDL_Texture* mapbg;
SDL_Rect mapSrect[3];
SDL_Rect mapDrect;



//Music
Mix_Music* g_bgm;
bool phase1first;
bool musOnOff; //인트로와 엔딩 음악에 한해서만 On_true, Off=false

//Sound
Mix_Chunk* sniff;
Mix_Chunk* bark;
Mix_Chunk* meow;
Mix_Chunk* liquidSound;
Mix_Chunk* eatingSound;
Mix_Chunk* keySound;
Mix_Chunk* unlocked;



int score_bone;
int score_fish;


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

	PhaseInterface* game_phases[13];
	game_phases[0] = new Intro;
	game_phases[1] = new Map1;
	game_phases[2] = new Map2;
	game_phases[3] = new Map3;
	game_phases[4] = new Map4;
	game_phases[5] = new Map5;
	game_phases[6] = new Map6;
	game_phases[7] = new Ending;
	game_phases[8] = new Over;
	game_phases[9] = new Clear;
	game_phases[10] = new ESC;
	game_phases[11] = new Manual;
	game_phases[12] = new Finish;
	
	
	g_current_game_phase = PHASE_INTRO;
	g_pre_game_phase = PHASE_STAGE1;

	//REPEAT//////////////////////////////////////////
	while (g_flag_running)
	{
		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < (1000 * g_timestep_s)) 
			continue;

		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		PlayingMusic();

		
		g_last_time_ms = cur_time_ms;
	}


	//END////////////////////////////////////////////
	

	for (int i = 0; i < 13; i++)
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
