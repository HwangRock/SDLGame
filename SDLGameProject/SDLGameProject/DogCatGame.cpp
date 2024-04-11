#include <iostream>
#include<string>
#include<vector>
#include <windows.h>
#include<algorithm>

#include "DogCatGame.h" 
#include "SDL_image.h"
#include "G2W.h"
#include "math.h"

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern float g_timestep_s;


//Innput
int catInput;
int dogInput;
int catKeyUp;
int dogKeyUp;
int catKeyDown;
int dogKeyDown;
std::vector<int> cat_input;
std::vector<int> dog_input;
int win_w, win_h;

//Sprite
SDL_Rect dogRect;
SDL_Rect catRect;
SDL_Texture* catTexture;
SDL_Texture* dogTexture;

SDL_Texture* wallTexture;
SDL_Rect wallRect;

#pragma region Dog and Cat Class



class Wall
{
public:
	Wall(int x, int y, int w, int h)
	{
		wallPos.x = x;
		wallPos.y = y;
		wallPos.w = w;
		wallPos.h = h;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &wallPos);
	}
	SDL_Rect wallPos;

};
Wall wall1(300, 100, 20, 100);
Wall wall2(50, 100, 20, 100);
Wall wall3(400, 200, 20, 500);
Wall wall4(100, 300, 600, 200);
std::vector<Wall>walls = { wall1,wall2,wall3,wall4 };

class Snack
{
public:
	Snack(int x, int y,bool isBone) 
	{
		if (isBone) 
		{ 
			bonePos.x = x; bonePos.y = y; 
			bonePos.w = 10; bonePos.h = 5;
		}
		else 
		{
			fishPos.x = x; fishPos.y = y;
			fishPos.w = 10; fishPos.h = 5;
		}
	
	}
	void Draw() 
	{
		if (isBone) { SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &bonePos); }
		else { SDL_RenderCopy(g_renderer, wallTexture, &wallRect, &fishPos); }
	}
	bool isBone;
	SDL_Rect bonePos;
	SDL_Rect fishPos;
};

class Pet
{
public:
	SDL_Rect pos;
};

class Dog : public Pet
{
public:
	Dog(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		pos.w = 50;
		pos.h = 50;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, dogTexture, &dogRect, &pos);
	}
	void Update()
	{
		// 벽 감지
		for (const Wall& wall : walls)
		{
			if (SDL_HasIntersection(&pos, &wall.wallPos))
			{

				if (pos.y + pos.h > wall.wallPos.y+5 &&
					pos.y < wall.wallPos.y + wall.wallPos.h-5)
				{
					//left
					if (pos.x < wall.wallPos.x + wall.wallPos.w / 2)
					{
						pos.x = min(pos.x, wall.wallPos.x - pos.w);
					}
					//right
					else if (pos.x + pos.w > wall.wallPos.x)
					{
						pos.x = max(pos.x, wall.wallPos.x + wall.wallPos.w);

					}

				}
				else 
				{
					if (pos.y + pos.h <= wall.wallPos.y+wall.wallPos.h/2)
					{
						// 벽 위에 있음
						pos.y = wall.wallPos.y - pos.h;
					}
					else 
					{
						// 벽 아래에 있음
						pos.y = wall.wallPos.y + wall.wallPos.h;
					}
				}	
			}
		}

	}
};

class Cat : public Pet
{
public:
	Cat(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		pos.w = 80;
		pos.h = 80;
	}
	void Draw()
	{
		SDL_RenderCopy(g_renderer, catTexture, &catRect, &pos);
	}
	void Update()
	{
		// 벽 감지
		for (const Wall& wall : walls)
		{
			if (SDL_HasIntersection(&pos, &wall.wallPos))
			{

				if (pos.y + pos.h > wall.wallPos.y + 5 &&
					pos.y < wall.wallPos.y + wall.wallPos.h - 5)
				{
					//left
					if (pos.x < wall.wallPos.x + wall.wallPos.w / 2)
					{
						pos.x = min(pos.x, wall.wallPos.x - pos.w);
					}
					//right
					else if (pos.x + pos.w > wall.wallPos.x)
					{
						pos.x = max(pos.x, wall.wallPos.x + wall.wallPos.w);

					}

				}
				else
				{
					if (pos.y + pos.h <= wall.wallPos.y + wall.wallPos.h / 2)
					{
						// 벽 위에 있음
						pos.y = wall.wallPos.y - pos.h;
					}
					else
					{
						// 벽 아래에 있음
						pos.y = wall.wallPos.y + wall.wallPos.h;
					}
				}
			}
		}

	}

};
#pragma endregion

