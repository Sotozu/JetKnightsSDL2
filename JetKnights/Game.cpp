#include "Game.h"


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

	//Sets all weapons at the beginning to a not firing state
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		isWeaponFiring[i] = false;
	}

	//Sets all robots at the beginning to not boosting
	for (int i = 0; i < TOTAL_ROBOTS; i++) {
		isRobotBoosting[i] = false;
	}

	loadMedia();

	genTestRobots();
	genTestObstacles();
	genTestWeapon();
}

void Game::handleEvent(SDL_Event e) {

	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {

			robots[i]->handleRobotMovement(e);

			//If the player presses the right trigger then this will come true
			if (robots[i]->isPlayerBoosting(e) == true) {

				isRobotBoosting[i] = true;
			}
			else {
				isRobotBoosting[i] = false;
			}
		}
	}
	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (weapons[i] != NULL) {
			//updates movement of the weapon
			weapons[i]->handleEvent(e);
			//updates if the weapon is firing
			if (weapons[i]->WeaponFiring(e) == true) {
				isWeaponFiring[i] = true;
			}
			else {
				isWeaponFiring[i] = false;
			}
		}
	}

	//Creates Bullets

}
/*
The update should be set in the following order because object are dependent on other objects updates
1.Robot
2.Weapon
3.Bullet
*/
void Game::updateObjects() {
	//std::cout << "updating objects " << std::endl;
	updatePlayerBoost();
	updateRobots();
	updateWeapons();
	updateBulletCreation();
	updateBulletMovement();
	updateObstacles();
	

}

void Game::updateRobots() {
	for (int i = 0; i < TOTAL_ROBOTS; ++i) {
		if (robots[i] != NULL) {
			//This updates robots position
			robots[i]->update();
			for (int j = 0; j < TOTAL_OBSTACLES; ++j) {
				if (obstacles[j] != NULL) {
					//This checks if the robot has collided with any of the onjects
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

void Game::updateBulletMovement() {
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
	

//Iterates through each weapon in Game and if it is firing then it will generate bullets
void Game::updateBulletCreation() {

	for (int i = 0; i < TOTAL_WEAPONS; i++) {
		if (isWeaponFiring[i] == true) {
			int n = 1;
			int n_bullets = 1;
			for (int i = 0; i < TOTAL_BULLETS; ++i) {
				if (bullets[i] == NULL && n_bullets > 0) {
					bullets[i] = new Bullet(weapons[0]->getPosX(), weapons[0]->getPosY(), weapons[0]->getAngle(), 10, gRenderer, &textures[2]);
					bullets[i]->setHitbox();
					bullets[i]->team = 1;
					//std::cout << i << std::endl;
					n_bullets--;
				}
			}
		}
	}
	
}

void Game::updatePlayerBoost() {
	for (int i = 0; i < TOTAL_ROBOTS; i++) {
		if (robots[i] != NULL) {
			if (isRobotBoosting[i] == true) {
				robots[i]->boostOn();
			}
			else {
				robots[i]->boostOff();
			}
		}
	}
}
void Game::genTestRobots() {
	robots[0] = new NewRobot(500, 500, 0, gRenderer, &textures[0]);
	robots[0]->setHitbox();
	robots[0]->team = 1;
}

void Game::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		textures[i].loadFromFile(images[i], gRenderer);
		//std::cout << "Texture loaded!!!" << std::endl;
	}
}


void  Game::genTestWeapon() {
	weapons[0] = new NewWeapon(10, 10, 0, gRenderer, &textures[1]);
	weapons[0]->setHitbox();
	weapons[0]->team = 1;
}

void  Game::genTestObstacles() {
	obstacles[0] = new GameObject(300, 300, 0, gRenderer, &textures[3]);
	obstacles[0]->setHitbox();
	obstacles[1] = new GameObject(600, 100, 0, gRenderer, &textures[3]);
	obstacles[1]->setHitbox();
}


