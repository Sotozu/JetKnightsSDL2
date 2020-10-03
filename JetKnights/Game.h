#pragma once
#include <list>
#include <iostream>
#include <array>
#include <vector>
#include "Bullet.h"

class Game {
public:
	Game();
	Game(SDL_Renderer* renderer);

	void updateObjects();
	void genTestBullets();
private:
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;
	static const int TOTAL_IMAGES = 3;
	static const int TOTAL_BULLETS = 100;
	SDL_Renderer* gRenderer;

	std::vector<std::string> images;
	LTexture textures[TOTAL_IMAGES];
	Bullet* bullets[TOTAL_BULLETS];
	
	void loadMedia();
	void updateBullets();
};

