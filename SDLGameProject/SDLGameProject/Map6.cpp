#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>

class Map6 : public StageInterface
{

public:

	Map6() {};
	~Map6() {};

	virtual void SetVar()
	{

		Terrain* default1 = new Terrain(0, 0, 30, win_h);
		Terrain* default2 = new Terrain(0, 0, win_w, 30);
		Terrain* default3 = new Terrain(win_w - 30, 0, 30, win_h);
		Terrain* default4 = new Terrain(0, win_h - 30, win_w, 30);

		Terrain* floor1 = new Terrain(80, 530, 90, 20);
		Terrain* floor2 = new Terrain(1130, 440, 70, 20);
		Terrain* floor3 = new Terrain(220, 150, 30, 550);
		Terrain* floor4 = new Terrain(1050, 497, 200, 40);
		Terrain* floor5 = new Terrain(1050, 170, 30, 330);
		Terrain* floor6 = new Terrain(250, 150, 300, 30);
		Terrain* floor7 = new Terrain(400, 330, 650, 20);
		Terrain* floor8 = new Terrain(400, 350, 30, 150);
		Terrain* floor9 = new Terrain(30, 260, 60, 30);//버튼 A가 있을 곳
		Terrain* floor10 = new Terrain(250, 650, 50, 50);//버튼 C가 있을 곳
		Terrain* floor11 = new Terrain(600, 650, 50, 50);
		Terrain* floor12 = new Terrain(850, 600, 50, 100);//버튼 D가 있을 곳
		//Terrain* floor13 = new Terrain(700, 670, 150, 20);
		Terrain* floor14 = new Terrain(800, 430, 100, 20);
		Terrain* floor15 = new Terrain(650, 150, 430, 20);
		Terrain* floor16 = new Terrain(1180, 210, 70, 20);
		Terrain* floor17 = new Terrain(150, 210, 70, 20);

		Terrain* floor18 = new Terrain(650, 170, 150, 80);
		Terrain* floor19 = new Terrain(800, 170, 150, 40);
		Terrain* floor20 = new Terrain(950, 170, 100, 80);
		Terrain* floor21 = new Terrain(650, 300, 400, 30);
		Terrain* floor22 = new Terrain(850, 260, 50, 40);
		Terrain* floor23 = new Terrain(870, 100, 100, 30);
		Terrain* floor24 = new Terrain(30, 595, 190, 100);

		LiquidWall* lwall1 = new LiquidWall({ 650,250,170,30 }, "down");//up
		LiquidWall* lwall2 = new LiquidWall({ 800,210,30,70 }, "down");//down
		LiquidWall* lwall3 = new LiquidWall({ 830,210,120,40 }, "down");//down
		liquidWalls = { *lwall1,*lwall2,*lwall3 };

		walls =
		{
			*default1,*default2,*default3,*default4,
			*floor1,*floor2,*floor3,*floor4,*floor5,*floor6,*floor7,*floor8,*floor9,*floor10,
			*floor11,*floor12,*floor14,*floor15,*floor16,*floor17,*floor18,
			*floor19,*floor20,*floor21,*floor22,*floor23,*floor24
		};

		Button* btnA = new Button(1, 1,
			{ { 30, 235, 25, 25} },
			{ { 1080,330,170,25 } },
			{ { 950, 330,170,25 } },
			{ { 1080,330,170,25 } });
		Button* btnB = new Button(1, 1,
			{ { 675, 130, 25, 25} },
			{ { 30,150,190,25 } },
			{ { 220, 150,190,25 } },
			{ { 30,150,190,25 } });
		Button* btnC = new Button(2, 1,
			{ { 250, 625, 25, 25},{1000, 280, 25, 25} },
			{ { 250, 330, 150, 20} },
			{ { 400, 330,170,25 } },
			{ { 250, 330, 150, 20} });
		Button* btnD = new Button(1, 1,
			{ { 850, 575, 25, 25} },
			{ { 700,660,150,30 } },
			{ {700,640,150,30 } },
			{ {700,660,150,30 } });
		buttons = { *btnA,*btnB,*btnC,*btnD };

		SDL_Rect laisle1 = { 650,250,220,50 };
		SDL_Rect laisle2 = { 800,200,50,100 };
		SDL_Rect laisle3 = { 850,200,100,50 };

		liquidAisles = { laisle1,laisle2,laisle3 };

		ClimbWall* cwall1 = new ClimbWall({ 650,450,50,250 });
		ClimbWall* cwall2 = new ClimbWall({ 1000,350,50,187 });
		climbWalls = { *cwall1,*cwall2 };

		Box* box1 = new Box({ 300, 500, 50, 50 });
		boxs = { *box1 };

		Terrain* cannon1 = new Terrain(850, 380, 50, 50);
		misile* misile1 = new misile({ 800, 380, 50, 30 },"left");
		cannon = { *cannon1 };
		mis = { *misile1 };

		Terrain* bone1 = new Terrain(280, 280, 30, 30);
		Terrain* bone2 = new Terrain(480, 450, 30, 30);
		Terrain* bone3 = new Terrain(650, 410, 30, 30);
		bone = { *bone1,*bone2,*bone3 };

		Terrain* fish1 = new Terrain(400, 110, 30, 30);
		Terrain* fish2 = new Terrain(300, 200, 30, 30);
		Terrain* fish3 = new Terrain(950, 360, 30, 30);
		fish = {*fish1,*fish2,*fish3 };

		keys = {};

		Liquid* water1 = new Liquid({ 30,570,190,27 }, "water");
		Liquid* water2 = new Liquid({ 300,670,300,30 }, "water");

		Liquid* milk1 = new Liquid({ 1080,470,170,27 }, "milk");
		Liquid* milk2 = new Liquid({ 700,650,150,50 }, "milk");
		Liquid* milk3 = new Liquid({ 810,140,200,20 }, "milk");
		Liquid* choco1 = new Liquid({ 900,680,100,20 }, "choco");

		liquid =
		{
			*water1,*water2,*milk1,*milk2,*milk3,*choco1
		};

		FadeFloor* fadefloor1 = new FadeFloor({ 30,450,70,25 });
		FadeFloor* fadefloor2 = new FadeFloor({ 150,410,50,25 });
		FadeFloor* fadefloor3 = new FadeFloor({ 50,340,50,25 });
		FadeFloor* fadefloor4 = new FadeFloor({ 1200,360,50,25 });
		FadeFloor* fadefloor5 = new FadeFloor({ 1080,275,50,25 });
		fadefloors = { *fadefloor1,*fadefloor2,*fadefloor3,*fadefloor4,*fadefloor5 };

		cushions = { };

		Blind* b1 = new Blind({ 340,100,140,50 },3);
		Blind* b2 = new Blind({ 800,20,220,150 },0);
		blinds = { *b1,*b2 };

		goal = { { 1190,610,50,80 } };
		start = { { 100,450,50,80 },{1130,360,50,80 } };
		//start = { {600,200,50,80} };
	}
protected:

};

