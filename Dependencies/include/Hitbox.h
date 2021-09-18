#pragma once

#include "Constants.h"
#include "IGameObject.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class IGameObject;

class Hitbox {
public:
	// Constructors
	Hitbox();
	Hitbox(int width, int height);

	// Mutators
	void setParameters(int m_x, int m_y, int width, int height);

	// Accessors
	bool chkCollision(Hitbox& b);
	bool chkBorderCollisionX(int);
	bool chkBorderCollisionY(int);

	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();

	SDL_Rect* getRect();

	void renderAll(float posX, float posY);
	void renderOrigin(float posX, float posY);

	IGameObject* parentObj;

private:
	float m_x;
	float m_y;
	float m_w; // Width
	float m_h; // Height
};
