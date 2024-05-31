#pragma once
#include <vector>

#include "Terrain.h"
#include "Button.h"
#include "LiquidWall.h"
#include "ClimbWall.cpp"
#include "Cushion.h"
#include "FadeFloor.h"


#include "SDL.h"



class Pet
{
public:
	SDL_Rect pos;
	bool isDead;
	double v[2];
	bool jumping;

	bool isInGoal;//does it reach in goal
	int isPressCushion;
	bool haveKey;
	int nowInput;

	Pet(double x, double y);
	
	void Reset();
	virtual void Update( double timestep_s	);

	void HandleEvent(SDL_Event event);

	virtual void BlockMoving(SDL_Rect obst);


	void setPos(double x, double y) { pos_[0] = x; pos_[1] = y; }
	//void setVelocity(double x, double y) { v[0] = x; v[1] = y; }
	
	double size() const { return size_; }
	double mass() const { return mass_; }
	double coeff_of_restitution() { return coeff_of_restitution_; }
	double pos_x() const { return pos_[0]; }
	double pos_y() const { return pos_[1]; }
	double jumpSpeed() const { return jump_speed; }
	void resetInputs() { inputs.clear(); inputs.push_back(0); }

protected:

	float jump_speed = -3.5f;

	
	double size_;
	double mass_;	// kg
	double coeff_of_restitution_; // from 0 o 1 ?????


	// position x,y
	double pos_[2];
	bool isDog;
	
	
	float gravity = 0.098f;

	//key input
	int keyUpNum;
	int keyDownNum;
	std::vector<int> inputs;

};
