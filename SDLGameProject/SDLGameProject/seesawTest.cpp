
/*
#include "SDL.h"
#include <cmath>
#include <iostream>

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PET_SIZE = 50;
const int SEESAW_LENGTH = 200;
const int SEESAW_HEIGHT = 20;
const double GRAVITY = 0.1;
const double DAMPING = 0.99;
const double FORCE = 0.009;

SDL_Renderer* renderer;

class Pet
{
public:
    Pet(int x, int y) { pos.x = x; pos.y = y; pos.w = PET_SIZE; pos.h = PET_SIZE; }

    SDL_Rect pos;
    void move(int dx, int dy) {
        pos.x += dx;
        pos.y += dy;
    }

    void draw() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
        SDL_RenderFillRect(renderer, &pos);
    }

    SDL_Rect getRect() {
        return pos;
    }
};

class Seesaw {
public:
    Seesaw(int x, int y, int length, int height)
        : x(x), y(y), length(length), height(height), angle(0.0), angleVelocity(0.0), angleAcceleration(0.0) {
        createTexture();
    }

    ~Seesaw() {
        SDL_DestroyTexture(texture);
    }

    void update() {
        angleVelocity += angleAcceleration;
        angleVelocity *= DAMPING;
        angle += angleVelocity;

        // Natural damping and gravity to bring the seesaw back to the original position
        angleAcceleration = -0.005 * angle;  // Assuming a simple proportional control for restoring force

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

    void draw() {
        SDL_Rect rect = getRect();
        SDL_Point center = { rect.w / 2, rect.h / 2 };

        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle * 180 / M_PI, &center, SDL_FLIP_NONE);

        // Draw seesaw center point for debugging
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        SDL_RenderDrawPoint(renderer, x, y);
    }

    SDL_Rect getRect() {
        int rectX = x - length / 2;
        int rectY = y - height / 2;
        return SDL_Rect{ rectX, rectY, length, height };
    }

    void applyForce(double force) {
        angleAcceleration += force;
    }

    double getAngle() const {
        return angle;
    }

private:
    int x, y, length, height;
    double angle, angleVelocity, angleAcceleration;
    SDL_Texture* texture;

    void createTexture() {
        SDL_Surface* surface = SDL_CreateRGBSurface(0, length, height, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 139, 69, 19)); // Brown color
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Seesaw and Pet Interaction", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    Seesaw seesaw(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SEESAW_LENGTH, SEESAW_HEIGHT);

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
                    pet.move(-5, 0);
                    break;
                case SDLK_RIGHT:
                    pet.move(5, 0);
                    break;
                case SDLK_UP:
                    pet.move(0, -5);
                    break;
                case SDLK_DOWN:
                    pet.move(0, 5);
                    break;
                }
            }
        }

        // Check for collision between pet and seesaw
        SDL_Rect petRect = pet.getRect();
        SDL_Rect seesawRect = seesaw.getRect();
        if (SDL_HasIntersection(&petRect, &seesawRect)) {
            if (petRect.x + petRect.w / 2 < seesawRect.x + seesawRect.w / 2)
            {
                std::cout << "left up\n";
                seesaw.applyForce(-FORCE);

            }
            else if (petRect.x + petRect.w / 2 > seesawRect.x + seesawRect.w / 2)
            {

                std::cout << "right up\n";
                seesaw.applyForce(FORCE);
            }
        }

        // Update seesaw
        seesaw.update();



        //Rernder///////////////////////////////////////////////////////////////////////
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderClear(renderer);

        // Draw seesaw
        seesaw.draw();

        // Draw pet
        pet.draw();

        // Refresh screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/