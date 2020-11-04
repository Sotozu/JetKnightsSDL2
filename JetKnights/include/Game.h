#pragma once
#include <list>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <SDL_gamecontroller.h>
#include <iomanip>
#include <SDL_mixer.h>
#include <windows.h>

#include "GameObject.h"
#include "NewRobot.h"
#include "NewWeapon.h"
#include "Bullet.h"
#include "StatusBar.h"
#include "LTimer.h"
#include "Sound.h"



class Game {
public:
	//Constructors
	Game(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

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
	void updateObjects2(float);
	void genTestRobots();
	void genTestBullets(int);
	void genTestWeapon();
	void genTestObstacles();
	
	void handleEvent(SDL_Event e);

	std::string findWorkingDir();

	void playFightTheme();

private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	
	static const int TOTAL_IMAGES = 4;
	static const int TOTAL_ROBOTS = 2;
	static const int TOTAL_WEAPONS = 2;
	static const int TOTAL_BULLETS = 1000;
	static const int TOTAL_OBSTACLES = 10;

	SDL_Renderer* gRenderer;
	
	std::string workingDir;
	std::vector<std::string> images;

	LTexture textures[TOTAL_IMAGES];

	Sound soundEffects;

	NewRobot* robots[TOTAL_ROBOTS];
	NewWeapon* weapons[TOTAL_WEAPONS];
	Bullet* bullets[TOTAL_BULLETS];
	GameObject* obstacles[TOTAL_BULLETS];

	std::list<StatusBar*> bars;
	
	LTimer timeTracker;

	//Mutators

	void loadMedia();
	void updatePlayerBoost();
	void updateBulletMovement();
	void updateRobots();
	void updateWeapons();
	void updateObstacles();
	

	void spawnBullets();

	void updateAllCollisions(Bullet* array[], int length, float timeStep);
	void updateAllCollisions(NewRobot* array[], int length, float timeStep);

	template<class T, class B>
	void updateCollisions(T* b, B* array[], int length, float timeStep) {
		for (int i = 0; i < length; ++i) {
			if (array[i] != NULL) {
				b->updateCollision(array[i], timeStep);
			}
		}
	}

	template<class B>
	void updateMovements(B* array[], int length, float timeStep) {
		for (int i = 0; i < length; ++i) {
			if (array[i] != NULL) {
				array[i]->update(timeStep);
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