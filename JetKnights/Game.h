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
	const int totalImages = 3;
	const int totalBullets = 3;
	SDL_Renderer* gRenderer;
	
	std::string images[3];
	LTexture textures[3];
	Bullet* bullets[3];
	
	void loadMedia();
};

