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

		if (!g_bgm) { //���� ���� �˷��ִ� ����
			std::cout << "Mix_LoadMUS(\"intro_bgm.mp3\"):" << Mix_GetError() << std::endl;
		}

		Mix_PlayMusic(g_bgm, -1);
		Mix_VolumeMusic(7);

		musOnOff = true;
	}

	else if (phase1first == true && g_current_game_phase == PHASE_STAGE1) {
		Mix_FreeMusic(g_bgm);

		g_bgm = Mix_LoadMUS("../Resources/stage_bgm.mp3");

		if (!g_bgm) { //���� ���� �˷��ִ� ����
			std::cout << "Mix_LoadMUS(\"stage_bgm.mp3\"):" << Mix_GetError() << std::endl;
		}

		Mix_PlayMusic(g_bgm, -1);
		Mix_VolumeMusic(7);

		phase1first = false;
		musOnOff = false;
	}

	else if (musOnOff == false && g_current_game_phase == PHASE_FINISH) { //���� ���� ��Ʈ�η� ���ư� �� musOnOff = false ����� ��.
		Mix_FreeMusic(g_bgm);

		g_bgm = Mix_LoadMUS("../Resources/ending_bgm.mp3");

		if (!g_bgm) { //���� ���� �˷��ִ� ����
			std::cout << "Mix_LoadMUS(\"ending_bgm.mp3\"):" << Mix_GetError() << std::endl;
		}

		Mix_PlayMusic(g_bgm, -1);
		Mix_VolumeMusic(7);

		musOnOff = true;
	}
}