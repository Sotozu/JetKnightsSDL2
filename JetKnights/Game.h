#pragma once
#include <list>
#include <iostream>
#include "Bullet.h"

class Game {
public:
	Game();
	Game(SDL_Renderer* renderer);

	void updateObjects();
	void genTestBullets();
private:
	const int totalImages = 1;
	const int totalBullets = 3;
	SDL_Renderer* gRenderer;
	
	std::string images[1];
	LTexture textures[1];
	Bullet bullets[3];
	
	void loadMedia();
};

