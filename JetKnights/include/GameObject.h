#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_gamecontroller.h>
#include <list>
#include <variant>

#include "LTexture.h"
#include "Hitbox.h"


// Declaring classes that will go into the variant
class GameObject;
class NewRobot;
class NewWeapon;
class Bullet;

class GameObject {

public:

	//Constructors
	GameObject();
	GameObject(int x, int y, float angle, SDL_Renderer* renderer);
	GameObject(int x, int y, float angle, SDL_Renderer* renderer, LTexture* );

	//Mutators
	void addHitbox();
	void setTeam(int);

	void setOrigin(float x, float y);
	void setPos(int x, int y, float angle);
	void setPosRelative(int x, int y, float angle);
	void updatePos();

	void updateSelf();
	void updateChildren();
	

	// Dirty way to get relative objects, create nested multi-objects instead.
	template <class T>
	void setRelative(T* relativeObject) {
		relXp = &relativeObject->posX;
		relYp = &relativeObject->posY;
	}

	template <class T>
	void addChild(T &childObj) {
		childObj.setOrigin(getPosX(), getPosY());
		children.push_back(childObj);
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

	std::list<std::variant<GameObject, NewRobot, NewWeapon, Bullet>> children;

	bool isDead;
	bool isRelative;
	int team;

	float oriX, oriY; //Absolute origin
	float relX, relY; //Relative position
	float posX, posY; //Absolute position

protected:
	SDL_Renderer* gRenderer;
	std::list<LTexture> textures;
	std::list<Hitbox> hitboxes;

	float ang;

	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;

	float* relXp;
	float* relYp;
};


// Headers for classes in the variant included here
#include "NewRobot.h"
#include "NewWeapon.h"
#include "Bullet.h"