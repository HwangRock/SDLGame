#include "SwellingLiquid.h"

SwellingLiquid::SwellingLiquid(SDL_Rect start, SDL_Rect end, std::string liquidName, int timeDelay_)
{
    startPos = start;
    endPos = end;
    liquidClass = liquidName;
    timeDelay = timeDelay_;
    started = false; // Initially, swelling doesn't start
    Reset();
}

void SwellingLiquid::Reset()
{
    time = 0;
    nowPos = startPos;
    started = false; // Reset the started state
}

void SwellingLiquid::Update(const Trap& trap)
{
    // Start swelling if trapActivated is true or if already started
    if (trap.trapActivated || started)
    {
        std::cout << "trap activate\n";
        started = true; // Ensure it continues even if trapActivated becomes false later
        if (nowPos.h != endPos.h)
        {
            if (time % timeDelay == 0)
            {
                nowPos.h++;
                nowPos.y--;
            }
            time++;
        }
    }
}

void SwellingLiquid::Update()
{
    if (nowPos.h != endPos.h)
    {
        if (time % timeDelay == 0)
        {
            nowPos.h++;
            nowPos.y--;
        }
        time++;
    }
}