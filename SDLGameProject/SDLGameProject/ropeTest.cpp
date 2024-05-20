
/*
#include "SDL.h"
#include <cmath>
#include <iostream>

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PET_SIZE = 50;
const int ROPE_LENGTH = 200;
const int BALL_SIZE = 20;
const double GRAVITY = 0.1;
const double DAMPING = 0.99;

SDL_Renderer* renderer;

class Pet {
public:
    Pet(int x, int y) { pos.x = x; pos.y = y; }

    SDL_Rect pos;
    void move(int dx, int dy) {
        pos.x += dx;
        pos.y += dy;
    }

    void draw() {
        std::cout << "draw\n";
        std::cout << pos.x << ", " << pos.y << "\n";

    }

    SDL_Rect getRect() {
        return SDL_Rect{ pos.x, pos.y, PET_SIZE, PET_SIZE };
    }

    void BlockMoving(SDL_Rect obst)
    {
        if (pos.y + pos.h > obst.y + 5 &&
            pos.y < obst.y + obst.h - 5)
        {
            //벽왼쪽에 있음
            if (pos.x < obst.x + obst.w / 2)
            {
                //std::cout << "left\n";
                pos.x = obst.x - pos.w;
            }
            //벽 오른쪽에 있음
            else if (pos.x + pos.w > obst.x)
            {
                //std::cout << "right\n";
                pos.x = obst.x + obst.w;
            }

        }
        else
        {
            if (pos.y + pos.h <= obst.y + obst.h / 2)
            {
                //std::cout << "up\n";
                // 벽 위에 있음

                pos.y = obst.y - pos.h < pos.y ? obst.y - pos.h : pos.y;
            }
            else
            {
                //std::cout << "down\n";
                // 벽 아래에 있음
                pos.y = obst.y + obst.h > pos.y ? obst.y + obst.h : pos.y;

            }
        }
    }

private:

};


class Rope {
public:
    Rope(int anchorX, int anchorY, int length)
        : anchorX(anchorX), anchorY(anchorY), length(length), angle(M_PI / 4), angleVelocity(0), angleAcceleration(0) {}

    void update(Pet& pet) {
        angleAcceleration = (-1 * GRAVITY / length) * sin(angle);
        angleVelocity += angleAcceleration;
        angleVelocity *= DAMPING;
        angle += angleVelocity;

        pet.BlockMoving(ballRect);

    }

    void draw() {
        int ballX = anchorX + length * sin(angle);
        int ballY = anchorY + length * cos(angle);

        // SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // Gray color
        SDL_RenderDrawLine(renderer, anchorX, anchorY, ballX, ballY);

        ballRect = { ballX - BALL_SIZE * 4 / 2, ballY - BALL_SIZE / 2, BALL_SIZE * 4, BALL_SIZE };
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
        SDL_RenderFillRect(renderer, &ballRect);
    }

    SDL_Rect getBallRect() {
        int ballX = anchorX + length * sin(angle);
        int ballY = anchorY + length * cos(angle);
        return SDL_Rect{ ballX - BALL_SIZE * 4 / 2, ballY - BALL_SIZE / 2, BALL_SIZE * 4, BALL_SIZE };
    }

    void applyForce(double force) {
        angleVelocity += force;
    }

private:
    int anchorX, anchorY, length;
    double angle, angleVelocity, angleAcceleration;
    SDL_Rect ballRect;
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Rope and Pet Interaction", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    Pet pet(500, 300);
    Rope rope(WINDOW_WIDTH / 2, 50, ROPE_LENGTH);

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_LEFT:
                    pet.move(-2.5, 0);
                    break;
                case SDLK_RIGHT:
                    pet.move(2.5, 0);
                    break;
                case SDLK_UP:
                    pet.move(0, -2.5);
                    break;
                case SDLK_DOWN:
                    pet.move(0, 2.5);
                    break;
                }
            }
        }

        // Check for collision between pet and rope ball
        SDL_Rect petRect = pet.getRect();
        SDL_Rect ballRect = rope.getBallRect();
        if (SDL_HasIntersection(&petRect, &ballRect))
        {
            if (petRect.x - petRect.w / 2 < ballRect.x - ballRect.w / 2)
            {
                if (petRect.y + petRect.h > ballRect.y + 5 &&
                    petRect.y < ballRect.y + ballRect.h - 5)
                {
                    //위에 올라타 있지 않음
                    rope.applyForce(0.0003); std::cout << "left puch\n";
                }
                else
                {
                    //위에 올라타 있음
                    rope.applyForce(0.00001); std::cout << "left up\n";
                }
            }
            else if (petRect.x - petRect.w / 2 > ballRect.x - ballRect.w / 2)
            {
                if (petRect.y + petRect.h > ballRect.y + 5 &&
                    petRect.y < ballRect.y + ballRect.h - 5)
                {
                    //위에 올라타 있지 않음
                    rope.applyForce(-0.0003); std::cout << "right puch\n";
                }
                else
                {
                    //위에 올라타 있음
                    rope.applyForce(-0.00001); std::cout << "right up\n";
                }
            }
            // Apply a force to the rope if it collides with the pet
        }

        // Update rope
        rope.update(pet);

        //RENDER///////////////////////////////////////////////////////////////////////////
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);




        // Draw rope
        rope.draw();
        //std::cout << "draw pet\n";
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        // Draw pets
        //std::cout << pet.pos.x;
        SDL_Rect rect = { pet.pos.x, pet.pos.y, PET_SIZE, PET_SIZE };
        SDL_RenderFillRect(renderer, &rect);


        // Refresh screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/