#include "Trap.h"

Trap::Trap(SDL_Rect touchPoint, SDL_Rect blockTrap, int timeDelay_)
{
    this->touchPoint = touchPoint;
    this->blockTrap = blockTrap;
    timeDelay = timeDelay_;
    Reset();
}

void Trap::Reset()
{
    time = 0;
    isDogTouch = false;
    isCatTouch = false;
    trapActivated = false;
}
