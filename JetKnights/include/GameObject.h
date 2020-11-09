#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_gamecontroller.h>
#include <list>
//#include <variant>

#include "LTexture.h"
#include "Hitbox.h"
//#include "NewRobot.h"  //including causes error
//#include "NewWeapon.h" //including causes error

class GameObject {

public:

	//Constructors
	GameObject();
	GameObject(int x, int y, float angle, SDL_Renderer* renderer);
	GameObject(int x, int y, float angle, SDL_Renderer* renderer, LTexture* );

	//Mutators
	void addHitbox();

	void setPos(int x, int y, float angle);
	void setTeam(int);

	// Dirty way to get relative objects, create nested multi-objects instead.
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
	bool chkCollision(T* otherObj) {
		if (team != otherObj->team && !isDead && !otherObj->isDead) {
			for (auto hitbox1 : hitboxes) {
				for (auto hitbox2 : otherObj->hitboxes) {
					if (hitbox1.chkCollision(&hitbox2) == true) {
						return true;
					}
				}
			}
		}
		return false;
	}

	
	
	//Data
	bool isDead;
	bool isRelative;
	int team;

	float posX;
	float posY;

protected:
	SDL_Renderer* gRenderer;
	std::list<LTexture> textures;
	std::list<Hitbox> hitboxes;

	//std::list<std::variant<GameObject, NewRobot, NewWeapon>> childs;

	float ang;

	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;

	float* relX;
	float* relY;
};