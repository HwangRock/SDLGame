#ifndef SWELLINGLIQUID_H
#define SWELLINGLIQUID_H

#include <string>
#include "SDL.h"
#include "Trap.h"

class SwellingLiquid
{
public:
    SwellingLiquid(SDL_Rect start, SDL_Rect end, std::string liquidName, int timeDelay_);

    void Reset();
    void Update(const Trap& trap);
    void Update();

    // Members
    SDL_Rect startPos;
    SDL_Rect endPos;
    SDL_Rect nowPos;
    std::string liquidClass;

protected:
    int timeDelay;
    int time;
    bool started; // To track if the swelling has started
};

#endif // SWELLINGLIQUID_H
