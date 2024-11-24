#pragma once
#include "SDL.h"
#include "Stage.h"
#include "Terrain.h"
#include "Button.h"
#include <vector>
#include "Torch.h"

class Map7 : public StageInterface
{

public:

    Map7() {};
    ~Map7() {};

    virtual void SetVar()
    {
        //Terrain
        Terrain* default1 = new Terrain(0, 0, 20, win_h); //왼쪽 외벽
        Terrain* default2 = new Terrain(0, 0, win_w, 20); //지붕
        Terrain* default3 = new Terrain(win_w - 20, 0, 20, win_h); //오른쪽 외벽

        Terrain* column1 = new Terrain(620, 140, 40, win_h - 305); //가운데 기둥(위)
        Terrain* column2 = new Terrain(620, win_h - 70, 40, 70); //가운데 기둥(아래)

        Terrain* floor_start = new Terrain(520, win_h - 90, 240, 20); //스타트 지점 있는 플로어
        Terrain* floor_goal = new Terrain(470, 120, 340, 20); //종료 지점 있는 플로어

        Terrain* floor1 = new Terrain(550, 190, 180, 20); //초콜릿 대포 올려져 있는 플로어
        Terrain* floor3 = new Terrain(435, 335, 410, 20); //텔레포트 올려져 있는 플로어

        Terrain* floor2 = new Terrain(20, 210, 260, 20); //2층 상자 올려져 있는 플로어

        Terrain* floor4 = new Terrain(win_w - 120, win_h - 30, 100, 30);//버튼 있는 플로어

        //Terrain* floor3 = new Terrain(450, 175, 300, 25);
        //Terrain* floor4 = new Terrain(750, 100, 200, 25);
        //Terrain* floor5 = new Terrain(0, 425, 850, 25);

        //Terrain* floor6 = new Terrain(670, 590, 25, 25);//초코 위의 벽


        //liquidWall쪽 벽
        //Terrain* floor7 = new Terrain(250, 110, 200, 15);//up
        //Terrain* floor8 = new Terrain(250, 175, 200, 25);//down
        //Terrain* floor2 = new Terrain(450, 110, 25, 90);


        //Terrain* floor9 = new Terrain(948, 175, 332, 25);
        //Terrain* floor10 = new Terrain(750, 98, 20, 23);
        //Terrain* floor11 = new Terrain(938, 98, 20, 23);

        walls =
        {

           *default1,*default2,*default3,
           *floor_start, *floor_goal,
           *floor1, *floor2, *floor3, *floor4,
           *column1, *column2,


        };

        /*
        //torch////////////////////////////////////////
        //torchNum, darkNum, darkRect, torchPos, opacity
        Torch* torch1 = new Torch(1, 1, { {400,194, 999,355 } }, { { 863, 580, 102, 119} }, 255);
        Torch* torch2 = new Torch(1, 1, { {0,0,279,443 } }, { { 288, 312, 102, 119} }, 255);
        Torch* torch3 = new Torch(1, 1, { {1004,1,278,189} }, { { 697, 60, 102, 119} }, 255);
        torches = { *torch1, *torch2, *torch3 };*/

        ///Teleport//////////
        Teleport_bi* tele1 = new Teleport_bi(
            { 565, 270, 50, 65 },
            { 665, 270, 50, 65 },
            "no one", "no one",
            false, false
        );

        teleports_bi = { *tele1 }; ///////벡터 이름만 첫 글자 t 소문자입니다. 클래스명은 Teleport_bi

        //Button//////////////////////////////////////
        Button* btn1 = new Button(2, 1,
            { {1180,675,20,20},{1180,675,20,20} },
            { { 280, 570,50,25 } },
            { { 280, 525,50,25 } },
            { { 950, 620,200,25 } });
        Button* btn2 = new Button(1, 1,
            { { 400, 160,20,20 } },
            { { 50, 400,150,25 } },
            { { 50, 175,150,25 } },
            { { 50, 400,150,25 } });
        buttons = { *btn1 };


        //BLIND///////////////////////////////////////
        /*
        SDL_Rect blind1 = { 550, 570, 300, 25 };
        SDL_Rect blind2 = { 550, 650, 300, 25 };

        blinds = { blind1,blind2 };  */

        Blind* blind1 = new Blind({ 740,60,230,150 }, 6);
        blinds = {  };


        //LIQUID WALL////////////////////////////////////
        LiquidWall* lwall1 = new LiquidWall({ 250,125,200,15 }, "down");
        liquidWalls = {  };


        SDL_Rect laisle1 = { 250,150,200,30 };
        liquidAisles = {  };

        robot* robo1 = new robot{ {670,win_h - 60,80,35},{win_w - 185,win_h - 60,80,35} };
        robo = { *robo1 };
        flyingBox* fly1 = new flyingBox{ {790, 180,80,35},{1020,180,80,35} };
        fly = { *fly1 };

        //CLIMB WALL////////////////////////////////////
        ClimbWall* cwall = new ClimbWall({ 13,31,19,394 });
        climbWalls = {  };


        //BOX///////////////////////////////////////////
        Box* box1 = new Box({ 510, 290, 50, 50 });
        Box* box2 = new Box({ 100, 150, 50, 50 });
        boxs = { *box1,*box2 };

        ///////////////////////////////////////////////
        cannon = { };
        mis = {};

        Terrain* fish1 = new Terrain(690, win_h - 70, 30, 30);
        Terrain* fish2 = new Terrain(150, 390, 30, 30);
        Terrain* fish3 = new Terrain(690, 150, 30, 30);

        Terrain* bone1 = new Terrain(1140, win_h - 410, 30, 30);
        Terrain* bone2 = new Terrain(150, win_h - 140, 30, 30);
        Terrain* bone3 = new Terrain(540, 150, 30, 30);
        bone = { *bone1,*bone2,*bone3 };
        fish = { *fish1,*fish2,*fish3 };

        keys = {};
        FadeFloor* fadefloor1 = new FadeFloor({ 1000,win_h - 140,100,30 });
        FadeFloor* fadefloor2 = new FadeFloor({ 1100,win_h - 220,100,30 });
        FadeFloor* fadefloor3 = new FadeFloor({ 1000,win_h - 300,100,30 });
        FadeFloor* fadefloor4 = new FadeFloor({ 1100,win_h - 380,100,30 });
        FadeFloor* fadefloor5 = new FadeFloor({ 900,win_h - 380,100,30 });
        fadefloors = { *fadefloor1,*fadefloor2,*fadefloor3,*fadefloor4,*fadefloor5 };
        cushions = {};
        torches = { };

        //LIQUID/////////////////////////////////////////////////
        //Liquid* water1 = new Liquid({ 200,693,330,35 }, "water");//1층
        //Liquid* water2 = new Liquid({ 750,95,198,25 }, "water");
        Liquid* milk1 = new Liquid({ 660, win_h - 30,500,35 }, "milk");//1층 오른쪽 우유(로봇청소기 다니는 곳)
        //Liquid* milk2 = new Liquid({ 750,175,198,25 }, "milk");
        Liquid* choco1 = new Liquid({ 20,win_h - 30,600,30 }, "choco");//1층 왼쪽 초코
        liquid = { *choco1, *milk1 };
        s_liquid = {};

        //SEESAW
        Seesaw* ss1 = new Seesaw({ 130, win_h - 90,100,20 });
        Seesaw* ss2 = new Seesaw({ 130, 430,100,20 });
        Seesaw* ss3 = new Seesaw({ 290, 370,100,20 });
        seesaws = { *ss1,*ss2,*ss3 };
        //GOAL, START/////////////////////////////////////////////
        //goal = { {1125,110,50,75} }; map1 원래 골인 지점
        //start = { {50,620,50,75} }; //map1 원래 스타트 지점
        //start = { {350,375,50,75} }; //텔레포트 시험용 빠른 시작 지점

        start = { {615,win_h - 166, 50, 75} }; //map7 스타트 지점
        goal = { {615,44,50,75} };
        //start={{600,300,50,80}};
        //start = { { 1000,100,50,100 } };
        //바로 클리어 장면 볼 수 있는 start 위치.
    }
protected:

};
