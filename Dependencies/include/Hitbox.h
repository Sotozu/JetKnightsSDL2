#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Hitbox {
public:
	// Constructors
	Hitbox();
	Hitbox(int width, int height);

	// Mutators
	void setParameters(int x, int y, int width, int height);

	// Accessors
	bool chkCollision(Hitbox* b);
	bool chkBorderCollisionX(int);
	bool chkBorderCollisionY(int);

	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();

	SDL_Rect* getRect();

	void renderAll(float posX, float posY);
	void renderOrigin(float posX, float posY);

private:
	float x;
	float y;
	float w; // Width
	float h; // Height
};
