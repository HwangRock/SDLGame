#include "Game.h"
#include "FinishGame.h"

int cnt = 0;

Finish::Finish()
{
    // For Texture
    SDL_Surface* temp_surface = IMG_Load("../Resources/finish.png");
    texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
    SDL_FreeSurface(temp_surface);

    SDL_QueryTexture(texture_, NULL, NULL, &source_rectangle_.w, &source_rectangle_.h);
    destination_rectangle_.x = 0;
    destination_rectangle_.y = 0;
    destination_rectangle_.w = 1280;
    destination_rectangle_.h = 700;

    // Initialize the source rectangle with the first coordinates and size
    UpdateSourceRectangle();
}

Finish::~Finish()
{
    SDL_DestroyTexture(texture_);
}

void Finish::Update()
{
    // No update logic required as per the current requirements
}

void Finish::Render()
{
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    SDL_RenderClear(g_renderer); // clear the renderer to the draw color

    SDL_RenderCopy(g_renderer, texture_, &source_rectangle_, &destination_rectangle_);

    SDL_RenderPresent(g_renderer); // draw to the screen
}

void Finish::HandleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_KEYDOWN:
            if (cnt != 6) {
                cnt++;
                UpdateSourceRectangle();
            }
            else {
                g_current_game_phase = PHASE_INTRO;
                cnt = 0;
                musOnOff = false;
                phase1first = true;
                UpdateSourceRectangle();
            }
            break;

        default:
            break;
        }
    }
}

void Finish::UpdateSourceRectangle()
{
    // Define an array of source rectangles
    SDL_Rect source_rects[] = {
        {136, 182, 596, 335},
        {756, 182, 596, 335},
        {136, 588, 596, 335},
        {756, 588, 596, 335},
        {136, 1000, 596, 335},
        {756, 1000, 596, 335},
        {136, 1391, 596, 335}
    };

    // Update the source rectangle based on the current count
    source_rectangle_ = source_rects[cnt];

   
}
