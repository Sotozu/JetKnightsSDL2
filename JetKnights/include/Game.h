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
#include <variant>

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

	void playFightTheme();

private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	
	static const int TOTAL_IMAGES = 4;

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
	void spawnBulletsRecursive();
	void updateAllCollisions(std::list<Bullet*> bullets, float timeStep);
	void updateAllCollisions(std::list<NewRobot*> robots, float timeStep);

	template<class T, class B>
	void updateCollisions(T* b, B items, float timeStep) {
		for (auto item : items) {
			b->updateCollision(item, timeStep);
		}
	}

	template<class B>
	void updateMovements(B items, float timeStep) {
		for (auto item : items) {
			item->update(timeStep);
		}
	}

	template<class B>
	void updateRenders(B items) {
		for (auto item : items) {
			item->render();
		}
	}

	// Removes dead items from the list
	template<class B>
	void despawn(B* items) {
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

	template<class T>
	void spawnBulletsRecursive(T &object) {
		for (auto &varObj : object.children) {
			if (auto weapon = std::get_if<NewWeapon>(&varObj)) {
				std::cout << varObj.index() << " WEAPON" << std::endl;
				if (weapon->isFiring & weapon->canFire()) {
					weapon->attemptToFire();
					genTestBullets(weapon);
					soundEffects.playgLow();
				}
			}
			else {
				std::cout << varObj.index() << std::endl;
			}
			std::visit([&](auto& child) {
				spawnBulletsRecursive(child);
			}, varObj);
		}
	}
	
	
};