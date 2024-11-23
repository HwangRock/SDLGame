#ifndef TRAP_H
#define TRAP_H
#include <iostream>
#include "SDL_image.h"
#include "SDL.h"

class Trap
{
public:
    Trap(SDL_Rect touchPoint, SDL_Rect blockTrap, int timeDelay_);

    void Reset();

    // Members
    SDL_Rect touchPoint; // two pets have to touch here
    SDL_Rect blockTrap;  // this trap will appear and lock pets
    bool isDogTouch;
    bool isCatTouch;
    bool trapActivated;

protected:
    int timeDelay;
    int time;
};

#endif // TRAP_H
