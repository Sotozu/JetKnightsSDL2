#include "Game.h"

Game::Game() {
	gRenderer = NULL;
}

Game::Game(SDL_Renderer* renderer) {
	//const int totalImages = 3;
	//const int totalBullets = 3;
	gRenderer = renderer;
	for (int i = 0; i < TOTAL_ROBOTS; i++) {
		robots[i] = NULL;
	}
	for (int i = 0; i < TOTAL_BULLETS; i++) {
		bullets[i] = NULL;
	}
	images =  { "assets/robotrightnew.png",
				"assets/cannonsmall.png",
				"assets/bullet.png" };
	loadMedia();

	genTestBullets();
	genTestRobots();
}

void Game::handleEvent(SDL_Event e) {
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {
			robots[i]->handleEvent(e);
		}

	}
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (weapons[i] != NULL) {
			weapons[i]->handleEvent(e);
		}
	}
}

void Game::updateObjects() {
	updateRobots();
	updateBullets();
}

void Game::updateRobots() {
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {
			robots[i]->update();
		}
	}
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {	
		if (robots[i] != NULL) {
			robots[i]->render();
		}
	}
}

void Game::updateBullets() {
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			bullets[i]->update();
		}
	}
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			if (bullets[i]->chkCollision(SCREEN_WIDTH, SCREEN_HEIGHT) || chkRobotCollisions(bullets[i]->getHitbox())) {
				delete bullets[i];
				bullets[i] = NULL;
			}
		}
	}
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			bullets[i]->render();
		}

		for (int i = 0; i < TOTAL_WEAPONS; ++i) {
			if (weapons[i] != NULL) {
				weapons[i]->setPos(300, 300, 0);
				weapons[i]->update();
				weapons[i]->render();
			}
		}
	}
}
	

	//Compares hitbox b against all robots
bool Game::chkRobotCollisions(Hitbox* b) {
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {
			if (b->chkCollision(robots[i]->getHitbox())) {
				return true;
			}
		}
	}
	return false;

}

void Game::genTestBullets() {
	int n = 1;
	int n_bullets = 1;
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] == NULL && n_bullets > 0) {
			bullets[i] = new Bullet(10, 200 + n_bullets * 100, 0.0, n * pow(2, n_bullets), gRenderer, &textures[2]);
			bullets[i]->setHitbox();
			//std::cout << i << std::endl;
			n_bullets--;
		}
	}
}
void Game::genTestRobots() {
	robots[0] = new NewRobot(500, 500, 0, gRenderer, &textures[0]);
	robots[0]->setHitbox();
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




void  Game::genTestWeapon() {
	weapons[0] = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
}