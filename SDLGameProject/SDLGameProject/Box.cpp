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

	v[1] += 0.1f; // Gravity
	for (const Terrain& wall : walls)
	{
		if (SDL_HasIntersection(&box_pos, &wall.pos))
		{
			BlockMoving(wall.pos);
		}
	}
	for (Button btn : buttons)
	{
		for (int i = 0; i < btn.scaffold_.size(); i++)
		{
			if (SDL_HasIntersection(&box_pos, &btn.scaffold_[i]))
			{
				BlockMoving(btn.scaffold_[i]);
			}
		}
	}
	for (Liquid l : liquid)
	{
		if (SDL_HasIntersection(&box_pos, &l.wallPos))
		{
			BlockMoving(l.wallPos);
		}
	}
	//박스끼리 부딪히게?
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
			box_pos.x = obst.x - box_pos.w;
		}
		//벽 오른쪽에 있음
		else if (box_pos.x + box_pos.w > obst.x)
		{
			box_pos.x = obst.x + obst.w;
		}

	}
	else
	{
		if (box_pos.y + box_pos.h <= obst.y + obst.h / 2)
		{
			// 벽 위에 있음
			box_pos.y = obst.y - box_pos.h + 1.0f;
			v[1] = 0;
		}
		else
		{
			// 벽 아래에 있음
			box_pos.y = obst.y + obst.h > box_pos.y ? obst.y + obst.h : box_pos.y;
			v[1] = 0;
		}
	}
}
