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
	images = { "assets/robotrightnew.png",
				"assets/cannonsmall.png",
				"assets/bullet-2.png",
				"assets/crate.png" };

	loadMedia();

	genTestRobots();
	genTestObstacles();
	genTestWeapon();
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
	//Creates Bullets
	WeaponFiring(e);
}
/*
The update should be set in the following order because object are dependent on other objects updates
1.Robot
2.Weapon
3.Bullet
*/
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
			if (bullets[i]->chkBorderCollision(SCREEN_WIDTH, SCREEN_HEIGHT) ||
				chkCollisions(robots, TOTAL_ROBOTS, bullets[i]) || 
				chkCollisions(obstacles, TOTAL_OBSTACLES, bullets[i]))
			{
				bullets[i]->isDead = true;
			}
			bullets[i]->render();
		}
	}
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] != NULL && bullets[i]->isDead) {
			delete bullets[i];
			bullets[i] = NULL;
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
	
void Game::genTestBullets() {
	int n = 1;
	int n_bullets = 1;
	for (int i = 0; i < TOTAL_BULLETS; ++i) {
		if (bullets[i] == NULL && n_bullets > 0) {
			bullets[i] = new Bullet(weapons[0]->getPosX(), weapons[0]->getPosY(), weapons[0]->getAngle() , 10, gRenderer, &textures[2]);
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
	weapons[0]->setHitbox();
}

void  Game::genTestObstacles() {
	obstacles[0] = new GameObject(300, 300, 0, gRenderer, &textures[3]);
	obstacles[0]->setHitbox();
	obstacles[1] = new GameObject(600, 100, 0, gRenderer, &textures[3]);
	obstacles[1]->setHitbox();
}

void Game::WeaponFiring(SDL_Event e) {

	//Handle BUllet Creation
	if (e.type == SDL_CONTROLLERAXISMOTION) {
		//Joystick input

		//If player 1 input
		if (e.caxis.which == 0) {
			if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
				genTestBullets();
				//std::cout << "BLAH" << std::endl;

			}
		}
	}
}