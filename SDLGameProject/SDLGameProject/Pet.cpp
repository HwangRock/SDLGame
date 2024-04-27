#include "Pet.h"
#include "SDL_image.h"
#include <iostream>


Pet::Pet(double x, double y,bool isDog)
{
	size_ = 30;

	isDog_ = isDog;

	mass_ = 2; // 2kg
	coeff_of_restitution_ = 0.7;

	pos_[0] = x;
	pos_[1] = y;

	pos.x = x;
	pos.y = y;
	pos.w = 30;
	pos.h = 30;


	Reset();
}

void
Pet::Reset()
{
	v[0] = 0;
	v[1] = 0;

	nowInput = 0;
	keyDownNum = 0;
	keyUpNum = 0;
	inputs.push_back(0);

	jumping = false;
}


void
Pet::Update(double timestep_s, std::vector<Terrain>& walls,std::vector<Button>&buttons)
{
	double dt = timestep_s;	// seconds


	//MOVING/////////////////////////////////////////////////

	v[1] += gravity;

	nowInput = inputs[inputs.size() - 1];
	//left
	if (nowInput == 1) { pos.x -= 2; }
	//right
	else if (nowInput == 2) { pos.x += 2; }
	//up
	pos.y += v[1];




	//MOVING LIMIT//////////////////////////////////////////////////
	// �� ����
	for (const Terrain& wall : walls)
	{
		if (SDL_HasIntersection(&pos, &wall.pos))
		{
			//����)���� height�� �ʹ� ������ ����� �۵����� ���� �� �����ϴ�..
			if (pos.y + pos.h > wall.pos.y + 10 &&
				pos.y < wall.pos.y + wall.pos.h - 10)
			{
				//�����ʿ� ����
				if (pos.x < wall.pos.x + wall.pos.w / 2)
				{
					//pos.x = min(pos.x, wall.pos.x - pos.w);
					pos.x = wall.pos.x - pos.w;
				}
				//�� �����ʿ� ����
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
					// �� ���� ����
					pos.y = wall.pos.y - pos.h;
					v[1] = 0;
					jumping = false;
				}
				else
				{
					// �� �Ʒ��� ����
					//pos.y = wall.pos.y + wall.pos.h;
					pos.y = std::max(wall.pos.y + wall.pos.h, pos.y);
				}
			}

		}
	}
	
	//PRESS BUTTON/////////////////////////////////////////////////////////////
	for (Button& btn : buttons)
	{
		//�Լ��� ���� �ʿ�
		for (int i = 0; i < btn.scaffold_.size(); i++)
		{
			if (SDL_HasIntersection(&pos, &btn.scaffold_[i]))
			{
				//����)���� height�� �ʹ� ������ ����� �۵����� ���� �� �����ϴ�..
				if (pos.y + pos.h > btn.scaffold_[i].y + 10 &&
					pos.y < btn.scaffold_[i].y + btn.scaffold_[i].h - 10)
				{
					//�����ʿ� ����
					if (pos.x < btn.scaffold_[i].x + btn.scaffold_[i].w / 2)
					{
						//pos.x = min(pos.x, wall.pos.x - pos.w);
						pos.x = btn.scaffold_[i].x - pos.w;
					}
					//�� �����ʿ� ����
					else if (pos.x + pos.w > btn.scaffold_[i].x)
					{
						//pos.x = max(pos.x, wall.pos.x + wall.pos.w);
						pos.x = btn.scaffold_[i].x + btn.scaffold_[i].w;
					}

				}
				else
				{
					if (pos.y + pos.h <= btn.scaffold_[i].y + btn.scaffold_[i].h / 2)
					{
						// �� ���� ����
						pos.y = btn.scaffold_[i].y - pos.h;
						v[1] = 0;
						jumping = false;
					}
					else
					{
						// �� �Ʒ��� ����
						//pos.y = btn.scaffold_[i].y + btn.scaffold_[i].h;
						pos.y = std::max(btn.scaffold_[i].y + btn.scaffold_[i].h, pos.y);
					}
				}

			}
		}




		for (int i = 0; i < btn.buttonPos.size(); i++)
		{
			if (SDL_HasIntersection(&pos, &btn.buttonPos[i]))
			{
				if (btn.isPressed == false)
				{
					std::cout << "pressed\n";
					btn.SetPress(true);
					btn.Update();

				}
			}
			else
			{
				std::cout << "not pressed\n";
				btn.SetPress(false);
				btn.Update();
			}
		}
		
	}





	/*
	// ���ӵ�
	double a[2];
	a[0] = 0;
	a[1] = room_->gravitational_acc_y();// Gravity

	// Move
	p_[0] = p_[0] + dt * v_[0];
	p_[1] = p_[1] + dt * v_[1];

	//�ӵ� = �����ӵ� + �ð�(dt) * ���ӵ�;
	v_[0] = v_[0] + dt * a[0];
	v_[1] = v_[1] + dt * a[1];
	*/
}

void
Pet::HandleEvent(SDL_Event event) 
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (isDog_)
		{
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				keyDownNum = 1;
				v[0] = -1.0f;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				keyDownNum = 2;
				v[0] = 1.0f;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				if (jumping == false)
				{
					v[1] = jumpSpeed();
					jumping = true;
				}
			}
		}
		else
		{
			if (event.key.keysym.sym == SDLK_a)
			{
				v[0] = -1.0f; keyDownNum = 1;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				v[0] = 1.0f; keyDownNum = 2;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				if (jumping == false)
				{
					v[1] = jumpSpeed();
					jumping = true;
				}
				keyDownNum = 3;
			}
		}

		if (keyDownNum != 0)
		{
			for (int i = inputs.size() - 1; i >= 0; i--)
			{
				if (inputs[i] != keyDownNum && keyDownNum != 0)
				{
					if (i == 0) { inputs.push_back(keyDownNum); }
				}
				else { break; }
			}
			keyDownNum = 0;
		}
		break;


	case SDL_KEYUP:

		if (isDog_)
		{
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				keyUpNum = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				keyUpNum = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				//dogKeyUp = 3;	
			}
		}
		else
		{
			if (event.key.keysym.sym == SDLK_a)
			{
				keyUpNum = 1;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				keyUpNum = 2;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				//catKeyUp = 3;	
			}
		}
		

		if (keyUpNum != 0)
		{
			for (int i = inputs.size() - 1; i >= 0; i--)
			{
				if (inputs[i] == keyUpNum)
				{
					//dog->v[0] = 0.0f;
					inputs.erase(inputs.begin() + i);
					keyUpNum = 0;
					break;
				}

			}
		}


		break;
	}

	


}
