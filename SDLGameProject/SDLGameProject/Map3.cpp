#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include "Key.cpp"
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
        Terrain* floor5 = new Terrain(749,173,102,25);
        Terrain* floor6 = new Terrain(0, 350, 250, 25);
        Terrain* floor7 = new Terrain(400, 350, win_w - 400, 25);
        Terrain* floor8 = new Terrain(950, 375, win_w - 950, 50);

        Terrain* floor9_1 = new Terrain(0, 475, 270, 25);
        Terrain* floor9_2 = new Terrain(430, 475, 110, 25);
        Terrain* floor9_3 = new Terrain(670, 475, 50, 25);

        Terrain* floor10 = new Terrain(950, 500, 200, 25);

        Terrain* floor12 = new Terrain(450, 575, 165, 65);//Liquid wallÂÊ
        Terrain* floor13 = new Terrain(675, 575, win_w - 675, win_h - 575);

        Terrain* block1 = new Terrain(116, 598, 318, 27);
        Terrain* block2 = new Terrain(15, 575, 103, 50);
        Terrain* block3 = new Terrain(426, 575, 25, 50);

        //default
        Terrain* default1 = new Terrain(0, 0, 30, win_h);
        Terrain* default2 = new Terrain(0, 0, win_w, 30);
        Terrain* default3 = new Terrain(win_w - 30, 0, 30, win_h);
        Terrain* default4 = new Terrain(0, win_h - 30, win_w, 30);
        walls =
        {

           *default1,*default2,*default3,*default4,
           *floor1,*floor2,*floor3,*floor4,*floor5,*floor6,*floor7,*floor8,
           *floor9_1,*floor9_2,*floor9_3,
           *floor10,*floor12,*floor13,
           *block1,*block2,*block3

        };


        //Button
        Button* btnA = new Button(1, 1,
            { {150,175,25,25} },
            { { 1000,350,25,50 } },
            { { 1000,300,25,50 } },
            { {1000,350,25,50} });
        Button* btnB = new Button(1, 2,
            { {1200,550,25,25} },
            { {450,500,25,75},{1125,500,25,75} },
            { {450,575,25,75},{1125,575,25,75} },
            { {450,500,25,75},{1125,500,25,75} }
        );
        Button* btnC = new Button(1, 1,
            { {600,670,25,25} },
            { {180,600,190,25} }, 
            { {180,550,190,25} },
            { {180,600,190,25} }
        );
        buttons = { *btnB,*btnC };


        Blind* blind1 = new Blind({ 400,50,100,100 }, 4);
        Blind* blind2 = new Blind({ 650,100,100,100 }, 5);
        blinds = { *blind1,*blind2 };

        LiquidWall* lwallA = new LiquidWall({ 615,575,15,90 }, "down");
        LiquidWall* lwallB = new LiquidWall({ 660,575,15,win_h - 575 }, "down");
        LiquidWall* lwallC = new LiquidWall({ 450,640,165,25 }, "down");

        liquidWalls = { *lwallA,*lwallB,*lwallC };
        //liquidWalls = {};
        liquidAisles = { };




        keys = {};

        Terrain* cannon1 = new Terrain(1100, 300, 100, 50);
        misile* misile1 = new misile({ 1050, 300, 50, 30 }, "left");
        cannon = { *cannon1 };
        mis = { *misile1 };

        Terrain* fish1 = new Terrain(250, 160, 30, 30);
        Terrain* fish2 = new Terrain(710, 520, 30, 30);
        Terrain* fish3 = new Terrain(684,123, 30, 30);

        Terrain* bone1 = new Terrain(60, 300, 30, 30);
        Terrain* bone2 = new Terrain(1020, 530, 30, 30);

        bone = { *bone1,*bone2 };
        fish = { *fish1,*fish2,*fish3 };
        boxs = {};
        fadefloors = {};
        cushions = {};
        climbWalls = {};



        Liquid* choco1 = new Liquid({ 270,475,160,25 }, "choco");

        Liquid* milk1 = new Liquid({ 118,575,310,25 }, "milk");
        Liquid* milk2 = new Liquid({ 950,483,200,20 }, "milk");
        Liquid* milk3 = new Liquid({ 651,173,99,25 }, "milk");

        Liquid* water1 = new Liquid({ 540,475,130,25 }, "water");
        //Liquid* water2 = new Liquid({ 399,101,101,25 }, "water");
        liquid = { *choco1, *milk1 , *milk2,*water1,*milk3 };
        s_liquid = {};


        start = { {100,30,50,70} };
        goal = { {50,505,50,70},{50,623,50,70} };


    }
protected:

};



