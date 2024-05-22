#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include "Box.h"
#include "Stage.h"

Box::Box(SDL_Rect pos) {
	box_pos = pos;
}

void Box::Update(double timestep_s) {

	v[1] += 0.189f; // Gravity
	for (const Terrain& wall : walls)
	{
		if (SDL_HasIntersection(&box_pos, &wall.pos))
		{
			BlockMoving(wall.pos);
		}
	}
	box_pos.y += v[1];
}

void Box::Reset() {
	v[0] = 0;
	v[1] = 0;
}

void Box::BlockMoving(SDL_Rect obst) {
	if (box_pos.y + box_pos.h > obst.y + 10 &&
		box_pos.y < obst.y + obst.h - 10)
	{
		//벽왼쪽에 있음
		if (box_pos.x < obst.x + obst.w / 2)
		{
			//pos.x = min(pos.x, obst.x - pos.w);
			box_pos.x = obst.x - box_pos.w;
		}
		//벽 오른쪽에 있음
		else if (box_pos.x + box_pos.w > obst.x)
		{
			//pos.x = max(pos.x, obst.x + obst.w);
			box_pos.x = obst.x + obst.w;
		}

	}
	else
	{
		if (box_pos.y + box_pos.h <= obst.y + obst.h / 2)
		{
			// 벽 위에 있음
			//pos.y = obst.y - pos.h;
			box_pos.y = obst.y - box_pos.h + 1.0f;
			//pos.y = std::min(obst.y - pos.h,pos.y);
			v[1] = 0;
		}
		else
		{
			// 벽 아래에 있음
			//pos.y = obst.y + obst.h;
			box_pos.y = obst.y + obst.h > box_pos.y ? obst.y + obst.h : box_pos.y;
			//pos.y = std::max(obst.y + obst.h, pos.y);
			v[1] = 0;
		}
	}
}
