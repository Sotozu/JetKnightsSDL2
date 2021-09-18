#pragma once
#include <SDL.h>
#include "LTexture.h"

class RelTexture {
public:
    RelTexture();
    RelTexture(float m_x, float m_y, float ang, LTexture* texture, SDL_Renderer* renderer);

    void render(float m_x, float m_y, float ang);

    // Accesors
    int getWidth();
    int getHeight();

    // Data
    float m_x, m_y, ang;

private:
    LTexture texture;
    SDL_Renderer* renderer;
};

