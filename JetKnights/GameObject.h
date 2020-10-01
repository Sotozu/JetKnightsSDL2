#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Hitbox.h"

class GameObject {

public:
	GameObject();

	GameObject(int x, int y, float angle, SDL_Renderer* renderer);

	GameObject(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);


	void render();

	void setHitbox();
	void setHitbox(int h, int w, int offsetX, int offsetY);
	void setTexture(LTexture* tex);
	void setPos(int x, int y, float angle);
protected:
	SDL_Renderer* gRenderer;
	LTexture* texture;
	Hitbox hitbox;

	int posX;
	int posY;
	float ang;
	
	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;
};