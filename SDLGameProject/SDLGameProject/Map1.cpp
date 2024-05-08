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
		Terrain* floorUp1 = new Terrain(150, 200, 50, 25);
		Terrain* floorUp2 = new Terrain(400, 200, 800, 25);
		Terrain* floorDown = new Terrain(0, 500, 600, 25);

		Terrain* Wall = new Terrain(400 - 25, 150, 25, 50);
		Terrain* Scaffolding2 = new Terrain(600, 100, 100, 25);
		Terrain* Scaffolding3 = new Terrain(500, 600, 100, 25);

		Terrain* default1 = new Terrain(0, 680, 1000, 20);
		Terrain* default2 = new Terrain(0, 0, 1000, 20);
		Terrain* default3 = new Terrain(0, 0, 20, 700);
		Terrain* default4 = new Terrain(980, 0, 20, 700);

		walls =
		{
			*floorUp1,*floorUp2,*floorDown,*Wall,
			*Scaffolding2,*Scaffolding3,
			*default1,*default2,*default3,*default4,
		};


		//Button
		Button* btn1 = new Button(2, 2,
			{ {500, 480,20,20},{900,650,20,20} },
			{ { 700,600,150,25 },{100,400,150,25} },
			{ { 700, 500,150,25 },{100,300,150,25} },
			{ { 700, 600,150, 25 },{100,400,150,25} });
		buttons = { *btn1 };


		SDL_Rect blind1 = { 100,650,30,30 };
		SDL_Rect blind2 = { 200,650,30,30 };
		blinds = { blind1,blind2 };

		LiquidWall* lwall1 = new LiquidWall({ 200,150,200,25 }, "down");
		LiquidWall* lwall2 = new LiquidWall({ 200,200,200,25 }, "up");
		liquidWalls = { *lwall1,*lwall2 };

		SDL_Rect laisle1 = { 200,175,200,30 };
		liquidAisles = { laisle1 };
		

		ClimbWall* cwall = new ClimbWall({ 25,100,30,400 });
		climbWalls = {*cwall};

		goal = { 800,50,50,100 };
		start={50,600,50,80};
	}
protected:

};



