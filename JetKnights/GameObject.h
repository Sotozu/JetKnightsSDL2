#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"
#include "Hitbox.h"
#include <iostream>
#include <SDL_gamecontroller.h>

class GameObject {

public:

	//Constructors
	GameObject();
	GameObject(int x, int y, float angle, SDL_Renderer* renderer);
	GameObject(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);

	//Mutators
	void setHitbox();
	void setHitbox(int h, int w, int offsetX, int offsetY);
	void setTexture(LTexture* tex);
	void setPos(int x, int y, float angle);

	//Accessors
	int getPosX();
	int getPosY();
	float getAng();

	//Pocesses
	void render();
protected:
	SDL_Renderer* gRenderer;
	LTexture* texture;
	Hitbox* hitbox;

	int posX;
	int posY;
	float ang;
	
	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;
};