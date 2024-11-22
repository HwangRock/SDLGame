#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include "Terrain.h"
#include <vector>

class Torch 
{
public:
    std::vector<SDL_Rect> dark_; //어두운 부분
    bool isTouched;
    std::vector<SDL_Rect> torchPos;
    int torchNum_;
    int darkNum_;
    int opacity;

    Torch
    (
        int torchNum, int darkNum,
        std::vector<SDL_Rect> dark,
        std::vector<SDL_Rect> torchP,
        int opacity
    );

    void Touch(bool t);

    void Reset();

    virtual void Update();

protected:

};