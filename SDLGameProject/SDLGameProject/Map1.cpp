#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>

class Map1 : public StageInterface
{

public:

    Map1() {};
    ~Map1() {};

    virtual void SetVar()
    {
        //Terrain
        Terrain* default1 = new Terrain(0, 0, 30, win_h);
        Terrain* default2 = new Terrain(0, 0, win_w, 30);
        Terrain* default3 = new Terrain(win_w - 30, 0, 30, win_h);

        Terrain* default4 = new Terrain(0, win_h - 30, 200, 30);
        Terrain* default5 = new Terrain(850, win_h - 30, 102, 30);
        Terrain* default6 = new Terrain(1150, win_h - 30, 130, 30);
        Terrain* default7 = new Terrain(530, win_h - 30, 20, 30);



        Terrain* floor1 = new Terrain(200, 175, 50, 25);
        
        Terrain* floor3 = new Terrain(450, 175, 300, 25);
        //Terrain* floor4 = new Terrain(750, 100, 200, 25);
        Terrain* floor5 = new Terrain(0, 425, 850, 25);

        Terrain* floor6 = new Terrain(670, 590, 25, 25);//초코 위의 벽
        

        //liquidWall쪽 벽
        Terrain* floor7 = new Terrain(250, 110, 200, 15);//up
        Terrain* floor8 = new Terrain(250, 175, 200, 25);//down
        Terrain* floor2 = new Terrain(450, 110, 25, 90);


        Terrain* floor9 = new Terrain(948, 175, 332, 25);
        //Terrain* floor10 = new Terrain(750, 98, 20, 23);
        //Terrain* floor11 = new Terrain(938, 98, 20, 23);

        walls =
        {
           *floor1,*floor2,*floor3,*floor5,*floor6,*floor7,*floor8,
           *default1,*default2,*default3,*default4,*default5,*default6,
           *default7, *floor9
        };





        //Button//////////////////////////////////////
        Button* btn1 = new Button(2, 1,
            { {650, 405,20,20},{1180,675,20,20} },
            { { 950, 620,200,25 } },
            { { 950, 470,200,25 } },
            { { 950, 620,200,25 } });
        Button* btn2 = new Button(1, 1,
            { { 400, 160,20,20 } },
            { { 50, 400,150,25 } },
            { { 50, 175,150,25 } },
            { { 50, 400,150,25 } });
        buttons = { *btn1,*btn2 };


        //BLIND///////////////////////////////////////
        /*
        SDL_Rect blind1 = { 550, 570, 300, 25 };
        SDL_Rect blind2 = { 550, 650, 300, 25 };

        blinds = { blind1,blind2 };  */
       
        Blind* blind1 = new Blind({ 740,60,230,150 }, 6);
        blinds = { *blind1 };


        //LIQUID WALL////////////////////////////////////
        LiquidWall* lwall1 = new LiquidWall({ 250,125,200,15 }, "down");
        liquidWalls = { *lwall1 };


        SDL_Rect laisle1 = { 250,150,200,30 };
        liquidAisles = { laisle1 };


        //CLIMB WALL////////////////////////////////////
        ClimbWall* cwall = new ClimbWall({ 13,31,19,394 });
        climbWalls = { *cwall };


        //BOX///////////////////////////////////////////
        Box* box1 = new Box({ 400, 580, 50, 50 });
        boxs = { *box1 };

        ///////////////////////////////////////////////
        cannon = { };
        mis = {};

        Terrain* fish1 = new Terrain(143, 41, 30, 30);
        Terrain* fish2 = new Terrain(760, 640, 30, 30);

        Terrain* bone1 = new Terrain(620, 640, 30, 30);
        Terrain* bone2 = new Terrain(810, 130, 30, 30);
        bone = { *bone1,*bone2 };
        fish = { *fish1,*fish2 };

        keys = {};
        fadefloors = {};
        cushions = {};

        //LIQUID/////////////////////////////////////////////////
        Liquid* water1 = new Liquid({ 200,693,330,35 }, "water");//1층
        Liquid* water2 = new Liquid({ 750,95,198,25 }, "water");
        Liquid* milk1 = new Liquid({ 952,693,198,35 }, "milk");//1층
        Liquid* milk2 = new Liquid({ 750,175,198,25 }, "milk");
        Liquid* choco1 = new Liquid({ 550,693,300,35 }, "choco");//1층
        liquid = { *water1,*water2 , *milk1,*milk2 ,*choco1 };
        s_liquid = {};

        //GOAL, START/////////////////////////////////////////////
        goal = { {1125,110,50,75} };
        start = { {50,620,50,75} };

        //start={{600,300,50,80}};
        //start = { 1000,100,50,100 };
        //바로 클리어 장면 볼 수 있는 start 위치.
    }
protected:

};
