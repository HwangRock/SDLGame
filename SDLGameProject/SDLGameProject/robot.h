#pragma once
#include "movingObject.h"

class robot : public movingObject {
public:
    robot(SDL_Rect start, SDL_Rect end);

    void Reset();
    void Update();

    int speed;
    bool isColision;
    SDL_Rect startPoint;
    SDL_Rect endPoint;
    SDL_Rect currentLocation;
    bool direction;
};

