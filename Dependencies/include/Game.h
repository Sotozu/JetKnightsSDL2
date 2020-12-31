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
#include "RelTexture.h"



class Game {
public:
	//Constructors
	Game(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	//Mutators
	void updateObjects(float);
	void genTestRobots();
	void genTestBullets(NewWeapon*);
	void genTestObstacles();
	void handleEvent(SDL_Event e);

	//Accessors
	std::string findWorkingDir();

	void playFightTheme();
	void playMenuTheme();
	void playPauseTheme();

	void stopMusic();



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

	// Mutators

	void loadMedia();
	void spawnBullets();

	void updateAllCollisions(std::list<Bullet*> bullets, float timeStep);

	//void updateRobotBulletCollisions(std::list<NewRobot*> robots, float timeStep);
	void updateRobotBulletCollisions(std::list<NewRobot*> robots, std::list<Bullet*> bullets, float timeStep);


	void updateAllRobotCollisionsX(std::list<NewRobot*> robots, float timeStep);
	void updateAllRobotCollisionsY(std::list<NewRobot*> robots, float timeStep);


	template<class T, class B>
	void updateCollisions(T* b, B items, float timeStep) {
		for (auto item : items) {
			b->updateCollision(item, timeStep);
		}
	}

	template<class T, class B>
	void updateCollisionsX(T* b, B items, float timeStep) {
		for (auto item : items) {
			b->updateCollisionX(item, timeStep);
		}
	}

	template<class T, class B>
	void updateCollisionsY(T* b, B items, float timeStep) {
		for (auto item : items) {
			b->updateCollisionY(item, timeStep);
		}
	}


	/*SEPERATES THE BULLET COLLISION FROM THE OBSTACLE AND ROBOT
	THIS IS CALLED IN Game.cpp
	"void Game::updateAllCollisions(std::list<NewRobot*> robotlist, float timeStep)"*/

	template<class T, class B>
	void updateBulletCollisions(T* b, B items, float timeStep) {
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
	void updateRobotMovements(B items, float timeStep) {
		for (auto item : items) {

			item->updatePosX(timeStep);
			/*Check for collision AND IF SO revert back to previous position*/
			updateAllRobotCollisionsX(robots, timeStep);

			item->updatePosY(timeStep);
			/*Check for collision AND IF SO revert back to previous position*/
			updateAllRobotCollisionsY(robots, timeStep);
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

	// Recursively checks objects for weapons and fires them
	template<class T>
	void spawnBulletsRecursive(T &object) {
		for (auto &varObj : object.children) {
			if (auto weapon = std::get_if<NewWeapon>(&varObj)) {
				// Fire Weapon check
				if (weapon->isFiring && weapon->canFire() && weapon->isActive) {
					weapon->attemptToFire();
					genTestBullets(weapon);
					//weapon->weaponSounds();
					//soundEffects.playgLow();
				}
			}
			std::visit([&](auto& child) {
				spawnBulletsRecursive(child);
			}, varObj);
		}
	}
	
	
};