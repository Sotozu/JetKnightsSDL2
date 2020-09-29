#pragma once
#include <list>
#include "Bullet.h"

class Game {
public:
	Game();
	Game(SDL_Renderer* renderer);
	void updateObjects();
	void genTestBullets();
private:
	SDL_Renderer* gRenderer;
	std::list<Bullet> bullets;
	
};

