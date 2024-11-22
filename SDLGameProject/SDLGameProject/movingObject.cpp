#include "movingObject.h"

movingObject::movingObject()
    : speed(0),
    isColision(false),
    startPoint{ 0, 0, 0, 0 },
    endPoint{ 0, 0, 0, 0 },
    currentLocation{ 0, 0, 0, 0 },
    direction(0) {}

void movingObject::Reset() {
    currentLocation = startPoint;
}

void movingObject::moving() {
    if (direction) {
        currentLocation.x -= speed;
    }
    else {
        currentLocation.x += speed;
    }
}
