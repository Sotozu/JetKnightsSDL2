#pragma once
#include <list>
#include <iostream>
#include <array>
#include <vector>
#include "Bullet.h"
#include <string>
#include <SDL_gamecontroller.h>
#include <iomanip>

#include "NewRobot.h"
#include "NewWeapon.h"


class Game {
public:
	//Constructor
	Game();
	Game(SDL_Renderer* renderer);

	//Accessors

	//Mutators
	void updateObjects();
	void genTestBullets();
	void genTestWeapon();
	void WeaponFiring();
	void handleEvent(SDL_Event e);
	bool chkRobotCollisions(Hitbox* b);

	void genTestRobots();

private:
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;
	static const int TOTAL_IMAGES = 3;
	static const int TOTAL_ROBOTS = 2;
	static const int TOTAL_WEAPONS = 2;
	static const int TOTAL_BULLETS = 100;


	SDL_Renderer* gRenderer;
	
	std::vector<std::string> images;
	LTexture textures[TOTAL_IMAGES];
	NewRobot* robots[TOTAL_ROBOTS];
	NewWeapon* weapons[TOTAL_WEAPONS];
	Bullet* bullets[TOTAL_BULLETS];
	
	void loadMedia();
	void updateBullets();
	void updateRobots();

	
};

