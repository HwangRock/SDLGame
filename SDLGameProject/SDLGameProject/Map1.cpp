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




		Terrain* floor7 = new Terrain(250, 110, 200, 15);//up
		Terrain* floor8 = new Terrain(250, 175 + 9, 200, 16);//down

		Terrain* default1 = new Terrain(0, 0, 30, win_h);
		Terrain* default2 = new Terrain(0, 0, win_w, 30);
		Terrain* default3 = new Terrain(win_w - 30, 0, 30, win_h);
		Terrain* default4 = new Terrain(0, win_h - 30, win_w, 30);

		walls =
		{
			*floor1,*floor2,*floor3,*floor4,*floor5,*floor6,*floor7,*floor8,
			*default1,*default2,*default3,*default4,
		};


		//Button
		Button* btn1 = new Button(2, 1,
			{ {650, 375,20,20},{1150,660,20,20} },
			{ { 950, 620,200,25 } },
			{ { 950, 470,200,25 } },
			{ { 950, 620,200,25 } });
		Button* btn2 = new Button(1, 1,
			{ { 400, 150,20,20 } },
			{ { 50, 400,150,25 } },
			{ { 50, 175,150,25 } },
			{ { 50, 400,150,25 } });
		buttons = { *btn1,*btn2 };

		
		/*
		SDL_Rect blind1 = { 550, 570, 300, 25 };
		SDL_Rect blind2 = { 550, 650, 300, 25 };

		blinds = { blind1,blind2 };  */ 

		LiquidWall* lwall1 = new LiquidWall({ 250,125,200,15 }, "down");//up
		LiquidWall* lwall2 = new LiquidWall({ 250,175,200,9 }, "up");//down
		liquidWalls = { *lwall1,*lwall2 };

		SDL_Rect laisle1 = { 250,150,200,30 };
		liquidAisles = { laisle1 };

		ClimbWall* cwall = new ClimbWall({ 13,31,19,394 });
		climbWalls = { *cwall };

		Box* box1 = new Box({ 400, 580, 50, 50 });
		boxs = { *box1 };
		cannon = { };
		mis = {};
		bone = {};
		fish = {};
		keys = {};
		fadefloors = {};
		cushions = {};


		Water* water1 = new Water({ 200,650,405,35 });
		Water* water2 = new Water({ 750,75,198,23 });
		water = { *water1, *water2 };

		Milk* milk1 = new Milk({ 952,663,198,23 });
		Milk* milk2 = new Milk({ 750,155,198,23 });
		milk = { *milk1,*milk2 };

		Choco* choco1 = new Choco({ 0,0,0,0 });
		choco = { *choco1 };

		goal = { {1100,100,50,100} };
		start={600,300,50,80};
		//start = { 1000,100,50,100 };
		//바로 클리어 장면 볼 수 있는 start 위치.
	}
protected:

};