Dog dog(200, 200);
Cat cat(100, 100);


//InitGame
DogCatGame::DogCatGame()
{
	g_flag_running = true;

	catInput = 0;
	dogInput = 0;
	catKeyDown = 0;
	dogKeyDown = 0;
	catKeyUp = 0;
	dogKeyUp = 0;

	cat_input.push_back(0);
	dog_input.push_back(0);

	SDL_GetWindowSize(g_window, &win_w, &win_h);

	//Drawing//////////////////////////////
	//Dog
	SDL_Surface* g_surface_dog = IMG_Load("../Resources/dog_.png");
	dogTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_dog);
	SDL_FreeSurface(g_surface_dog);
	dogRect = { 0,0,141,141 };



	//Cat
	SDL_Surface* g_surface_cat = IMG_Load("../Resources/cat_.png");
	catTexture = SDL_CreateTextureFromSurface(g_renderer, g_surface_cat);
	SDL_FreeSurface(g_surface_cat);
	catRect = { 0,0,90,90 };


	//Wall
	SDL_Surface* surface_wall = IMG_Load("../Resources/sky.jpg");
	wallTexture = SDL_CreateTextureFromSurface(g_renderer, surface_wall);
	SDL_FreeSurface(surface_wall);
	wallRect = { 0,0,680,808 };



	// Ball
	{
		SDL_Surface* ball_surface = IMG_Load("../Resources/ball.png");
		ball_src_rectangle_.x = 0;
		ball_src_rectangle_.y = 0;
		ball_src_rectangle_.w = ball_surface->w;
		ball_src_rectangle_.h = ball_surface->h;

		ball_texture_ = SDL_CreateTextureFromSurface(g_renderer, ball_surface);
		SDL_FreeSurface(ball_surface);
	}



	// Initialize ball pointers
	for (int i = 0; i < MAX_BALL_NUM; i++)
	{
		balls_[i] = 0;
	}

	num_of_balls_ = 0;

	mouse_win_x_ = 0;
	mouse_win_y_ = 0;

	AddNewBall();
}



//ClearGame(Game 종료시 실행)
DogCatGame::~DogCatGame()
{
	// Delete balls
	for (int i = 0; i < MAX_BALL_NUM; i++)
	{
		if (balls_[i] != 0)
			delete balls_[i];

		balls_[i] = 0;
	}

	num_of_balls_ = 0;


	SDL_DestroyTexture(ball_texture_);
	SDL_DestroyTexture(dogTexture);
	SDL_DestroyTexture(catTexture);
}


void
DogCatGame::AddNewBall()
{
	if (num_of_balls_ == MAX_BALL_NUM) return;

	// Create new Ball
	Ball* ball = new Ball(0.11f, &room_);

	// Add to the list
	balls_[num_of_balls_] = ball;

	// Increase Num
	num_of_balls_++;

}


void
DogCatGame::Update()
{

	// Update balls
	for (int i = 0; i < num_of_balls_; i++)
	{
		balls_[i]->Update(g_timestep_s);
	}

	//DOG MOVING
	dogInput = dog_input[dog_input.size() - 1];

	//left
	if (dogInput == 1) { dog.pos.x -= 10; }
	//right
	else if (dogInput == 2) { dog.pos.x += 10; }
	//up
	else if (dogInput == 3) { dog.pos.y -= 5; }
	//down
	else if (dogInput == 4) { dog.pos.y += 5; }



	//CAT MOVING
	catInput = cat_input[cat_input.size() - 1];
	//left
	if (catInput == 1) 
	{ cat.pos.x -= 10;  }
	//right
	else if (catInput == 2) 
	{ cat.pos.x += 10; 
	}
	//up
	else if (catInput == 3) 
	{ cat.pos.y -= 10; 
	}



	dog.Update();
	cat.Update();
}

