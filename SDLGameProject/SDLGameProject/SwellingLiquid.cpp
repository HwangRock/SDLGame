#include "SDL.h"
#include <string>

class SwellingLiquid
{
public:
	SDL_Rect startPos;
	SDL_Rect endPos;

	SDL_Rect nowPos;

	std::string liquidClass;

	SwellingLiquid(SDL_Rect start,SDL_Rect end, std::string liquidName,int timeDelay_)
	{
		startPos = start;
		endPos = end;
		liquidClass = liquidName;
		timeDelay=timeDelay_;
		Reset();
	}
	void Reset()
	{
		time = 0;
		nowPos = startPos;
	}
	void Update()
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
protected:
	int timeDelay;
	int time;
};