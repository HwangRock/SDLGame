#include "Pet.h"
#include "SDL_image.h"
#include <iostream>


Pet::Pet(double x, double y, double size)
{
	size_ = size;

	mass_ = 2; // 2kg
	coeff_of_restitution_ = 0.7;

	pos_[0] = x;
	pos_[1] = y;

	pos.x = x;
	pos.y = y;
	pos.w = size;
	pos.h = size;


	Reset();
}

void
Pet::Reset()
{
	v[0] = 0;
	v[1] = 0;

	jumping = false;
}


void
Pet::Update(double timestep_s, std::vector<Terrain>& walls)
{
	double dt = timestep_s;	// seconds



	// 벽 감지
	for (const Terrain& wall : walls)
	{
		if (SDL_HasIntersection(&pos, &wall.pos))
		{

			if (pos.y + pos.h > wall.pos.y + 5 &&
				pos.y < wall.pos.y + wall.pos.h - 5)
			{
				//벽왼쪽에 있음
				if (pos.x < wall.pos.x + wall.pos.w / 2)
				{
					//pos.x = min(pos.x, wall.pos.x - pos.w);
					pos.x = wall.pos.x - pos.w;
				}
				//벽 오른쪽에 있음
				else if (pos.x + pos.w > wall.pos.x)
				{
					//pos.x = max(pos.x, wall.pos.x + wall.pos.w);
					pos.x = wall.pos.x + wall.pos.w;
				}

			}
			else
			{
				if (pos.y + pos.h <= wall.pos.y + wall.pos.h / 2)
				{
					// 벽 위에 있음
					pos.y = wall.pos.y - pos.h;
				}
				else
				{
					// 벽 아래에 있음
					pos.y = wall.pos.y + wall.pos.h;
				}
			}


			v[1] = 0;
			jumping = false;
		}
	}



	/*
	// 가속도
	double a[2];
	a[0] = 0;
	a[1] = room_->gravitational_acc_y();// Gravity

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];


	// Collision with Ground
	if (p_[1] - radius_ < room_->ground_height() && v_[1] < 0)
	{
		p_[1] = radius_ + room_->ground_height();

		v_[1] = -1 * v_[1];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Ceilling
	else if (p_[1] + radius_ > room_->height() && v_[1] > 0)
	{
		p_[1] = room_->height() - radius_;

		v_[1] = -1 * v_[1];

		// Coefficient of restitution
		v_[1] = coeff_of_restitution_ * v_[1];
	}

	// Collision with Left Wall
	if (p_[0] - radius_ < room_->left_wall_x() && v_[0] < 0)
	{
		p_[0] = room_->left_wall_x() + radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	// Collision with Right Wall
	else if (p_[0] + radius_ > room_->right_wall_x() && v_[0] > 0)
	{
		p_[0] = room_->right_wall_x() - radius_;

		v_[0] = -1 * v_[0];

		// Coefficient of restitution
		v_[0] = coeff_of_restitution_ * v_[0];
	}

	//속도 = 이전속도 + 시간(dt) * 가속도;
	v_[0] = v_[0] + dt * a[0];
	v_[1] = v_[1] + dt * a[1];
	*/
}
