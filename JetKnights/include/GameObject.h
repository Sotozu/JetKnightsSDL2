#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Hitbox.h"

class GameObject {
public:
	GameObject(int posX, int posY, float angle, SDL_Renderer* renderer);
	void render()
private:
	int x;
	int y;
	float ang;
	LTexture texture;
	Hitbox hitbox;
};


