#include "flyingBox.h"

flyingBox::flyingBox(SDL_Rect start, SDL_Rect end) : movingObject() {
    startPoint = start;
    endPoint = end;
    direction = 0;
    speed = 2.0f;
    isColision = false;
    Reset();
}

void flyingBox::Reset() {
    currentLocation = startPoint;
}

void flyingBox::Update() {
    int finish = endPoint.x;
    int start = startPoint.x;
    int current = currentLocation.x;


    if (direction == 0 && current >= finish) {
        direction = 1;
    }
    if (direction == 1 && current <= start) {
        direction = 0;
    }


    if (direction == 0) {
        current += speed;
    }
    else {
        current -= speed;
    }

    currentLocation = { current, currentLocation.y, currentLocation.w, currentLocation.h };
}
