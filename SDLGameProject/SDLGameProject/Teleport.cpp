#include "Teleport.h"

Teleport_bi::Teleport_bi
(SDL_Rect Lport_pos, SDL_Rect Rport_pos)
{
	Lport_pos_ = Lport_pos;
	Rport_pos_ = Rport_pos;
	Reset();
}

void Teleport_bi::Reset() {
	Lport_passanger_ = "no one";
	Rport_passanger_ = "no one";
	Lport_activated_ = false;
	Rport_activated_ = false;

	Lport_activating_area_.x = Lport_pos_.x + (Lport_pos_.w / 3);
	Lport_activating_area_.y = Lport_pos_.y + (Lport_pos_.h / 3);
	Lport_activating_area_.w = Lport_pos_.w / 3;
	Lport_activating_area_.h = Lport_pos_.h / 3;

	Rport_activating_area_.x = Rport_pos_.x + (Rport_pos_.w / 3);
	Rport_activating_area_.y = Rport_pos_.y + (Rport_pos_.h / 3);
	Rport_activating_area_.w = Rport_pos_.w / 3;
	Rport_activating_area_.h = Rport_pos_.h / 3;
}