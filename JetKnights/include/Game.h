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

	//Mutators
	void updateObjects(float);
	void genTestRobots();
	void genTestBullets(NewWeapon*);
	void genTestWeapon();
	void genTestObstacles();
	void handleEvent(SDL_Event e);

	//Accessors
	std::string findWorkingDir();

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

	std::list<NewRobot*> robots;
	std::list<NewWeapon*> weapons;
	std::list<Bullet*> bullets;
	std::list<GameObject*> obstacles;

	std::list<StatusBar*> bars;
	
	LTimer timeTracker;

	//Mutators

	void loadMedia();
	void spawnBullets();
	void updateAllCollisions(std::list<Bullet*> bullets, int length, float timeStep);
	void updateAllCollisions(std::list<NewRobot*> robots, int length, float timeStep);

	template<class T, class B>
	void updateCollisions(T* b, B items, int length, float timeStep) {
		for (auto item : items) {
			b->updateCollision(item, timeStep);
		}
	}

	template<class B>
	void updateMovements(B items, int length, float timeStep) {
		for (auto item : items) {
			item->update(timeStep);
		}
	}

	template<class B>
	void updateRenders(B items, int length) {
		for (auto item : items) {
			item->render();
		}
	}

	// Removes dead items from the list
	template<class B>
	void despawn(B* items, int length) {
		class B::iterator it = items->begin();
		while (it != items->end()) {
			if ( (*it)->isDead ) {
				it = items->erase(it);
			}
			else {
				++it;
			}
		}
	}

	
	
};