void
DogCatGame::Render()
{
	//Background
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	
	//Dog and Cat
	dog.Draw();
	cat.Draw();



	for(Wall wall : walls)
	{
		wall.Draw();
	}



	// Room
	{
		SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);

		// Left Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
			G2W_Y(0),
			G2W_X(room_.left_wall_x()),
			G2W_Y(room_.height()));


		// Right Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.right_wall_x()),
			G2W_Y(0),
			G2W_X(room_.right_wall_x()),
			G2W_Y(room_.height()));

		// Top Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
			G2W_Y(room_.height()),
			G2W_X(room_.right_wall_x()),
			G2W_Y(room_.height()));

		// Bottom Wall
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.left_wall_x()),
			G2W_Y(0),
			G2W_X(room_.right_wall_x()),
			G2W_Y(0));

		// Fence
		SDL_RenderDrawLine(g_renderer, G2W_X(room_.vertiacal_fence_pos_x()),
			G2W_Y(0),
			G2W_X(room_.vertiacal_fence_pos_x()),
			G2W_Y(room_.ground_height() + room_.vertiacal_fence_height()));
	}


	// Balls
	for (int i = 0; i < num_of_balls_; i++)
	{
		Ball* ball = balls_[i];

		int ball_win_x = G2W_X(balls_[i]->pos_x());
		int ball_win_y = G2W_Y(balls_[i]->pos_y());

		double win_radius = G2W_Scale * balls_[i]->radius();

		SDL_Rect dest_rect;
		dest_rect.w = (int)(2 * win_radius);
		dest_rect.h = (int)(2 * win_radius);
		dest_rect.x = (int)(ball_win_x - win_radius);
		dest_rect.y = (int)(ball_win_y - win_radius);

		SDL_RenderCopy(g_renderer, ball_texture_, &ball_src_rectangle_, &dest_rect);
	}


	/*
	// Draw the Guide Line 
	if (num_of_balls_ > 0)
	{
		SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 100);
		SDL_RenderDrawLine(g_renderer, G2W_X(balls_[num_of_balls_ - 1]->pos_x()),
			G2W_Y(balls_[num_of_balls_ - 1]->pos_y()),
			mouse_win_x_,
			mouse_win_y_);
	}
	*/

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void DogCatGame::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				dogKeyDown = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				dogKeyDown = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				dogKeyDown = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				dogKeyDown = 4;
			}

			if (dogKeyDown != 0)
			{
				for (int i = dog_input.size() - 1; i >= 0; i--)
				{
					if (dog_input[i] != dogKeyDown && dogKeyDown != 0)
					{
						if (i == 0) { dog_input.push_back(dogKeyDown); }
					}
					else { break; }
				}
				dogKeyDown = 0;
			}

			if (event.key.keysym.sym == SDLK_a)
			{
				catKeyDown = 1;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				catKeyDown = 2;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				catKeyDown = 3;
			}

			if (catKeyDown != 0)
			{
				for (int i = cat_input.size() - 1; i >= 0; i--)
				{
					if (cat_input[i] != catKeyDown && catKeyDown != 0)
					{
						if (i == 0) { cat_input.push_back(catKeyDown); }
					}
					else { break; }
				}
				catKeyDown = 0;
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				dogKeyUp = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				dogKeyUp = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				dogKeyUp = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				dogKeyUp = 4;
			}

			if (dogKeyUp != 0)
			{
				for (int i = dog_input.size() - 1; i >= 0; i--)
				{
					if (dog_input[i] == dogKeyUp)
					{
						dog_input.erase(dog_input.begin() + i);
						dogKeyUp = 0;
						break;
					}

				}
			}


			if (event.key.keysym.sym == SDLK_a)
			{
				catKeyUp = 1;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				catKeyUp = 2;
			}
			else if (event.key.keysym.sym == SDLK_w)
			{
				catKeyUp = 3;
			}

			if (catKeyUp != 0)
			{
				for (int i = cat_input.size() - 1; i >= 0; i--)
				{
					if (cat_input[i] == catKeyUp)
					{
						cat_input.erase(cat_input.begin() + i);
						catKeyUp = 0;
						break;
					}

				}
			}

			break;
		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				// Get the cursor's x position.
				mouse_win_x_ = event.button.x;
				mouse_win_y_ = event.button.y;


				double mouse_game_x = W2G_X(mouse_win_x_);
				double mouse_game_y = W2G_Y(mouse_win_y_);



				// Luanch
				if (num_of_balls_ > 0)
				{
					Ball* ball = balls_[num_of_balls_ - 1];

					// Guide Line Vector
					double guide_line_x = mouse_game_x - ball->pos_x();
					double guide_line_y = mouse_game_y - ball->pos_y();

					// Lauching Force
					double launcing_force_x = 8.0 * guide_line_x;
					double launcing_force_y = 8.0 * guide_line_y;

					// Launch
					ball->Launch(launcing_force_x, launcing_force_y);


					// Add a new ball for the next
					AddNewBall();
				}
			}



		case SDL_MOUSEMOTION:
		{
			// Get the cursor's x position.
			mouse_win_x_ = event.button.x;
			mouse_win_y_ = event.button.y;



		}
		break;

		default:
			break;
		}
	}
}

