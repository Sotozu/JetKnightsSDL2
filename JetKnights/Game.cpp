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
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		weapons[i] = NULL;
	}
	for (int i = 0; i < TOTAL_BULLETS; i++) {
		bullets[i] = NULL;
	}
	for (int i = 0; i < TOTAL_OBSTACLES; i++) {
		obstacles[i] = NULL;
	}
	images =  { "assets/robotrightnew.png",
				"assets/cannonsmall.png",
				"assets/bullet.png",
				"assets/crate.png" };
	loadMedia();

	genTestBullets();
	genTestRobots();
	genTestObstacles();
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
	std::cout << "updating objects " << std::endl;
	updateRobots();
	updateWeapons();
	updateBullets();
	updateObstacles();
}

void Game::updateRobots() {
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {
			robots[i]->update();
			for (int j = 0; j < TOTAL_OBSTACLES; ++j) {
				if (obstacles[j] != NULL) {
					robots[i]->updateCollision(SCREEN_WIDTH, SCREEN_HEIGHT, obstacles[j]->getHitbox());
				}
			}
			
			robots[i]->render();
		}
	}
}

void Game::updateWeapons() {
	for (int i = 0; i < TOTAL_WEAPONS; ++i) {
		if (weapons[i] != NULL) {
			weapons[i]->setPos(robots[0]->getPosX(), robots[0]->getPosY(), 0);
			weapons[i]->update();
			weapons[i]->render();
		}
	}
}

void Game::updateBullets() {
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL) {
			bullets[i]->update();
		}
		if (bullets[i] != NULL) {
			if (bullets[i]->chkCollision(SCREEN_WIDTH, SCREEN_HEIGHT) || chkRobotCollisions(bullets[i]->getHitbox())) {
				delete bullets[i];
				bullets[i] = NULL;
			}
		}
		if (bullets[i] != NULL) {
			bullets[i]->render();
		}
	}
}

void Game::updateObstacles() {
	for (int i = 0; i < TOTAL_OBSTACLES; ++i) {
		if (obstacles[i] != NULL) {
			obstacles[i]->render();
		}
	}
}
	
bool Game::chkBorderCollision(Hitbox* b) {
	if (b != NULL) {
		//Check if bullet hits screen boundaries
		if ((b->x < 0) || (b->x + b->w > SCREEN_WIDTH) || (b->y < 0) || (b->y + b->h > SCREEN_HEIGHT)) {
			return true;
		}
	}
	return false;
}

// Compares hitbox b against all robots
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

void Game::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		textures[i].loadFromFile(images[i], gRenderer);
		//std::cout << "Texture loaded!!!" << std::endl;
	}
}

void Game::WeaponFiring() {
	genTestBullets();
}

void Game::genTestRobots() {
	robots[0] = new NewRobot(500, 500, 0, gRenderer, &textures[0]);
	robots[0]->setHitbox();
}

void  Game::genTestWeapon() {
	weapons[0] = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
	weapons[0]->setHitbox();
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

void  Game::genTestObstacles() {
	obstacles[0] = new GameObject(300, 300, 0, gRenderer, &textures[3]);
	obstacles[0]->setHitbox();
	obstacles[1] = new GameObject(600, 100, 0, gRenderer, &textures[3]);
	obstacles[1]->setHitbox();
}