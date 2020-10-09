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
	//Constructors
	Game(SDL_Renderer* renderer);

	//Accessors
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

	//Mutators
	void updateObjects2();
	void genTestRobots();
	void genTestBullets(int);
	void genTestWeapon();
	void genTestObstacles();
	
	void handleEvent(SDL_Event e);

private:
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;
	static const int TOTAL_IMAGES = 4;
	static const int TOTAL_ROBOTS = 2;
	static const int TOTAL_WEAPONS = 2;
	static const int TOTAL_BULLETS = 1000;
	static const int TOTAL_OBSTACLES = 10;

	SDL_Renderer* gRenderer;
	
	std::vector<std::string> images;
	LTexture textures[TOTAL_IMAGES];
	NewRobot* robots[TOTAL_ROBOTS];
	NewWeapon* weapons[TOTAL_WEAPONS];
	Bullet* bullets[TOTAL_BULLETS];
	GameObject* obstacles[TOTAL_BULLETS];
	
	//Mutators

	void loadMedia();

	void spawnBullets();

	void updateAllCollisions(Bullet* array[], int length);
	void updateAllCollisions(NewRobot* array[], int length);

	template<class T, class B>
	void updateCollisions(T* b, B* array[], int length) {
		for (int i = 0; i < length; ++i) {
			if (array[i] != NULL) {
				b->updateCollision(array[i]);
			}
		}
	}

	template<class B>
	void updateMovements(B* array[], int length) {
		for (int i = 0; i < length; ++i) {
			if (array[i] != NULL) {
				array[i]->update();
			}
		}
	}

	template<class B>
	void updateRenders(B* array[], int length) {
		for (int i = 0; i < length; ++i) {
			if (array[i] != NULL) {
				array[i]->render();
			}
		}
	}

	template<class B>
	void despawn(B* array[], int length) {
		for (int i = 0; i < length; ++i) {
			if (array[i] != NULL && array[i]->isDead) {
				delete array[i];
				array[i] = NULL;
			}
		}
	}
	
};

