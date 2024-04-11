#include "func.h"
#include <windows.h>
#include<string>
#include<vector>
#include "SDL_image.h"

double g_elapsed_time_ms;


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
class Pet
{

};

class Dog :Pet 
{
public:
	Dog(int x, int y)
	{
		dogPos.x = x;
		dogPos.y = y;
		dogPos.w = 100;
		dogPos.h = 100;
	}
	void Draw() 
	{
		SDL_RenderCopy(g_renderer,dogTexture,&dogRect,&dogPos);
		SDL_RenderPresent(g_renderer);	
	}
	SDL_Rect dogPos;
};

class Cat :Pet
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
		SDL_RenderPresent(g_renderer);
	}
	SDL_Rect pos;
};
#pragma endregion

Dog dog(100, 100);
Cat cat(200, 200);

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
		SDL_RenderPresent(g_renderer);
	}
	SDL_Rect wallPos;

};
Wall wall1(300, 100, 20, 100);
Wall wall2(50, 100, 20, 100);
std::vector<Wall>walls = { wall1,wall2 };

#pragma region Init
void InitGame()
{

	g_flag_running = true;
	g_elapsed_time_ms = 0;

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
	wallTexture= SDL_CreateTextureFromSurface(g_renderer, surface_wall);
	SDL_FreeSurface(surface_wall);
	wallRect = { 0,0,680,808 };
}
#pragma endregion


#pragma region Update
void Update()
{
	//DOG MOVING
	dogInput = dog_input[dog_input.size() - 1];
	for (int i = 0; i < dog_input.size(); i++)
	{
		std::cout << dog_input[i] << " ";
	}
	std::cout << "\t";

	//left
	if (dogInput == 1) { dog.dogPos.x -= 10; }
	//right
	else if (dogInput == 2) { dog.dogPos.x += 10; }
	//up
	else if (dogInput == 3) { dog.dogPos.y -= 10; }



	//CAT MOVING
	catInput = cat_input[cat_input.size() - 1];
	for (int i = 0; i < cat_input.size(); i++)
	{
		std::cout << cat_input[i] << " ";
	}
	std::cout << "\n";
	//left
	if (catInput == 1) { cat.pos.x -= 10; }
	//right
	else if (catInput == 2) { cat.pos.x += 10; }
	//up
	else if (catInput == 3) { cat.pos.y -= 10; }
	


	//Limit
	if (dog.dogPos.x > win_w - dog.dogPos.w)
	{
		dog.dogPos.x = win_w - dog.dogPos.w;
	}
	else if (dog.dogPos.x < 0)
	{
		dog.dogPos.x = 0;
	}

	if (cat.pos.x > win_w - cat.pos.w)
	{
		cat.pos.x = win_w - cat.pos.w;
	}
	else if (cat.pos.x < 0)
	{
		cat.pos.x = 0;
	}

	for (int i = 0; i < walls.size(); i++)
	{
		if (dog.dogPos.x + dog.dogPos.w > walls[i].wallPos.x &&
			dog.dogPos.x + dog.dogPos.w < walls[i].wallPos.x + walls[i].wallPos.w)
		{
			dog.dogPos.x = walls[i].wallPos.x - dog.dogPos.w;
		}
		else if (dog.dogPos.x < walls[i].wallPos.x + walls[i].wallPos.w &&
				dog.dogPos.x > walls[i].wallPos.x)
		{
			dog.dogPos.x = walls[i].wallPos.x + walls[i].wallPos.w;
		}

	}



	g_elapsed_time_ms += 33;

}
#pragma endregion


#pragma region Render
void Render() 
{
	SDL_RenderClear(g_renderer);


	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	
	dog.Draw();
	cat.Draw();
	wall1.Draw();
	wall2.Draw();

	SDL_RenderPresent(g_renderer);
}
#pragma endregion


#pragma region Handle Event
void HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

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
			// 마우스 왼쪽 버튼이 눌려 졌을 때.
			break;

		default:
			break;
		}
	}

}
#pragma endregion



void ClearGame()
{
	SDL_DestroyTexture(dogTexture);
	SDL_DestroyTexture(catTexture);

}