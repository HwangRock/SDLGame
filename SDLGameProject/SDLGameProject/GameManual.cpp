#pragma once
#include "SDL.h"
#include "Game.h"

class Manual : public PhaseInterface
{
public:
	Manual()
	{

	
	};
	~Manual();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	
};


