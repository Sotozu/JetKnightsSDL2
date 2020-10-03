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
	//Iniitialize Weapon

}

void Game::updateObjects() {
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			//std::cout << "UPDATE ATTEMPTED" << std::endl;
			bullets[i]->update();
			bullets[i]->render();
		}
	}

	for (int i = 0; i < TOTAL_WEAPONS; ++i) {
		if (weapons[i] != NULL) {
			weapons[i]->setPos(300, 300, 0);
			weapons[i]->update();
			weapons[i]->render();
		}
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
	int n_bullets = 1;
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] == NULL && n_bullets > 0) {
			bullets[i] = new Bullet(10, 200 + n_bullets * 100, 0, n * pow(2, n_bullets), gRenderer, &textures[2]);
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


void Game::WeaponFiring() {
	genTestBullets();
}


void Game::handlEvent(SDL_Event e) {

	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (weapons[i] != NULL) {
			weapons[i]->handleEvent(e);
		}
	}
	
}


void  Game::genTestWeapon() {
	weapons[0] = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
}
