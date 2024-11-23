#include "robot.h"

robot::robot(SDL_Rect start, SDL_Rect end) : movingObject() {
    startPoint = start;
    endPoint = end;
    direction = false;
    speed = 2.0f;
    isColision = false;
    Reset();
}

void robot::Reset() {
    currentLocation = startPoint;
}

void robot::Update() {
    int finish = endPoint.x;
    int start = startPoint.x;
    int current = currentLocation.x;

    if (!direction && current >= finish) {
        direction = true;
    }
    if (direction && current <= start) {
        direction = false;
    }

    if (!direction) {
        current += speed;
    }
    else {
        current -= speed;
    }

    // x ��ǥ�� ������Ʈ�Ͽ� ���� y, w, h �� ����
    currentLocation.x = current;
}
