#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>

const int modify = 15;
const int modify2 = 10;

class Map2 : public StageInterface
{

public:

	Map2() {};
	~Map2() {};

	virtual void SetVar()
	{
		//Terrain
		Terrain* floor1 = new Terrain(280, 670, 50, 57);
		Terrain* floor2 = new Terrain(163, 615, 45, 90);
		Terrain* floor3 = new Terrain(20, 540, 125, 20);
		Terrain* floor4 = new Terrain(20, 450, 85, 22);

		Terrain* floor5 = new Terrain(253, 520, 415, 20);
		Terrain* floor8 = new Terrain(843, 264, 445, 20);

		Terrain* floor9 = new Terrain(177, 208, 211, 70);
		Terrain* floor10 = new Terrain(20, 370, 40, 20);
		Terrain* extra1 = new Terrain(150, 296, 40, 20);
		Terrain* extra2 = new Terrain(20, 250, 40, 20);
		Terrain* floor11 = new Terrain(468, 230, 35, 35);
		Terrain* floor12 = new Terrain(617, 230, 100, 35);

		Terrain* floor13 = new Terrain(825, 230, 70, 35);
		Terrain* floor14 = new Terrain(1032, 230, 80, 35);
		Terrain* floor15 = new Terrain(1068, 93, 95, 20);

		//맨위의 goal있는 발판
		Terrain* floor16_1 = new Terrain(25, 100, 115, 25);
		Terrain* floor16_2 = new Terrain(250, 100, 50, 25);
		Terrain* floor16_3 = new Terrain(410, 100, 50, 25);
		Terrain* floor16_4 = new Terrain(570, 100, 225, 25);


		Terrain* floor18 = new Terrain(832, 415, 21, 151);
		Terrain* floor19 = new Terrain(177, 278, 1092, 38);


		//DEFAULT
		Terrain* default1 = new Terrain(win_w - 26, 0, 35, 720);
		Terrain* default2 = new Terrain(0, 0, 1280, 20);
		Terrain* default3 = new Terrain(0, 0, 25, 720);

		// 바닥 아래부분
		Terrain* default4 = new Terrain(0, 700, 293, 37);
		Terrain* default5 = new Terrain(325, 700, 166, 35);
		Terrain* default6 = new Terrain(1064, 700, 205, 35);

		//버튼 부분
		Terrain* f1 = new Terrain(1213, 402, 53, 40);
		Terrain* f2 = new Terrain(850, 402, 53, 40);
		Terrain* f3 = new Terrain(901, 414, 316, 28);

		Terrain* liquid2 = new Terrain(388, 258, 455, 20);

		walls =
		{
			*floor1,*floor2,*floor3,*floor4,*floor5,*floor8,*floor9,
			*floor10,*floor11,*floor12,*floor13,*floor14,*floor15,
			*floor16_1,*floor16_2,*floor16_3,*floor16_4,
			*floor18,*floor19,
			*default2,*default3,*default4,*default5,*default6,*default1,
			*liquid2, *extra1,*extra2, *f1,*f2,*f3
		};


		Box* box1 = new Box({ 540, 410, 50, 50 });
		boxs = { *box1 };

		Terrain* fish1 = new Terrain(850, 346, 30, 30);
		Terrain* fish2 = new Terrain(1212, 215, 30, 30);
		Terrain* fish3 = new Terrain(498, 45, 30, 30);

		Terrain* bone1 = new Terrain(549, 331, 30, 30);
		Terrain* bone2 = new Terrain(1212, 28, 30, 30);
		Terrain* bone3 = new Terrain(337, 45, 30, 30);

		bone = { *bone1,*bone2,*bone3 };
		fish = { *fish1,*fish2,*fish3 };

		cannon = { };
		mis = {};
		fadefloors = {};
		cushions = {};

		//Button
		Button* btn1 = new Button(1, 1,
			{ {win_w - 50, 400 - modify,20,20} },
			{ { 105, 450,25,90 } },
			{ { 105, 380,25,90 } },
			{ { 105, 450,25,90 } });
		Button* btn2 = new Button(1, 1,
			{ { 1100, 75,20,20 } },
			{ { 852,93,170,20 } },
			{ { 852, 210,170,20 } },
			{ { 852, 93,170,20 } });
		buttons = { *btn1,*btn2 };


		ClimbWall* cwall1 = new ClimbWall({ 828,402,25,150 + modify });
		ClimbWall* cwall2 = new ClimbWall({ 1250,20,19,259 });
		climbWalls = { *cwall1,*cwall2 };


		//맨 상단의 우유
		Liquid* water0 = new Liquid({ 460,100,110,25 }, "water");

		Liquid* water1 = new Liquid({ 490,700,574,25 }, "water");

		Liquid* milk1 = new Liquid({ 899,402,325,22 }, "milk");
		//맨 상단의 우유
		Liquid* milk2 = new Liquid({ 300,100,110,25 }, "milk");


		Liquid* choco1 = new Liquid({ 388,245,872,24 }, "choco");

		//맨 상단의 초코
		Liquid* choco0 = new Liquid({ 140,100,125,25 }, "choco");


		//밑에 왼쪽 초코
		Liquid* choco2 = new Liquid({ 25,670,140,30 }, "choco");
		Liquid* choco3 = new Liquid({ 200,670,80,30 }, "choco");
		liquid = { *water0, *water1 , *milk1,*milk2 , *choco0 ,*choco1,*choco2,*choco3 };
		s_liquid = {};



		//Blind
		blinds = { };

		liquidWalls = {  };
		liquidAisles = { };

		Key* key = new Key({ 44,493,25,25 }, { 178,125,40,85 });
		keys = { *key };
		//keys = {};

		goal = { {50,35,50,70} };
		start = { {1200,625,50,80} };

		//start = { {600,50,50,80} };//test
	}
protected:

};
