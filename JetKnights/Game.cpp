#include "Game.h"

Game::Game() {
	gRenderer = NULL;
	
}

Game::Game(SDL_Renderer* renderer) {
	gRenderer = renderer;
	genTestBullets();
}

void Game::updateObjects() {
	for (Bullet bullet : bullets) {
		bullet.update();
		bullet.render();
	}
	//for object in objects
		//process events
		//gen
		//update position
	//for object in objecs
		//if(object.chkCollision())
			//on_collision()
	//for object in objects
		//object.render
	
}

void Game::genTestBullets() {
	Bullet bullet1(10, 100, 0, 1, gRenderer);
	Bullet bullet2(10, 200, 0, 2, gRenderer);
	Bullet bullet3(10, 300, 0, 4, gRenderer);

	bullets.push_back(bullet1);
	bullets.push_back(bullet2);
	bullets.push_back(bullet3);
}