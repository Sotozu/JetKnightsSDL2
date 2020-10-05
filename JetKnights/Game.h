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
	void genTestRobots();
	void genTestBullets();
	void genTestWeapon();
	void genTestObstacles();

	void WeaponFiring();
	void handleEvent(SDL_Event e);
	bool chkBorderCollision(Hitbox* b);
	bool chkRobotCollisions(Hitbox* b);
	void WeaponFiring(SDL_Event e);

	

private:
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;
	static const int TOTAL_IMAGES = 4;
	static const int TOTAL_ROBOTS = 2;
	static const int TOTAL_WEAPONS = 2;
	static const int TOTAL_BULLETS = 100;
	static const int TOTAL_OBSTACLES = 10;


	SDL_Renderer* gRenderer;
	
	std::vector<std::string> images;
	LTexture textures[TOTAL_IMAGES];
	NewRobot* robots[TOTAL_ROBOTS];
	NewWeapon* weapons[TOTAL_WEAPONS];
	Bullet* bullets[TOTAL_BULLETS];
	GameObject* obstacles[TOTAL_BULLETS];
	
	void loadMedia();
	void updateBullets();
	void updateRobots();
	void updateWeapons();
	void updateObstacles();

	
};

