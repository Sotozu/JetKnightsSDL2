#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Hitbox.h"

class GameObject {
public:
	GameObject();
	GameObject(int x, int y, float angle, int speed, SDL_Renderer* renderer);
	void render();
	void update();

	void setHitbox(int h, int w, int offsetX, int offsetY);
	void setTexture(LTexture* tex);

	int getVelX();
	int getVelY();
private:
	SDL_Renderer* gRenderer;
	LTexture* texture;
	Hitbox hitbox;

	int posX;
	int posY;
	int mSpeed;
	float ang;
	
	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;
};