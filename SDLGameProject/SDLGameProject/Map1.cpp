#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>

class Map1 : public StageInterface
{

public:

	Map1() {};
	~Map1() {};

	virtual void SetVar()
	{
		//Terrain
		Terrain* floor1 = new Terrain(200, 175, 50, 25);
		Terrain* floor2 = new Terrain(450, 125, 25, 75);
		Terrain* floor3 = new Terrain(450, 175, win_w - 450, 25);
		Terrain* floor4 = new Terrain(750, 100, 200, 25);
		Terrain* floor5 = new Terrain(0, 425, 850, 25);
		Terrain* floor6 = new Terrain(550, 575, 300, 25);




		Terrain* default1 = new Terrain(0, 0, 30, win_h);
		Terrain* default2 = new Terrain(0, 0, win_w, 30);
		Terrain* default3 = new Terrain(win_w - 30, 0, 30, win_h);
		Terrain* default4 = new Terrain(0, win_h - 30, win_w, 30);

		walls =
		{
			*floor1,*floor2,*floor3,*floor4,*floor5,*floor6,
			*default1,*default2,*default3,*default4,
		};


		//Button
		Button* btn1 = new Button(2, 1,
			{ {650, 375,20,20},{1150,660,20,20} },
			{ { 950, 600,200,25 } },
			{ { 950, 470,200,25 } },
			{ { 950, 600,200,25 } });
		Button* btn2 = new Button(1, 1,
			{ { 400, 150,20,20 } },
			{ { 50, 400,150,25 } },
			{ { 50, 175,150,25 } },
			{ { 50, 400,150,25 } });
		buttons = { *btn1,*btn2 };


		SDL_Rect blind1 = { 750, 80, 200, 30 };
		SDL_Rect blind2 = { 750 ,170,200,30 };
		SDL_Rect blind3 = { 550, 570, 300, 25 };
		SDL_Rect blind4 = { 550, 650, 300, 25 };

		blinds = { blind1,blind2,blind3,blind4 };

		LiquidWall* lwall1 = new LiquidWall({ 250,125,200,25 }, "down");
		LiquidWall* lwall2 = new LiquidWall({ 250,175,200,25 }, "up");
		liquidWalls = { *lwall1,*lwall2 };

		SDL_Rect laisle1 = { 250,150,200,30 };
		liquidAisles = { laisle1 };
		

		ClimbWall* cwall = new ClimbWall({ 0,0,50,450 });
		climbWalls = {*cwall};

		goal = { 1100,100,50,100 };
		start={50,600,50,80};
	}
protected:

};



