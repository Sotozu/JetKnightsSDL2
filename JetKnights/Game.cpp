#include "Game.h"

Game::Game() {
	gRenderer = NULL;
}

Game::Game(SDL_Renderer* renderer) {
	const int totalImages = 1;
	std::string images[totalImages] = { "assets/bullet.png" };
	gRenderer = renderer;
	loadMedia();
	genTestBullets();
}

void Game::updateObjects() {
	for (int i = 0; i < totalBullets; ++i) {
		bullets[i].update();
		bullets[i].render();
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
	int n = 1;

	Bullet bullet1(10, 200, 0, n, gRenderer);
	bullet1.setTexture(&textures[0]);
	bullet1.setHitbox();
	Bullet bullet2(10, 300, 0, 2*n, gRenderer);
	bullet2.setTexture(&textures[0]);
	bullet2.setHitbox();
	Bullet bullet3(10, 400, 0, 4*n, gRenderer);
	bullet3.setTexture(&textures[0]);
	bullet3.setHitbox();

	bullets[0] = bullet1;
	bullets[1] = bullet2;
	bullets[2] = bullet3;
}

void Game::loadMedia() {
	for (int i = 0; i < totalImages; ++i) {
		textures[i].loadFromFile("assets/bullet.png", gRenderer);
		std::cout << "Texture loaded!!!" << std::endl;
	}
}
