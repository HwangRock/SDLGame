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
        Terrain* default1 = new Terrain(0, 0, 20, win_h); //���� �ܺ�
        Terrain* default2 = new Terrain(0, 0, win_w, 20); //����
        Terrain* default3 = new Terrain(win_w - 20, 0, 20, win_h); //������ �ܺ�

        Terrain* column1 = new Terrain(620, 140, 40, win_h - 305); //��� ���(��)
        Terrain* column2 = new Terrain(620, win_h - 70, 40, 70); //��� ���(�Ʒ�)

        Terrain* floor_start = new Terrain(520, win_h - 90, 240, 20); //��ŸƮ ���� �ִ� �÷ξ�
        Terrain* floor_goal = new Terrain(470, 120, 340, 20); //���� ���� �ִ� �÷ξ�

        Terrain* floor1 = new Terrain(550, 190, 180, 20); //���ݸ� ���� �÷��� �ִ� �÷ξ�
        Terrain* floor3 = new Terrain(435, 335, 410, 20); //�ڷ���Ʈ �÷��� �ִ� �÷ξ�

        Terrain* floor2 = new Terrain(20, 210, 260, 20); //2�� ���� �÷��� �ִ� �÷ξ�

        Terrain* floor4 = new Terrain(win_w - 120, win_h - 30, 100, 30);//��ư �ִ� �÷ξ�

        //Terrain* floor3 = new Terrain(450, 175, 300, 25);
        //Terrain* floor4 = new Terrain(750, 100, 200, 25);
        //Terrain* floor5 = new Terrain(0, 425, 850, 25);

        //Terrain* floor6 = new Terrain(670, 590, 25, 25);//���� ���� ��


        //liquidWall�� ��
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
            { 565, 285, 50, 50 },
            { 665, 285, 50, 50 },
            "no one", "no one",
            false, false
        );

        teleports_bi = { *tele1 }; ///////���� �̸��� ù ���� t �ҹ����Դϴ�. Ŭ�������� Teleport_bi

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
        buttons = { };


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

        //robot* robo1 = new robot{ {150,653,80,35},{200,653,80,35} };
        robo = {  };
        //flyingBox* fly1 = new flyingBox{ {150,553,80,35},{200,553,80,35} };
        fly = {  };

        //CLIMB WALL////////////////////////////////////
        ClimbWall* cwall = new ClimbWall({ 13,31,19,394 });
        climbWalls = {  };


        //BOX///////////////////////////////////////////
        Box* box1 = new Box({ 400, 580, 50, 50 });
        boxs = {  };

        ///////////////////////////////////////////////
        cannon = { };
        mis = {};

        Terrain* fish1 = new Terrain(143, 41, 30, 30);
        Terrain* fish2 = new Terrain(760, 640, 30, 30);

        Terrain* bone1 = new Terrain(620, 640, 30, 30);
        Terrain* bone2 = new Terrain(810, 130, 30, 30);
        bone = {};
        fish = {};

        keys = {};
        fadefloors = {};
        cushions = {};

        //LIQUID/////////////////////////////////////////////////
        //Liquid* water1 = new Liquid({ 200,693,330,35 }, "water");//1��
        //Liquid* water2 = new Liquid({ 750,95,198,25 }, "water");
        Liquid* milk1 = new Liquid({ 660, win_h - 30,500,35 }, "milk");//1�� ������ ����(�κ�û�ұ� �ٴϴ� ��)
        //Liquid* milk2 = new Liquid({ 750,175,198,25 }, "milk");
        Liquid* choco1 = new Liquid({ 20,win_h - 30,600,30 }, "choco");//1�� ���� ����
        liquid = { *choco1, *milk1 };
        s_liquid = {};

        //SEESAW
        //Seesaw* ss1 = new Seesaw({ 880,500,100,25 });
        //seesaws = { *ss1 };
        //GOAL, START/////////////////////////////////////////////
        //goal = { {1125,110,50,75} }; map1 ���� ���� ����
        //start = { {50,620,50,75} }; //map1 ���� ��ŸƮ ����
        //start = { {350,375,50,75} }; //�ڷ���Ʈ ����� ���� ���� ����

        start = { {615,win_h - 166, 50, 75} }; //map7 ��ŸƮ ����
        goal = { {615,44,50,75} };
        //start={{600,300,50,80}};
        //start = { { 1000,100,50,100 } };
        //�ٷ� Ŭ���� ��� �� �� �ִ� start ��ġ.
    }
protected:

};
