#include "SDL.h"
#include <cmath>
#include <iostream>

const int SEESAW_LENGTH = 200;
const int SEESAW_HEIGHT = 20;
const double GRAVITY = 0.1;
const double DAMPING = 0.99;
const double FORCE = 0.009;


class Seesaw {
public:
    SDL_Rect pos;
    double angle, angleVelocity, angleAcceleration;

    Seesaw(SDL_Rect p) 
        : pos(p), angle(0.0), angleVelocity(0.0), angleAcceleration(0.0) 
    {   }

    ~Seesaw() {
    }

    void update() 
    {
        angleVelocity += angleAcceleration;
        angleVelocity *= DAMPING;
        angle += angleVelocity;

        // Natural damping and gravity to bring the seesaw back to the original position
        angleAcceleration = -0.005 * angle;  
        // Assuming a simple proportional control for restoring force

        // Prevent the seesaw from rotating too far
        if (angle > M_PI / 1.5) 
        {
            angle = M_PI / 1.5;
            angleVelocity = 0;
        }
        else if (angle < -M_PI / 1.5) 
        {
            angle = -M_PI / 1.5;
            angleVelocity = 0;
        }
    }


    SDL_Rect getRect() {
        int rectX = pos.x - pos.w / 2;
        int rectY = pos.y - pos.h / 2;
        return SDL_Rect{ rectX, rectY, pos.w, pos.h };
    }

    void applyForce(double force) {
        angleAcceleration += force;
    }


private:
    

};


        



