#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_gamecontroller.h>
#include "LTexture.h"
#include "Hitbox.h"

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
	void setTeam(int);

	// Dirty way to get relative objects, create a nested multi-object instead.
	// This was a quick fix to make the weapons work with lists implemented.
	template <class T>
	void setRelative(T* relativeObject) {
		relX = &relativeObject->posX;
		relY = &relativeObject->posY;
	}

	//Accessors
	int getPosX();
	int getPosY();
	float getAng();
	Hitbox* getHitbox();

	//Pocesses
	void render();
	bool chkBorderCollision(int, int);

	template <class T>
	bool chkCollision(T* b) {
		if (hitbox != NULL && b->hitbox != NULL && team != b->team && !isDead && !b->isDead) {
			return hitbox->chkCollision(b->getHitbox());
		}
		return false;
	}
	
	//Data
	bool isDead;
	int team;

	float posX;
	float posY;

protected:
	SDL_Renderer* gRenderer;
	LTexture* texture;
	Hitbox* hitbox;

	float ang;

	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;

	float* relX;
	float* relY;
};