#pragma once
         
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "SDL.h"     
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h" 
 
//////////////////////  ///
#include "math.h"  

#include "Dog.h"
#include "Cat.h" 
#include "Pet.h"
  
#include "Terrain.h"
#include "Button.h"    
#include "LiquidWall.h"
#include "ClimbWall.cpp"
#include "FadeFloor.h"
#include "Cushion.h" 
#include "Blind.cpp"
     
    
#include "Box.h"  
#include "misile.cpp" 
 
#include "Liquid.cpp" 
#include "SwellingLiquid.cpp"

#include "Key.cpp" 

#include "Game.h"

#include "CatAnimation.h"
#include "DogAnimation.h"

extern std::vector<Terrain> walls, cannon, fish, bone; 
extern std::vector<Box> boxs;    
extern std::vector<Button> buttons;        
extern std::vector<Blind> blinds;
extern std::vector<LiquidWall>liquidWalls;
extern std::vector<SDL_Rect>liquidAisles;         
extern std::vector<ClimbWall>climbWalls;
extern std::vector<Cushion>cushions;
extern std::vector<FadeFloor>fadefloors;
extern std::vector<misile>mis;

extern std::vector<SDL_Rect> cat_animation;
extern std::vector<SDL_Rect> dog_animation;

extern std::vector<Liquid>liquid;
extern std::vector<SwellingLiquid> s_liquid;
extern std::vector<Key>keys;

extern std::vector<SDL_Rect> goal;
extern std::vector<SDL_Rect> start;

  
extern int chapterNum;
extern int win_w, win_h; 

extern SDL_Texture *manyTexture;
extern SDL_Texture* many2Texture;

extern int score_bone;
extern int score_fish; 

extern SDL_Texture* mapbg; 
extern SDL_Rect mapSrect[3];
extern SDL_Rect mapDrect;

extern bool isFirst; 
      
class StageInterface : public PhaseInterface    
{  
public:   
	StageInterface();  
	~StageInterface();
	    
	virtual void SetVar();
	virtual void Reset();
	 
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	
	void NextChapter();
	CatAnimation catAnim;
	DogAnimation dogAnim;

private:   
	//Sprite 
	SDL_Rect dogRect;
	SDL_Rect catRect;  


	SDL_Texture* wallTexture;
	SDL_Texture* cwallTexture;
 
	SDL_Texture* goalTexture;
	SDL_Texture* scaffoldTexture;
	SDL_Texture* reTexture;

	SDL_Texture* curtainTexture;
             


	SDL_Texture* picturesTexture;
	std::vector<SDL_Rect> picturesRect;

	SDL_Texture* liquidTexture;
	SDL_Rect waterR;
	SDL_Rect chocoR;
	SDL_Rect milkR;

	 
	SDL_Rect keyRect;
	SDL_Rect lockRect;

	
	 
	 
	SDL_Rect dogPushRect;
	SDL_Rect scaffoldRect; 
	SDL_Rect goalRect;
	SDL_Rect cwallRect;   
	SDL_Rect wallRect;
	SDL_Rect buttonRect;
	SDL_Rect PushbuttonRect;

	 
	SDL_Rect boxRect;
	SDL_Rect cannonRect;
	SDL_Rect reRect;     
	SDL_Rect lcannonRect;
	SDL_Rect misileRect;
	SDL_Rect reRect_des;        
	SDL_Rect fishRect;
	SDL_Rect boneRect;  
	SDL_Rect cushionRect;
	SDL_Rect PushcushionRect;
	SDL_Rect fadefloorRect;
	SDL_Rect catDieRect;
	SDL_Rect dogDieRect;
	SDL_Rect bgRect;

	  
	  
	 
	//Pets
	//Pet* dog = new Pet(700, 100, true);
	//Pet* cat = new Pet(600, 1 00, false);
	Dog* dog = new Dog(700, 100); 
	Cat* cat = new Cat(600, 100);

	// Mouse   
	int mouse_win_x_; 
	int mouse_win_y_;
 
	//gameOver���� �� ��� ���
	int gameOverDelay;
	 
	// gravity 
	float gravity = 0.098f; 

	
	 
}; 

 


