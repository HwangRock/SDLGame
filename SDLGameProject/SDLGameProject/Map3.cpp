#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
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
		Terrain* floor12 = new Terrain(450, 575, 150, 75);
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

		//Hidden_강아지 스킬로 걷어낼 수 있는 숨겨진 지역, Blind로 표시하신 것 같아서 일단 Blind로 나두었습니다!
		SDL_Rect blind1 = { 400,50,100,100 };
		SDL_Rect blind2 = { 650,100,100,100 };

		blinds = { blind1,blind2};


		liquidWalls = { };
		liquidAisles = { };

		start = { 100,50,50,50 };
		goal = { 50,520,50,50 };

	}
protected:

};



