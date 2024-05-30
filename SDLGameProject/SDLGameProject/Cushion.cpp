#include "Cushion.h"

Cushion::Cushion(SDL_Rect pos)
{
	cushion_pos = pos;
	cushion_blockPos = { pos.x,pos.y+surplus,pos.w,pos.h-2*surplus };
}