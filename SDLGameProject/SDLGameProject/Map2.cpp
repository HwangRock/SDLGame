#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>

class Map2 : public StageInterface
{

public:

	Map2() {};
	~Map2() {};

	virtual void SetVar()
	{
		//Terrain
		Terrain* floor1 = new Terrain(280, 670, 50, 30);
		Terrain* floor2 = new Terrain(163, 615, 45, 90);
		Terrain* floor3 = new Terrain(20, 540, 125, 20);
		Terrain* floor4 = new Terrain(20, 450, 85, 22);

		Terrain* floor5 = new Terrain(253, 520, 415, 20);
		Terrain* floor6 = new Terrain(250, 400, 170, 15);
		Terrain* floor7 = new Terrain(851, 417, 445, 15);
		Terrain* floor8 = new Terrain(843, 264, 445, 14);

		Terrain* floor9 = new Terrain(178, 208, 210, 70);
		Terrain* floor10 = new Terrain(20, 370, 40, 15);
		Terrain* extra1 = new Terrain(150, 300, 40, 15);
		Terrain* extra2 = new Terrain(20, 250, 40, 15);
		Terrain* floor11 = new Terrain(468, 230, 35, 35);
		Terrain* floor12 = new Terrain(617, 230, 100, 35);

		Terrain* floor13 = new Terrain(825, 230, 70, 35);
		Terrain* floor14 = new Terrain(1032, 230, 80, 35);
		Terrain* floor15 = new Terrain(1068, 93, 95, 20);
		Terrain* floor16 = new Terrain(25, 100, 765, 20);
		Terrain* floor17 = new Terrain(782, 552, 47, 15);
		Terrain* floor18 = new Terrain(832, 415, 21, 151);

		Terrain* default1 = new Terrain(0, 700, 1280, 20); 
		Terrain* default2 = new Terrain(0, 0, 1280, 20); 
		Terrain* default3 = new Terrain(0, 0, 20, 720); 
		Terrain* default4 = new Terrain(1260, 0, 20, 720);

		Terrain* liquid1 = new Terrain(388, 320, 450, 20);
		Terrain* liquid2 = new Terrain(388, 258, 455, 20);

		walls =
		{
			*floor1,*floor2,*floor3,*floor4,*floor5,*floor6,*floor7,*floor8,*floor9,
			*floor10,*floor11,*floor12,*floor13,*floor14,*floor15,*floor16,* floor17,* floor18,
			*default1,*default2,*default3,*default4,
			*liquid1,* liquid2, *extra1,* extra2
		};

		
		Box* box1 = new Box({ 540, 410, 50, 50 });
		boxs = { *box1 };
		
		cannon = { };
		mis = {};
		bone = {};
		fish = {};
		fadefloors = {};
		cushions = {};

		//Button
		Button* btn1 = new Button(1, 1,
			{ {win_w-50, 400,20,20} },
			{ { 100, 450,25,80 } },
			{ { 100, 350,25,80 } },
			{ { 100, 450,25,80 } });
		Button* btn2 = new Button(1, 1,
			{ { 1100, 75,20,20 } },
			{ { 973, 93,100,20 } },
			{ { 973, 50,100,20 } },
			{ { 973, 93,100,20 } });
		buttons = { *btn1,*btn2 };


		ClimbWall* cwall1 = new ClimbWall({ 828,416,25,150 });
		ClimbWall* cwall2 = new ClimbWall({ 1250,20,19,259 });
		climbWalls = { *cwall1,*cwall2 };



		Liquid* water1 = new Liquid({ 490,700,574,25 }, "water");

		Liquid* milk1 = new Liquid({ 849,412,363,20 }, "milk");

		Liquid* choco1 = new Liquid({ 388,245,872,24 }, "choco");
		liquid = { *water1 , *milk1 , *choco1 };
		s_liquid = {};



		//Blind
		blinds = { };

		liquidWalls = {  };
		liquidAisles = { };

		Key* key = new Key({ 44,493,25,25 }, { 390,280,30,30 });
		keys = {*key};
		//keys = {};

		goal = { {50,30,40,70} };
		start = { {1200,620,50,80} };
	}
protected:

};
