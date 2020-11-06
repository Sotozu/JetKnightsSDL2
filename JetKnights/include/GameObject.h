#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_gamecontroller.h>
#include <list>
#include <variant>

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
	void setHitbox();
	void setHitbox(int h, int w, int offsetX, int offsetY);
	void setTexture(LTexture&);
	void setPos(int x, int y, float angle);
	void setTeam(int);
	
	void update(float);

	//template<class T>
	//void addChild(T child) {
	//	childObjects.push_back(child);
	//}

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
		//if (hitboxes.size() != 0 && b->hitboxes.size() != 0 && team != b->team && !isDead && !b->isDead) {
		//	return hitbox->chkCollision(b->getHitbox());
		//}
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
	//std::list<std::variant<GameObject, NewRobot, NewWeapon>> childs;
	std::list<LTexture> textures;
	std::list<Hitbox> hitboxes;

	float ang;

	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;

	float* relX;
	float* relY;
};