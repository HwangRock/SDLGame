#include "Teleport.h"

Teleport_bi::Teleport_bi
(
	SDL_Rect Lport_pos,
	SDL_Rect Rport_pos,
	std::string Lport_passanger,
	std::string Rport_passanger,
	bool L_activated,
	bool R_activated
)
{
	Lport_pos_ = Lport_pos;
	Rport_pos_ = Rport_pos;
	Lport_passanger_ = Lport_passanger;
	Rport_passanger_ = Rport_passanger;
	Lport_activated_ = L_activated;
	Rport_activated_ = R_activated;
}