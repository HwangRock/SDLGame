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
		Terrain* floor1 = new Terrain(200, 140, win_w - 200, 25);
		Terrain* floor2 = new Terrain(win_w-200, 140-25, 200, 25);

		Terrain* floor3 = new Terrain(0, 300, 100, 25);
		Terrain* floor4 = new Terrain(130, 370, 75, 25);
		Terrain* floor5 = new Terrain(0, 440, 100, 25);
		Terrain* floor6 = new Terrain(130, 510, 75, 25);

		Terrain* floor7 = new Terrain(200, 280, 25, win_h-280);
		Terrain* floor8 = new Terrain(200+100, 280, 705, 25);
		Terrain* floor9 = new Terrain(200, 400, 600, 25);
		Terrain* floor10 = new Terrain(350, 520, 150, 25);
		Terrain* floor11 = new Terrain(600, 520, 400, 25);
		Terrain* floor12 = new Terrain(1000, 280, 25, 260);


		Terrain* floor13 = new Terrain(1000, 350, 120, 25);
		Terrain* floor14 = new Terrain(1200, 350, 150, 25);
		Terrain* floor15 = new Terrain(1000, 350+85, 90, 25);
		Terrain* floor16 = new Terrain(1180, 350+85, 150, 25);
		Terrain* floor17 = new Terrain(1000, 520, 130, 25);
		Terrain* floor18 = new Terrain(1220, 520, 100, 25);

		Terrain* floor19 = new Terrain(1000, 650, 25, 100);

		Terrain* default1 = new Terrain(0, 0, 30, win_h);
		Terrain* default2 = new Terrain(0, 0, win_w, 30);
		Terrain* default3 = new Terrain(win_w-30, 0, 30, win_h);
		Terrain* default4 = new Terrain(0, win_h-30, win_w, 30);

		
		walls =
		{
			*floor1,*floor2,
			*floor3,*floor4,*floor5,*floor6,
			*floor7,*floor8,*floor9,*floor10,
			*floor11,*floor12,*floor13,*floor14,*floor15,*floor16,
			*floor17,*floor18,*floor19,
			*default1,*default2,*default3,* default4
		};



		//Button
		Button* btnA = new Button(1, 1,
			{ { 550, 400-25, 25, 25} },
			{ { 0,300-25,80,25 } },
			{ { 0, 240,80,25 } },
			{ { 0,300 - 25,80,25 } });
		Button* btnB = new Button(1, 2,
			{ {370, 520-25, 25, 25} },
			{ {225,280,100,25},{500,520,100,25} },
			{ {225,350,100,25},{500,600,100,25} },
			{ {225,280,100,25},{500,520,100,25} });
		Button* btnC = new Button(1, 1,
			{ {700,400-25,25,25} },
			{ {800,500,100,25 } },
			{ { 800, 400,100,25 } },
			{ { 800,500,100,25  } });
		buttons = {*btnA,*btnB,*btnC };

		blinds = { };

		Box* box1 = new Box({ 600, 450, 50, 50 });
		Box* box2 = new Box({ 300, 330, 50, 50 });
		boxs = { *box1,*box2 };

		Terrain* cannon1 = new Terrain(940, 640, 50, 50);
		misile* misile1 = new misile({ 890, 640, 50, 30 });

		Terrain* fish1 = new Terrain(70, 350, 30, 30);
		Terrain* fish2 = new Terrain(460, 40, 30, 30);
		Terrain* fish3 = new Terrain(840, 210, 30, 30);
		Terrain* fish4 = new Terrain(1180, 230, 30, 30);
		Terrain* fish5 = new Terrain(1130, 390, 30, 30);
		Terrain* fish6 = new Terrain(590, 600, 30, 30);

		Terrain* bone1 = new Terrain(660, 40, 30, 30);
		Terrain* bone2 = new Terrain(165, 470, 30, 30);
		Terrain* bone3 = new Terrain(390, 600, 30, 30);
		Terrain* bone4 = new Terrain(1180, 200, 30, 30);
		Terrain* bone5 = new Terrain(1150, 470, 30, 30);
		Terrain* bone6 = new Terrain(540, 250, 30, 30);

		cannon = { *cannon1 };
		mis = { *misile1 };
		bone = { *bone1,*bone2,*bone3,*bone4,*bone5,*bone6 };
		fish = { *fish1,*fish2,*fish3,*fish4,*fish5,*fish6 };
		
		liquidWalls = { };
		liquidAisles = { };
		climbWalls = {};
		keys = {};
		goal = { {800,50,50,80} };
		start={300,300,50,80};
	}


protected:

};



