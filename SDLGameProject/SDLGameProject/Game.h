#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_STAGE1 = 1;
const int PHASE_STAGE2 = 2;
const int PHASE_STAGE3 = 3;
const int PHASE_STAGE4 = 4;
const int PHASE_STAGE5 = 5;
const int PHASE_STAGE6 = 6;
const int PHASE_ENDING = 7;
const int PHASE_OVER = 8;
const int PHASE_CLEAR = 9;
const int PHASE_ESC = 10;
const int PHASE_MANUAL = 11;
const int PHASE_FINISH = 12;

void InitGame();
void ClearGame();
void PlayingMusic();

extern int g_current_game_phase;
extern int g_pre_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;

extern int chapterNum;

extern Mix_Music* g_bgm;
extern bool phase1first;
extern bool musOnOff;

extern Mix_Chunk* sniff;
extern Mix_Chunk* bark;
extern Mix_Chunk* meow;
extern Mix_Chunk* liquidSound;
extern Mix_Chunk* eatingSound;
extern Mix_Chunk* keySound;
extern Mix_Chunk* unlocked;


class PhaseInterface
{
public:
	PhaseInterface() {};
	virtual ~PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};
