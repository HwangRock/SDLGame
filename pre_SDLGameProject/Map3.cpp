#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include "Key.cpp"
#include <vector>

class Map3 : public StageInterface
{

public:

	Map3() {};
	~Map3() {};

	virtual void SetVar()
	{
		Terrain* floor1 = new Terrain(0, 100, 400, 50);
		Terrain* floor2 = new Terrain(0, 200, 400, 50);
		Terrain* floor3 = new Terrain(400, 125, 100, 25);
		Terrain* floor4 = new Terrain(400, 225, 100, 25);
		Terrain* floor5 = new Terrain(650, 175, 200, 25);
		Terrain* floor6 = new Terrain(0, 350, 150, 25);
		Terrain* floor7 = new Terrain(400, 350, win_w - 400, 25);
		Terrain* floor8 = new Terrain(950, 375, win_w - 950, 50);
		Terrain* floor9 = new Terrain(0, 475, 800, 25);
		Terrain* floor10 = new Terrain(950, 500, 200, 25);
		Terrain* floor11 = new Terrain(0, 575, 450, 50);

		Terrain* floor12 = new Terrain(450, 575, 165, 65);
		Terrain* floor13 = new Terrain(675, 575, win_w - 675, win_h - 575);



		Terrain* default1 = new Terrain(0, 0, 30, win_h);
		Terrain* default2 = new Terrain(0, 0, win_w, 30);
		Terrain* default3 = new Terrain(win_w - 30, 0, 30, win_h);
		Terrain* default4 = new Terrain(0, win_h - 30, win_w, 30);
		walls =
		{

			*default1,*default2,*default3,*default4,
			*floor1,*floor2,*floor3,*floor4,*floor5,*floor6,*floor7,*floor8,*floor9,*floor10,*floor11,*floor12,*floor13

		};


		//Button
		Button* btnA = new Button(1, 1, 
			{ {150,175,25,25} }, 
			{ { 1000,350,25,50 }}, 
			{ { 1000,300,25,50 }}, 
			{ {1000,350,25,50} });
		Button* btnB = new Button(1, 2,
			{ {1200,550,25,25} },
			{ {450,500,25,75},{1100,500,25,75} },
			{ {450,575,25,75},{1100,575,25,75} },
			{ {450,500,25,75},{1100,500,25,75} }
			);
		Button* btnC = new Button(1,1,
			{ {600,675,25,25} },
			{ {100,500,200,25} },
			{ {100,550,200,25} },
			{ {100,550,200,25} }
		);
		buttons = { *btnA,*btnB,*btnC};

		
		SDL_Rect blind1 = { 400,50,100,100 };
		SDL_Rect blind2 = { 650,100,100,100 };

		blinds = { blind1,blind2};

		LiquidWall* lwallA = new LiquidWall({ 615,575,15,90 }, "right");
		LiquidWall* lwallB = new LiquidWall({ 660,575,15,win_h-575 }, "left");
		LiquidWall* lwallC = new LiquidWall({ 450,640,165,25 }, "down");

		liquidWalls = { *lwallA,*lwallB,*lwallC};
		//liquidWalls = {};
		liquidAisles = { };
		
		seesaws = {};


		keys = {};

		Terrain* cannon1 = new Terrain(1100, 300, 100, 50);
		misile* misile1 = new misile({ 1050, 300, 50, 30 });
		cannon = { *cannon1 };
		mis = { *misile1 };

		Terrain* fish1 = new Terrain(250, 160, 30, 30);
		Terrain* fish2 = new Terrain(710, 520, 30, 30);

		Terrain* bone1 = new Terrain(60, 300, 30, 30);
		Terrain* bone2 = new Terrain(1020, 510, 30, 30);

		bone = {*bone1,*bone2};
		fish = { *fish1,*fish2 };
		boxs = {};
		fadefloors = {};
		cushions = {};
		climbWalls = {};
		//milk
		Milk* milk1 = new Milk({ 120,548,305,25 });
		Milk* milk2 = new Milk({ 950,481,200,20 });
		milk = { *milk1,*milk2 };

		// water
		Water* water1 = new Water({ 0,0,0,0 });
		water = { *water1 };

		//choco
		Choco* choco1 = new Choco({ 0,0,0,0 });
		choco = { *choco1 };

		start = { 100,30,50,50 };
		goal = { {50,520,50,50},{50,650,50,50} };

	}
protected:

};



