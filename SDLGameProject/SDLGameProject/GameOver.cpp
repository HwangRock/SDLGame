#pragma once
#include "SDL.h"
#include "Game.h"
#include "GameFinish.cpp"

class Over : public GameFinish
{
public:
	Over();
	~Over();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:


};


