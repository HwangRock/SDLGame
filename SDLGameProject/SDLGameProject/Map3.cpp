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
	
		//Terrain
		Terrain* floorUp = new Terrain(200, 200, 800, 25);
		Terrain* floorDown = new Terrain(0, 500, 600, 25);

		Terrain* default1 = new Terrain(0, 680, 1000, 20);
		Terrain* default2 = new Terrain(0, 0, 1000, 20);
		Terrain* default3 = new Terrain(0, 0, 20, 700);
		Terrain* default4 = new Terrain(980, 0, 20, 700);

		walls =
		{
			*floorUp,*floorDown,
			*default1,*default2,*default3,*default4
		};


		//Button

		buttons = { };

		blinds = { };

		liquidWalls = { };
		liquidAisles = { };

		std::cout << "map3 SetVar\n";
	}
protected:

};



