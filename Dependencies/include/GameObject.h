#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_gamecontroller.h>
#include <list>
#include <vector>
#include <variant>

#include "LTexture.h"
#include "RelTexture.h"
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
	GameObject(int m_x, int m_y, float angle, SDL_Renderer* renderer);
	GameObject(int m_x, int m_y, float angle, SDL_Renderer* renderer, RelTexture* texture );

	//Mutators
	void addHitbox();
	void setTeam(int);

	void setOrigin(float m_x, float m_y);
	void setPos(int m_x, int m_y, float angle);
	void setPosRelative(int m_x, int m_y, float angle);
	void updatePos();

	void update(float timestep);
	void updateChildren(float timeStep);
	void handleEvent(SDL_Event e);
	void passOnEvent(SDL_Event e);

	template <class T>
	void addChild(T &childObj) {
		childObj.setOrigin(getPosX(), getPosY());
		childObj.setTeam(this->team);
		children.push_back(childObj);
	}

	//Accessors
	int getPosX();
	int getPosY();
	float getAng();
	Hitbox* getHitbox();

	//Pocesses
	void render();
	void renderTextures();
	void renderHitboxes();
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
	bool isActive;
	bool isRelative;
	int team;

	float oriX, oriY; //Absolute origin
	float relX, relY; //Relative position
	float posX, posY; //Absolute position

protected:
	SDL_Renderer* gRenderer;
	std::list<RelTexture> textures;
	std::list<Hitbox> hitboxes;

	float ang;

	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;
};


// Headers for classes in the variant included here
#include "NewRobot.h"
#include "NewWeapon.h"
#include "Bullet.h"