#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include "Terrain.h"

class Box {
public:
    SDL_Rect box_pos;
    double v[2] = { 0, };

    Box(SDL_Rect pos);

    void Reset();
    virtual void Update(double timestep_s);
    virtual void BlockMoving(SDL_Rect obst);

};
