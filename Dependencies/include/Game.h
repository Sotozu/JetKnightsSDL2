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

#include "IGameObject.h"
#include "Arena.h"
#include "Obstacle.h"

#include "LTimer.h"
#include "Sound.h"
#include "RelTexture.h"
/*
#include "GameObject.h"
#include "NewRobot.h"
#include "NewWeapon.h"
#include "Bullet.h"
#include "StatusBar.h"

*/


class Game {
public:
	//Default Constructors
	Game();

	//Constructors

	Game(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, 
		SDL_GameController* CONTROLLER1, SDL_GameController* CONTROLLER2);

	//Mutators

	void initialize(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, 
		SDL_GameController* CONTROLLER1, SDL_GameController* CONTROLLER2);

	void pauseGame(SDL_Event e);
	void unpauseGame();

	void update(float);
	void handleEvent(SDL_Event e);

	//void genTestRobots();
	//void genTestBullets(NewWeapon*);
	//void genTestObstacles();

	void genTestArena();

	
	//Accessors
	std::string findWorkingDir();

	void playFightTheme();
	void playMenuTheme();
	void playPauseTheme();

	void stopMusic();



private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	bool isPaused;
	
	static const int TOTAL_IMAGES = 6;

	SDL_Renderer* gRenderer;
	
	std::string workingDir;
	std::vector<std::string> images;

	LTexture textures[TOTAL_IMAGES];

	Sound soundEffects;

	IGameObject* mainObj; // The "main" ojbect of the game, typically a map or screen

	//std::list<StatusBar*> bars;
	
	LTimer timeTracker;

	SDL_GameController* gGameController0;
	SDL_GameController* gGameController1;


	// Mutators

	void loadMedia();
	//void spawnBullets();


	// Removes dead items from the list
	/*
	void deleteDeadObjects() {
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
	*/

	// Recursively checks objects for weapons and fires them
	template<class T>
	void spawnBulletsRecursive(T &object) {
		/*
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
		*/
	}
	
	
};