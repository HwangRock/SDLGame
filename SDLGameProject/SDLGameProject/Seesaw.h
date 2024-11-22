#pragma once
#include "SDL_image.h"
#include <iostream>
#include "SDL.h"

class Seesaw {
public:
    SDL_Rect pos;
    double angle, angleVelocity, angleAcceleration;

    const int SEESAW_LENGTH = 200;
    const int SEESAW_HEIGHT = 20;
    const double GRAVITY = 0.1;
    const double DAMPING = 0.99;
    const double FORCE = 0.009;


    // Constructor and Destructor
    Seesaw(SDL_Rect p);


    void update();
    SDL_Rect getRect();
    void applyForce(double force);

    Seesaw& operator=(const Seesaw& other) {
        if (this == &other) return *this; // Self-assignment check
        pos = other.pos;
        angle = other.angle;
        angleVelocity = other.angleVelocity;
        angleAcceleration = other.angleAcceleration;
        return *this;
    }

private:

};
