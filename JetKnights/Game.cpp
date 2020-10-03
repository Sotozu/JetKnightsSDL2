#include "Game.h"

Game::Game() {
	gRenderer = NULL;
}

Game::Game(SDL_Renderer* renderer) {
	const int totalImages = 3;
	const int totalBullets = 3;
	gRenderer = renderer;
	std::string images[totalImages] = { "assets/robotrightnew.png",
										"assets/cannonsmall.png",
										"assets/bullet.png" };
	loadMedia();
	genTestBullets();
}

void Game::updateObjects() {
	for (int i = 0; i < totalBullets; ++i) {
		bullets[i]->update();
		bullets[i]->render();
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
	for (int i = 0; i < totalBullets; ++i) {
		bullets[i] = new Bullet(10, 200 + i * 100, 0, n * pow(2, i), gRenderer, &textures[2]);
	}
}

void Game::loadMedia() {
	for (int i = 0; i < totalImages; ++i) {
		textures[i].loadFromFile("assets/bullet.png", gRenderer);
		std::cout << "Texture loaded!!!" << std::endl;
	}
}
