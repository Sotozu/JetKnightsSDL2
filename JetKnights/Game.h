#pragma once
#include <list>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <SDL_gamecontroller.h>
#include <iomanip>

#include "GameObject.h"
#include "NewRobot.h"
#include "NewWeapon.h"
#include "Bullet.h"


class Game {
public:
	//Constructor

	Game(SDL_Renderer* renderer);

	//Accessors

	//Mutators
	void updateObjects();
	void genTestRobots();
	void updateBulletCreation();
	void genTestWeapon();
	void genTestObstacles();

	
	void handleEvent(SDL_Event e);
	
	//--Templates--
	//Checks class against array of classes for collision 
	template<class T, class B>
	bool chkCollisions(B* array[], int length, T* b) {
		for (int i = 0; i < length; ++i) {
			if (array[i] != NULL) {
				if (b->chkCollision(array[i])) {
					return true;
				}
			}
		}
		return false;
	}

	void WeaponFiring(SDL_Event e);

private:
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;
	static const int TOTAL_IMAGES = 4;
	static const int TOTAL_ROBOTS = 2;
	static const int TOTAL_WEAPONS = 2;
	static const int TOTAL_BULLETS = 1000;
	static const int TOTAL_OBSTACLES = 10;



	bool isWeaponFiring[TOTAL_WEAPONS];

	SDL_Renderer* gRenderer;
	
	std::vector<std::string> images;
	LTexture textures[TOTAL_IMAGES];
	NewRobot* robots[TOTAL_ROBOTS];
	NewWeapon* weapons[TOTAL_WEAPONS];
	Bullet* bullets[TOTAL_BULLETS];
	GameObject* obstacles[TOTAL_BULLETS];
	
	void loadMedia();
	void updateBulletMovement();
	void updateRobots();
	void updateWeapons();
	void updateObstacles();
	

	
};

