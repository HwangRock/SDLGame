#pragma once
#include "SDL.h"
#include "Game.h"

class ESC : public PhaseInterface
{
public:
	ESC();
	~ESC();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	
};


