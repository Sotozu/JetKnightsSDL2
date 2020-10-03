#pragma once
#include <list>
#include <iostream>
#include <array>
#include <vector>
#include "Bullet.h"
#include <string>
#include <SDL_gamecontroller.h>
#include "NewWeapon.h"
#include <iomanip>

class Game {
public:
	//Constructor
	Game();
	Game(SDL_Renderer* renderer);

	//Accessors

	//Mutators
	void moveWeapon(SDL_Event);
	
	//Processes

	void updateObjects();
	void genTestBullets();
	void WeaponFiring();
	void handlEvent(SDL_Event);

private:

	static const int TOTAL_IMAGES = 3;
	static const int TOTAL_BULLETS = 100;

	SDL_Renderer* gRenderer;

	NewWeapon slot1player1;
	
	std::vector<std::string> images;
	LTexture textures[TOTAL_IMAGES];
	Bullet* bullets[TOTAL_BULLETS];
	
	void loadMedia();
};

