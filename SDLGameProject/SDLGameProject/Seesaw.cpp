#include "Seesaw.h"
#include <cmath>


const double DAMPING = 0.99;

Seesaw::Seesaw(SDL_Rect p)
    : pos(p), angle(0.0), angleVelocity(0.0), angleAcceleration(0.0)
{}


void Seesaw::update() {
    angleVelocity += angleAcceleration;
    angleVelocity *= DAMPING;
    angle += angleVelocity;

    // Natural damping and gravity to bring the seesaw back to the original position
    angleAcceleration = -0.005 * angle;

    // Prevent the seesaw from rotating too far
    if (angle > M_PI / 1.5) {
        angle = M_PI / 1.5;
        angleVelocity = 0;
    }
    else if (angle < -M_PI / 1.5) {
        angle = -M_PI / 1.5;
        angleVelocity = 0;
    }
}

SDL_Rect Seesaw::getRect() {
    int rectX = pos.x - pos.w / 2;
    int rectY = pos.y - pos.h / 2;
    return SDL_Rect{ rectX, rectY, pos.w, pos.h };
}

void Seesaw::applyForce(double force) {
    angleAcceleration += force;
}
