#include "Game.h"

Game::Game() {
	gRenderer = NULL;
}

Game::Game(SDL_Renderer* renderer) {
	//const int totalImages = 3;
	//const int totalBullets = 3;
	gRenderer = renderer;
	for (int i = 0; i < TOTAL_BULLETS; i++) {
		bullets[i] = NULL;
	}
	images =  { "assets/robotrightnew.png",
				"assets/cannonsmall.png",
				"assets/bullet.png" };
	loadMedia();
	genTestBullets();
}

void Game::updateObjects() {
	//updateRobots();
	updateBullets();
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

void Game::updateBullets() {
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			bullets[i]->update();
		}
	}
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			if (bullets[i]->chkCollision(SCREEN_WIDTH, SCREEN_HEIGHT)) {
				delete bullets[i];
				bullets[i] = NULL;
			}
		}
	}
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			bullets[i]->render();
		}
	}
}

void Game::genTestBullets() {
	int n = 1;
	int n_bullets = 3;
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] == NULL && n_bullets > 0) {
			bullets[i] = new Bullet(10, 200 + n_bullets * 100, 0.0, n * pow(2, n_bullets), gRenderer, &textures[2]);
			//std::cout << i << std::endl;
			n_bullets--;
		}
	}
}

void Game::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		textures[i].loadFromFile(images[i], gRenderer);
		//std::cout << "Texture loaded!!!" << std::endl;
	}
}
