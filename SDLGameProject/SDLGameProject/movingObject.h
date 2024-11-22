#pragma once
#include "SDL.h"

class movingObject {
public:
    movingObject();

    virtual ~movingObject() = default;

    int speed;
    bool isColision;
    SDL_Rect startPoint;
    SDL_Rect endPoint;
    SDL_Rect currentLocation;
    bool direction;

    virtual void Update() = 0;
    void Reset();
    void moving();
};

