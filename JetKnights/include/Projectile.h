#pragma once
#include "LTexture.h"
#include <SDL.h>
#include <iostream>

class Projectile
{
public:

	//Initialize position and animation
	Projectile(int x, int y, float angle, SDL_Renderer* renderer, LTexture* texture);

	//Shows the particle
	void render(SDL_Renderer* gRenderer);

	//Checks if particle is dead
	//bool isDead();

	void update();

private:
	SDL_Renderer* mRenderer;
	LTexture* mTexture;

	int counter;
	int mPosX;
	int mPosY;
	int speed;
	float mAngle;
	bool isDead;
};