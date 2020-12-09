#pragma once
#include <SDL.h>
#include "LTexture.h"

class RelTexture {
public:
    RelTexture();
    RelTexture(float x, float y, float ang, LTexture* texture, SDL_Renderer* renderer);

    void render(float x, float y, float ang);

    int getWidth();
    int getHeight();

    //Data
    float x, y, ang;

private:
    LTexture texture;
    SDL_Renderer* renderer;
};

