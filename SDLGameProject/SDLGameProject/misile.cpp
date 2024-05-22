#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class misile
{
public:
    SDL_Rect misile_pos;
    SDL_Rect initial_pos;  // 초기 위치 저장

    misile(SDL_Rect pos)
    {
        misile_pos = pos;
        initial_pos = pos;  // 초기 위치 설정
    }
};
