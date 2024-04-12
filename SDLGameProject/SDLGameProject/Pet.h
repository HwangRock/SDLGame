#pragma once
#include <vector>
#include "Terrain.h"
#include "SDL.h"

class Pet
{
public:
	SDL_Rect pos;
	double v[2];
	bool jumping = false;

	Pet(double x, double y, double size);

	void Reset();
	virtual void Update(double timestep_s,std::vector<Terrain>& walls);

	void setPos(double x, double y) { pos_[0] = x; pos_[1] = y; }
	//void setVelocity(double x, double y) { v[0] = x; v[1] = y; }
	
	double size() const { return size_; }
	double mass() const { return mass_; }
	double coeff_of_restitution() { return coeff_of_restitution_; }
	double pos_x() const { return pos_[0]; }
	double pos_y() const { return pos_[1]; }
	double jumpSpeed() const { return jump_speed; }

protected:

	float jump_speed = -2.0f;

	double size_;
	double mass_;	// kg
	double coeff_of_restitution_; // from 0 o 1 ?????


	// position x,y
	double pos_[2];
	

};