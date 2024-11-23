#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include <vector>
#include "Torch.h"

class Map8 : public StageInterface
{

public:

    Map8() {};
    ~Map8() {};

    virtual void SetVar()
    {
        //Terrain/////////////////////////////////////////////
        Terrain* default1 = new Terrain(0, 0, 30, win_h);
        Terrain* default2 = new Terrain(0, 0, win_w, 30);
        Terrain* default3 = new Terrain(win_w - 30, 0, 30, win_h);

        //기본 바닥(아래)
        Terrain* default4 = new Terrain(0, win_h - 30, 580, 30);
        Terrain* default5 = new Terrain(1015, win_h - 30, 269, 30);

        Terrain* floor1 = new Terrain(991, 453, 102, 29); //BLIND 위치의 바닥
        Terrain* floor2 = new Terrain(1120, 133, 135, 30); //END 위치의 바닥
        Terrain* floor3 = new Terrain(251, 186, 41, 420); //lock위의 세로벽
        Terrain* floor4 = new Terrain(539, 185, 164, 40); //횃불아래바닥
        Terrain* floor5 = new Terrain(252, 185, 287, 40);//액체화통로 아래쪽

        walls = { *default1,*default2,*default3,*default4,
                        *default5, *floor1,*floor2,*floor3,*floor4,*floor5 };

        //LIQUID WALL////////////////////////////////////
        LiquidWall* lwall1 = new LiquidWall({ 252,185,287,40 }, "down");
        LiquidWall* lwall2 = new LiquidWall({ 252,135,287,20 }, "up");
        liquidWalls = { *lwall1, *lwall2 };

        //SDL_Rect laisle1 = { 250,150,200,30 };
        //liquidAisles = { laisle1 };


        //FADEFLOOR////////////////////////////////////
        FadeFloor* fadefloor1 = new FadeFloor({ 835,412,80,35 });
        FadeFloor* fadefloor2 = new FadeFloor({ 873, 144, 110, 45 }); //높은 위치의 fadefloor
        fadefloors = { *fadefloor1, *fadefloor2 };


        //CLIMB WALL////////////////////////////////////
        ClimbWall* cwall1 = new ClimbWall({ 1226, 493, 25,197 });
        climbWalls = { *cwall1 };


        //score////////////////////////////////////////
        Terrain* fish1 = new Terrain(855, 324, 35, 35);
        Terrain* fish2 = new Terrain(199, 413, 35, 35);
        Terrain* fish3 = new Terrain(169, 141, 35, 35);
        Terrain* fish4 = new Terrain(1017, 78, 35, 35);

        fish = { *fish1, *fish2, *fish3, *fish4 };

        Terrain* bone1 = new Terrain(463, 569, 35, 35);
        Terrain* bone2 = new Terrain(46, 539, 35, 35);
        Terrain* bone3 = new Terrain(43, 273, 35, 35);
        Terrain* bone4 = new Terrain(766, 108, 35, 35);

        bone = { *bone1, *bone2, *bone3, *bone4 };


        //key////////////////////////////////////////
        Key* key = new Key({ 660,293, 50,50 }, { 250,604,41,85 });
        keys = { *key };


        //BLIND////////////////////////////////////
        Blind* blind1 = new Blind({ 762, 384, 251, 133 }, 6);
        blinds = { *blind1 };


        //LIQUID/////////////////////////////////////////////////
        Liquid* choco1 = new Liquid({ 580, 697, 436, 25 }, "choco");
        Liquid* choco2 = new Liquid({ 772, 453, 219, 29 }, "choco");
        Liquid* water1 = new Liquid({ 252,114,287,25 }, "water");
        liquid = { *choco1, *choco2 };
        s_liquid = {};


        //SEESAW/////////////////////////////////////////////////
        Seesaw* ss1 = new Seesaw({ 865, 620, 151, 25 });
        Seesaw* ss2 = new Seesaw({ 582, 620, 151, 25 });
        Seesaw* ss3 = new Seesaw({ 632, 372, 100, 25 });
        seesaws = { *ss1, *ss2, *ss3 };


        //torch/////////////////////////////////////////////////
        Torch* torch1 = new Torch(1, 1, { {0,0,1280,720 } }, { { 1012, 385, 72, 72} }, 255);
        Torch* torch2 = new Torch(1, 1, { {0,0,1280,720 } }, { { 446,623,71,72} }, 255);
        Torch* torch3 = new Torch(1, 1, { {0,0,1280,720 } }, { { 631,119,72,72} }, 255);
        torches = { *torch1, *torch2, *torch3 };


        //other/////////////////////////////////////////////////
        teleports_bi = { };
        buttons = { };
        robo = { };
        fly = { };
        boxs = { };
        cannon = { };
        mis = {};
        cushions = {};

        //GOAL, START/////////////////////////////////////////////
        start = { {1133, 610, 50,80} };
        goal = { { 1166,60,50,80 } };

        //test용도
        //start = { {570,110, 50,80} };
    }
protected:

};
