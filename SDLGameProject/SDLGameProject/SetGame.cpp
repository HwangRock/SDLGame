#include "SetGame.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

SetGame::SetGame(int chapterNum)
{

	chapterNum_ = chapterNum;
	
}

std::vector<Terrain> SetGame::SetTerrains() 
{	
	switch (chapterNum_)
	{
	case 0:
		

		break;
	case 1:break;
	case 2:break;
	case 3:break;
	default:
		break;
	}
	//Terrain
	Terrain* floorUp = new Terrain(200, 200, 800, 25);
	Terrain* floorDown = new Terrain(0, 500, 600, 25);

	Terrain* Wall = new Terrain(400 - 25, 150, 25, 50);
	Terrain* Scaffolding2 = new Terrain(600, 100, 100, 25);
	Terrain* Scaffolding3 = new Terrain(500, 600, 100, 25);

	Terrain* default1 = new Terrain(0, 680, 1000, 20);
	Terrain* default2 = new Terrain(0, 0, 1000, 20);
	Terrain* default3 = new Terrain(0, 0, 20, 700);
	Terrain* default4 = new Terrain(980, 0, 20, 700);

	terrains_ =
	{
		*floorUp,*floorDown,*Wall,
		*Scaffolding2,*Scaffolding3,
		*default1,*default2,*default3,*default4,
	};
	return terrains_;
}

std::vector<Button> SetGame::SetButtons()
{
	switch (chapterNum_)
	{
	case 0:
		
		break;
	case 1:break;
	case 2:break;
	case 3:break;
	default:
		break;
	}

	//Button
	Button* btn1 = new Button(2, 2,
		{ {500, 480,20,20},{900,650,20,20} },
		{ { 700,600,150,25 },{100,400,150,25} },
		{ { 700, 500,150,25 },{100,300,150,25} },
		{ { 700, 600,150, 25 },{100,400,150,25} });
	buttons_ = { *btn1 };

	return buttons_;
}
std::vector<SDL_Rect> SetGame::SetBlinds()
{
	switch (chapterNum_)
	{
	case 0:
		

		break;
	case 1:break;
	case 2:break;
	case 3:break;
	default:
		break;
	}

	SDL_Rect blind1 = { 100,650,30,30 };
	SDL_Rect blind2 = { 200,650,30,30 };
	blinds_ = { blind1,blind2 };
	return blinds_;
}
std::vector<SDL_Rect> SetGame::SetLiquidWalls()
{
	switch (chapterNum_)
	{
	case 0:
		
		break;
	case 1:break;
	case 2:break;
	case 3:break;
	default:
		break;
	}

	SDL_Rect lwall1 = { 200, 150, 200, 25 };
	lwalls_ = { lwall1 };
	return lwalls_;
}

std::vector<SDL_Rect> SetGame::SetLiquidAisles()
{
	switch (chapterNum_)
	{
	case 0:
		
		break;
	case 1:break;
	case 2:break;
	case 3:break;
	default:
		break;
	}

	SDL_Rect laisle1 = { 200,175,200,30 };
	laisles_ = { laisle1 };
	return laisles_;
}


