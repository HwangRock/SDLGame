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
		Terrain* floor1 = new Terrain(0, 100, 400, 25);
		Terrain* floor2 = new Terrain(700, 150, 100, 25);
		Terrain* floor3 = new Terrain(150, 300, 1000 - 100, 25);
		Terrain* floor4 = new Terrain(0, 350, 60, 25);
		Terrain* floor5 = new Terrain(0, 400, 100, 25);
		Terrain* floor6 = new Terrain(250, 450, 150, 25);
		Terrain* floor7 = new Terrain(350, 350, 350, 80);
		Terrain* floor8 = new Terrain(800, 450, 100, 25);
		Terrain* floor9 = new Terrain(600, 500, 1000 - 600, 25);
		Terrain* floor10 = new Terrain(0, 500, 150, 25);
		Terrain* floor11 = new Terrain(300, 550, 100, 25);

		Terrain* wall1 = new Terrain(100, 700 - 50, 50, 50);
		Terrain* wall2 = new Terrain(200, 700 - 100, 50, 100);

		Terrain* default1 = new Terrain(0, 680, 1000, 20);
		Terrain* default2 = new Terrain(0, 0, 1000, 20);
		Terrain* default3 = new Terrain(0, 0, 20, 700);
		Terrain* default4 = new Terrain(980, 0, 20, 700);

		walls =
		{
			*floor1,*floor2,*floor3,*floor4,*floor5,*floor6,*floor7,*floor8,*floor9,*floor10,*floor11,
			*wall1,*wall2,
			*default1,*default2,*default3,*default4
		};


		//Button
		buttons = { };

		blinds = { };

		liquidWalls = {  };

		liquidAisles = { };
	}
protected:

};



