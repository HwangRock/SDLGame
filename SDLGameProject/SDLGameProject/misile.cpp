#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
class misile
{
public:
    SDL_Rect misile_pos;
    SDL_Rect initial_pos;  // 초기 위치 저장
    std::string dir;
    bool isHit;

    misile(SDL_Rect pos,std::string direction)
    {
        dir = direction;
        misile_pos = pos;
        initial_pos = pos;  // 초기 위치 설정
        Reset();
    }
    void Reset()
    {
        isHit = false;
    }
};
