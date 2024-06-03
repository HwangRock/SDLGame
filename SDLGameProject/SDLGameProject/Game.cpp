#include "Game.h"

void InitGame() {
	g_flag_running = true;
	phase1first = true;
	musOnOff = false;
}

void ClearGame() {
	Mix_FreeChunk(bark);
	Mix_FreeChunk(meow);
	Mix_FreeChunk(sniff);
	Mix_FreeChunk(eatingSound);
	Mix_FreeChunk(liquidSound);
	Mix_FreeChunk(keySound);
	Mix_FreeChunk(unlocked);
}

void PlayingMusic() {
	if (musOnOff == false && g_current_game_phase == PHASE_INTRO) {
		Mix_FreeMusic(g_bgm);
		g_bgm = Mix_LoadMUS("../Resources/intro_bgm.mp3");

		if (!g_bgm) { //오류 뭔지 알려주는 구문
			std::cout << "Mix_LoadMUS(\"intro_bgm.mp3\"):" << Mix_GetError() << std::endl;
		}

		Mix_PlayMusic(g_bgm, -1);
		Mix_VolumeMusic(7);

		musOnOff = true;
	}

	else if (phase1first == true && g_current_game_phase == PHASE_STAGE1) {
		Mix_FreeMusic(g_bgm);

		g_bgm = Mix_LoadMUS("../Resources/stage_bgm.mp3");

		if (!g_bgm) { //오류 뭔지 알려주는 구문
			std::cout << "Mix_LoadMUS(\"stage_bgm.mp3\"):" << Mix_GetError() << std::endl;
		}

		Mix_PlayMusic(g_bgm, -1);
		Mix_VolumeMusic(7);

		phase1first = false;
		musOnOff = false;
	}

	else if (musOnOff == false && g_current_game_phase == PHASE_FINISH) { //엔딩 이후 인트로로 돌아갈 때 musOnOff = false 해줘야 함.
		Mix_FreeMusic(g_bgm);

		g_bgm = Mix_LoadMUS("../Resources/ending_bgm.mp3");

		if (!g_bgm) { //오류 뭔지 알려주는 구문
			std::cout << "Mix_LoadMUS(\"ending_bgm.mp3\"):" << Mix_GetError() << std::endl;
		}

		Mix_PlayMusic(g_bgm, -1);
		Mix_VolumeMusic(7);

		musOnOff = true;
	}
}