#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Teleport_bi
{
public:

	SDL_Rect Lport_pos_;
	SDL_Rect Rport_pos_;

	SDL_Rect Lport_activating_area_;
	SDL_Rect Rport_activating_area_;

	std::string Lport_passanger_;
	std::string Rport_passanger_;

	bool Lport_activated_;
	bool Rport_activated_;

	Teleport_bi( SDL_Rect Lport_pos, SDL_Rect Rport_pos);

	void Reset();



protected:



};