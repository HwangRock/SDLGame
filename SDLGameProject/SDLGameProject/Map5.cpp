#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>

class Map5 : public StageInterface
{

public:

    Map5() {};
    ~Map5() {};

    virtual void SetVar()
    {

        Terrain* default1 = new Terrain(0, 0, 30, win_h);
        Terrain* default2 = new Terrain(0, 0, win_w, 30);
        Terrain* default3 = new Terrain(win_w - 30, 0, 30, win_h);
        Terrain* default4 = new Terrain(460, win_h - 30, win_w, 30);

        Terrain* floor1 = new Terrain(600, 300, 100, 20);
        //Terrain* floor2 = new Terrain(300, 400, 30, 20);
        Terrain* floor3 = new Terrain(150, 550, 870, 20);
        Terrain* floor4 = new Terrain(1020, 500, 20, 70);
        Terrain* floor5 = new Terrain(150, 350, 20, 200);


        //왼쪽 상단 물
        Terrain* floor6_1 = new Terrain(30, 130, 25, 25);
        Terrain* floor6_2 = new Terrain(125, 130, 25, 25);


        Terrain* floor7 = new Terrain(150, 130, 20, 150);
        Terrain* floor8 = new Terrain(100, 350, 50, 20);
        Terrain* floor9 = new Terrain(30, 275, 40, 20);
        Terrain* floor10 = new Terrain(300, 130, 100, 20);
        //Terrain* floor11 = new Terrain(300, 300, 50, 20);
        Terrain* floor12 = new Terrain(800, 300, 20, 20);
        Terrain* floor13 = new Terrain(800, 150, 20, 20);
        Terrain* floor14 = new Terrain(500, 130, 220, 20);
        Terrain* floor15 = new Terrain(850, 420, 25, 80);//박스 위쪽 막는거
        Terrain* floor16 = new Terrain(1200, 370, 50, 20);
        Terrain* floor17 = new Terrain(1100, 140, 180, 20);//goal있는곳
        Terrain* floor18 = new Terrain(910, 30, 10, 390);

        walls =
        {
           *default1,*default2,*default3,*default4,
           *floor1,*floor3,*floor4, *floor5,*floor6_1,*floor6_2,*floor7,*floor8,*floor9,
           *floor10,*floor12,*floor13,*floor14,*floor15,*floor16,*floor17,*floor18
        };

        Button* btnA = new Button(1, 1,
            { { 330, 110, 25, 25} },
            { { 150, 280,20,80 } },
            { { 150, 200,20,80 } },
            { { 150, 280,20,80 } });
        Button* btnB = new Button(1, 1,
            { { 30, 255, 25, 25} },
            { { 170,400,130,30 } },
            { { 300,400,130,30 } },
            { { 170,400,130,30 } });
        Button* btnC = new Button(1, 1,
            { { 1150, 120, 25, 25} },
            { { 940,420 - 25,150,25 } },
            { { 940,140,150,25 } },
            { { 940,420 - 25,150,25 } });
        buttons = { *btnA,*btnB,*btnC };

        liquidWalls = { };
        liquidAisles = { };

        ClimbWall* cwall1 = new ClimbWall({ 900,30,40,400 });
        climbWalls = { *cwall1 };

        Box* box1 = new Box({ 850, 500, 50, 50 });
        boxs = { *box1 };

        Terrain* cannon1 = new Terrain(750, 500, 50, 50);
        misile* misile1 = new misile({ 700, 500, 50, 30 }, "left");

        Terrain* cannon2 = new Terrain(600, 640, 50, 50);
        misile* misile2 = new misile({ 650, 640, 50, 30 }, "right");
        cannon = { *cannon1,*cannon2 };
        mis = { *misile1,*misile2 };

        Terrain* bone1 = new Terrain(50, 450, 50, 30);
        Terrain* bone2 = new Terrain(780, 610, 50, 30);
        bone = { *bone1,*bone2 };

        Terrain* fish1 = new Terrain(80, 95, 50, 30);
        Terrain* fish2 = new Terrain(630, 95, 50, 30);
        fish = { *fish1,*fish2 };

        keys = {};

        Liquid* water1 = new Liquid({ 55, 130,70,25 }, "water");
        Liquid* choco1 = new Liquid({ 30, win_h - 30,470,30 }, "choco");//아래쪽 초코
        Liquid* choco2 = new Liquid({ 300, 400, 600, 30 }, "choco");//위쪽 초코
        liquid =
        {
           *water1,*choco1,*choco2
        };
        s_liquid = {};



        FadeFloor* fadefloor1 = new FadeFloor({ 200,640,87,25 });
        FadeFloor* fadefloor2 = new FadeFloor({ 50,640,87,25 });
        FadeFloor* fadefloor3 = new FadeFloor({ 50,540,87,25 });
        FadeFloor* fadefloor4 = new FadeFloor({ 350,640,87,25 });
        FadeFloor* fadefloor5 = new FadeFloor({ 400,300,87,25 });
        fadefloors = { *fadefloor1,*fadefloor2, *fadefloor3,*fadefloor4,*fadefloor5 };

        Cushion* cushion1 = new Cushion({ 1100,640,100, 55 });
        cushions = { *cushion1 };

        Blind* blind1 = new Blind({ 30,80,140,80 }, 2);
        Blind* blind2 = new Blind({ 580,60,150,80 }, 0);
        blinds = { *blind1,*blind2 };

        goal = { { 1100,65,50,80 } };
        start = { { 620,225,50,80 } };

        //start = { {1110,300,50,80} };
        //start = { 300,50,50,80 };
        //start = { 30, 170, 50, 80 };
    }
protected:

};

