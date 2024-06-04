#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>

extern int win_w, win_h; //Window size

class Map4: public StageInterface
{

public:

	Map4() {};
	~Map4() {};

	virtual void SetVar()
	{

		//Terrain
		//����
		Terrain* floor1_1 = new Terrain(200, 140, 150, 25);
		Terrain* floor1_2 = new Terrain(1100, 140, 150, 25);
		Terrain* floor2 = new Terrain(1150, 140-25, 100, 25);

		//���� ���ǵ�
		Terrain* floor3 = new Terrain(0, 300, 100, 25);
		Terrain* floor4 = new Terrain(150, 370, 50, 25);
		Terrain* floor5 = new Terrain(0, 450, 100, 25);
		Terrain* floor6 = new Terrain(150, 530, 50, 25);
		//������� ����� �߰�
		Terrain* default20 = new Terrain(0, 610, 100, 25);


		//���
		Terrain* floor7 = new Terrain(200, 250, 25, win_h-250);
		Terrain* floor8_1 = new Terrain(350,250,150,25);
		Terrain* floor8_2 = new Terrain(600, 250, 50, 25);
		Terrain* floor8_3 = new Terrain(750, 250, 50, 25);
		Terrain* floor8_4 = new Terrain(900, 250, 100, 25);
		Terrain* floor9_1 = new Terrain(200, 400, 350, 25);
		Terrain* floor9_2 = new Terrain(700, 400, 50, 25);
		Terrain* floor10 = new Terrain(350, 540, 150, 25);
		Terrain* floor11_1 = new Terrain(600, 540, 150, 25);
		Terrain* floor11_2 = new Terrain(900, 540, 100, 25);
		Terrain* floor12 = new Terrain(1000, 250, 25, 300-10+25);

		//������ ���ǵ�
		/*
		Terrain* floor13 = new Terrain(1000, 350, 120, 25);
		Terrain* floor14 = new Terrain(1200, 350, 150, 25);
		Terrain* floor15 = new Terrain(1000, 350+85, 90, 25);
		Terrain* floor16 = new Terrain(1190, 350+85, 150, 25);
		Terrain* floor17 = new Terrain(1000, 520, 130, 25);
		Terrain* floor18 = new Terrain(1220, 520, 100, 25);
		*/

		//������
		Terrain* floor19 = new Terrain(1000, 650, 25, 100);

		


		//�⺻ ��
		Terrain* default1 = new Terrain(0, 0, 30, win_h);
		Terrain* default2 = new Terrain(0, 0, win_w, 30);
		Terrain* default3 = new Terrain(win_w-30, 0, 30, win_h);
		Terrain* default4 = new Terrain(0, win_h-30, win_w - 130, 30);

		
		
		walls =
		{
			*floor1_1,*floor1_2,*floor2,
			*floor3,*floor4,*floor5,*floor6,* default20,
			*floor7,*floor8_1,* floor8_2,* floor8_3,* floor8_4,
			*floor9_1,* floor9_2,*floor10,
			*floor11_1,* floor11_2,*floor12,
			*floor19,
			*default1,*default2,*default3,* default4
		};



		//Button
		Button* btnA = new Button(1, 1,
			{ { 525, 400-25, 25, 25} },
			{ { 30,300-25,50,25 } },
			{ { 30,200,50,25 } },
			{ { 30,300 - 25,50,25 } });
		Button* btnB = new Button(1, 2,
			{ {370, 520, 25, 25} },
			{ {225,250,125,25},{500,540,100,25} },
			{ {225,330,125,25},{500,620,100,25} },
			{ {225,250,125,25},{500,540,100,25} });
		/*
		Button* btnC = new Button(1, 1,
			{ { 700,400-25,25,25} },
			{ { 800,500,100,25 } },
			{ { 800,400,100,25 } },
			{ { 800,500,100,25 } });
		*/
		buttons = {*btnA,*btnB };

		Blind* b1 = new Blind({ 150,450,50,100 },1);
		Blind* b2 = new Blind({ 480,210,140,60 },2);
		Blind* b3 = new Blind({ 1150 ,630,win_w - 30 - 1150,70 },5);
		Blind* b4 = new Blind({ 325,500,100,75 },4);
		blinds = {*b1,*b2,*b3,*b4 };



		Box* box1 = new Box({ 600, 450, 50, 50 });
		Box* box2 = new Box({ 450, 330, 50, 50 });
		boxs = { *box1,*box2 };

		Terrain* cannon1 = new Terrain(940, 640, 50, 50);
		cannon = { *cannon1 };
		misile* misile1 = new misile({ 890, 640, 50, 30 },"left");
		mis = { *misile1 };

		Terrain* fish1 = new Terrain(70, 350, 30, 30);
		Terrain* fish2 = new Terrain(460, 60, 30, 30);
		Terrain* fish3 = new Terrain(840, 210, 30, 30);
		Terrain* fish4 = new Terrain(1160, 230, 30, 30);
		Terrain* fish5 = new Terrain(1130, 390, 30, 30);
		Terrain* fish6 = new Terrain(590, 600, 30, 30);

		Terrain* bone1 = new Terrain(660, 60, 30, 30);
		Terrain* bone2 = new Terrain(165, 470, 30, 30);
		Terrain* bone3 = new Terrain(390, 600, 30, 30);
		Terrain* bone4 = new Terrain(1160, 200, 30, 30);
		Terrain* bone5 = new Terrain(1150, 470, 30, 30);
		Terrain* bone6 = new Terrain(550, 210, 30, 30);

		//FadeFloor* fadefloor1 = new FadeFloor({ 115,650,87,25 });
		//FadeFloor* fadefloor2 = new FadeFloor({ 30,580,87,25 });
		FadeFloor* fadefloor3 = new FadeFloor({ 400,125,100,20 });
		FadeFloor* fadefloor4 = new FadeFloor({ 600,125,100,20 });
		FadeFloor* fadefloor5 = new FadeFloor({ 800,125,100,20 });
		FadeFloor* fadefloor6 = new FadeFloor({ 1000,125,100,20 });
		fadefloors = { *fadefloor3,*fadefloor4,*fadefloor5,*fadefloor6 };

		

	
		bone = { *bone1,*bone2,*bone3,*bone4,*bone5,*bone6 };
		fish = { *fish1,*fish2,*fish3,*fish4,*fish5,*fish6 };
		


		// water
		Liquid* water1 = new Liquid({ 650,250,100,25 }, "water");
		//Liquid* water2 = new Liquid({ 1024,435,66,35 }, "water");


		//milk
		Liquid* milk1 = new Liquid({ 500,250,100,25 }, "milk");
		//Liquid* milk2 = new Liquid({ 1218,519,31,35 }, "milk");


		//choco
		Liquid* choco0 = new Liquid({ 350,140,750,25 }, "choco");

		Liquid* choco1 = new Liquid({ 800,250,100,25 },"choco");
		Liquid* choco2 = new Liquid({ 550,400,150,25 }, "choco");
		Liquid* choco3 = new Liquid({ 750,540,150,25 }, "choco");

		Liquid* choco4 = new Liquid({ 1025,350,90,35 }, "choco");
		//Liquid* choco5 = new Liquid({ 1200,350,50,35 }, "choco");
		Liquid* choco6 = new Liquid({ 1190,435,60,35 }, "choco");
		Liquid* choco7 = new Liquid({ 1025,500,70,35 }, "choco");

		Liquid* choco8 = new Liquid({ 1150,690,100,30 }, "choco");

		liquid =
		{
			*choco0,*choco1,*choco2,*choco3,
			*choco4,*choco6,*choco7,
			* choco8,
			*milk1 ,
			*water1};
		s_liquid = {};

		Cushion* cushion1 = new Cushion({ 900,500,100, 55 });
		cushions = { *cushion1 };


		//climbwall
		ClimbWall* cwall1 = new ClimbWall({ 215,426,20,265 });
		//ClimbWall* cwall2 = new ClimbWall({ 980,306,20,216 });
		climbWalls = { *cwall1 };


		liquidWalls = { };
		liquidAisles = { };
		keys = {};
		goal = { {1200 - 25,40,50,75} };
		start = { {125,620,50,75} };

		//start = { {350,300,50,75} };
	}


protected:

};



